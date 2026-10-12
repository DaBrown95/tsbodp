#!/usr/bin/env python3
"""Read-only ROM inspection and strict comparison; standard library only."""

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import sys
import zlib
from datetime import datetime, timezone


ROOT = Path(__file__).resolve().parents[1]


def hashes(data):
    return {"sha1": hashlib.sha1(data).hexdigest(),
            "sha256": hashlib.sha256(data).hexdigest(),
            "md5": hashlib.md5(data).hexdigest(),
            "crc32": f"{zlib.crc32(data):08x}"}


def inspect_rom(data, target):
    result = {"target": target["id"], "size": len(data), **hashes(data)}
    checks = {
        "size": len(data) == target["size"],
        "catalogue_sha1": result["sha1"] == target["sha1"],
        "header_present": len(data) >= 0xC0,
    }
    for name in ("sha256", "md5", "crc32"):
        if name in target:
            checks[name] = result[name] == target[name]
    if checks["header_present"]:
        calculated = (-sum(data[0xA0:0xBD]) - 0x19) & 0xFF
        result["header"] = {
            "title": data[0xA0:0xAC].rstrip(b"\0").decode("ascii", errors="replace"),
            "game_code": data[0xAC:0xB0].decode("ascii", errors="replace"),
            "maker_code": data[0xB0:0xB2].decode("ascii", errors="replace"),
            "revision": data[0xBC],
            "fixed_byte": data[0xB2],
            "checksum_stored": data[0xBD],
            "checksum_calculated": calculated,
        }
        checks.update({
            "game_code": result["header"]["game_code"] == target["game_code"],
            "revision": data[0xBC] == target["revision"],
            "fixed_byte": data[0xB2] == 0x96,
            "header_checksum": data[0xBD] == calculated,
        })
    result["checks"] = checks
    result["accepted"] = all(checks.values())
    return result


def compare_bytes(reference, candidate):
    overlap = min(len(reference), len(candidate))
    first = []
    differences = 0
    for offset in range(overlap):
        if reference[offset] != candidate[offset]:
            differences += 1
            if len(first) < 16:
                first.append({"offset": offset, "expected": reference[offset],
                              "actual": candidate[offset]})
    differences += abs(len(reference) - len(candidate))
    if len(first) < 16 and len(reference) != len(candidate):
        for offset in range(overlap, min(max(len(reference), len(candidate)),
                                         overlap + 16 - len(first))):
            first.append({"offset": offset,
                          "expected": reference[offset] if offset < len(reference) else None,
                          "actual": candidate[offset] if offset < len(candidate) else None})
    return {
        "identical": differences == 0,
        "reference_size": len(reference),
        "candidate_size": len(candidate),
        "differing_bytes_including_missing_or_extra": differences,
        "first_differences": first,
        "candidate_hashes": hashes(candidate),
        "scope": "all bytes; no masks or ignored ranges",
        "source_reconstruction_verified": False,
    }


def local_path(value):
    path = Path(value)
    return path if path.is_absolute() else ROOT / path


def write_report(name, result, target_id="us-eu"):
    path = ROOT / "reports" / target_id / (name + ".json")
    path.parent.mkdir(parents=True, exist_ok=True)
    result["recorded_at_utc"] = datetime.now(timezone.utc).isoformat()
    path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(f"Report: {path}")


def audit(path, target):
    data = path.read_bytes()
    result = inspect_rom(data, target)
    result["input_path"] = str(path.resolve())
    write_report("audit", result, target["id"])
    print(f"ROM identity: {'PASS' if result['accepted'] else 'FAIL'}")
    print(f"Size: {result['size']} bytes")
    print(f"SHA-1: {result['sha1']}")
    print(f"SHA-256: {result['sha256']}")
    for check, passed in result["checks"].items():
        if not passed:
            print(f"Failed check: {check}")
    return data, result


def doctor(target):
    names = ["git", "make", "arm-none-eabi-as", "arm-none-eabi-ld",
             "arm-none-eabi-objdump", "arm-none-eabi-objcopy", "agbcc", "objdiff", "mgba"]
    result = {"python": sys.version, "python_executable": sys.executable,
              "tools": {name: shutil.which(name) for name in names},
              "compiler_status": target["compiler_status"],
              "matching_build_configured": False}
    result["local_tools"] = {
        name: str(ROOT / name) if (ROOT / name).is_file() else None
        for name in ("toolchains/agbcc/gcc/agbcc", "toolchains/binutils/bin/arm-none-eabi-as",
                     "toolchains/binutils/bin/arm-none-eabi-ld", "toolchains/analysis-venv/bin/python")
    }
    write_report("doctor", result, target["id"])
    for name, path in result["tools"].items():
        print(f"{name}: {path or 'not found on PATH'}")
    for name, path in result["local_tools"].items():
        print(f"{name}: {path or 'not available'}")
    print(f"Compiler evidence: {target['compiler_status']}; run make build for the partial matching ROM reconstruction.")
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("audit", "compare"):
        command = sub.add_parser(name)
        command.add_argument("--target", choices=("us-eu", "us-rev1"), default="us-eu")
        command.add_argument("--rom", help="ROM path; relative paths use the project root")
        if name == "compare":
            command.add_argument("--built")
    sub.add_parser("doctor").add_argument("--target", choices=("us-eu", "us-rev1"), default="us-eu")
    args = parser.parse_args()
    target = json.loads((ROOT / "config/targets" / (args.target + ".json")).read_text())
    try:
        if args.command == "doctor":
            return doctor(target)
        rom_path = local_path(args.rom or target["rom_path"])
        if not rom_path.is_file():
            print(f"ROM dump needed at: {rom_path}", file=sys.stderr)
            return 2
        reference, identity = audit(rom_path, target)
        if not identity["accepted"]:
            if args.command == "compare":
                write_report("compare", {"identical": False, "comparison_performed": False,
                                         "reason": "Reference ROM failed identity audit"}, target["id"])
            print("Stop: the input does not pass this target's identity checks.", file=sys.stderr)
            return 1
        if args.command == "audit":
            return 0
        built_path = local_path(args.built or f"build/{target['id']}/bustin-out.gba")
        if not built_path.is_file():
            write_report("compare", {"identical": False, "comparison_performed": False,
                                     "reason": "Built ROM is missing"}, target["id"])
            print(f"Built ROM needed at: {built_path}", file=sys.stderr)
            return 2
        if built_path.samefile(rom_path):
            write_report("compare", {"identical": False, "comparison_performed": False,
                                     "reason": "Candidate and reference are the same file"}, target["id"])
            print("Candidate must be a separate build output.", file=sys.stderr)
            return 2
        result = compare_bytes(reference, built_path.read_bytes())
        result.update({"reference_path": str(rom_path.resolve()),
                       "reference_hashes": hashes(reference),
                       "candidate_path": str(built_path.resolve()),
                       "comparison_performed": True})
        write_report("compare", result, target["id"])
        print(f"Whole-ROM equality: {'PASS' if result['identical'] else 'FAIL'}")
        print(f"Different/missing/extra bytes: {result['differing_bytes_including_missing_or_extra']}")
        print("This checks binary equality only; source reconstruction needs separate evidence.")
        return 0 if result["identical"] else 1
    except OSError as error:
        print(f"File operation failed: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
