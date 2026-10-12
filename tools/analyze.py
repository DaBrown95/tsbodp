#!/usr/bin/env python3
"""Reproduce the bounded startup audit; not automatic whole-ROM disassembly."""

import hashlib
import json
from pathlib import Path
import re
import struct

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
from project import ROOT, audit, write_report


def main():
    target = json.loads((ROOT / "config/targets/us-eu.json").read_text())
    data, identity = audit(ROOT / target["rom_path"], target)
    if not identity["accepted"]:
        return 1
    regions = [
        {"name": "ARM startup", "offset": 0xC0, "size": 0x2C, "mode": "ARM"},
        {"name": "Thumb startup", "offset": 0xEC, "size": 0x1C, "mode": "Thumb"},
        {"name": "ARM interrupt enable helper", "offset": 0x130, "size": 0x18, "mode": "ARM"},
        {"name": "ARM interrupt disable helper", "offset": 0x148, "size": 0x18, "mode": "ARM"},
        {"name": "ARM IRQ dispatcher", "offset": 0x160, "size": 0x128, "mode": "ARM"},
        {"name": "Thumb startup copy helper", "offset": 0x288, "size": 0x16, "mode": "Thumb"},
        {"name": "Thumb entry routine", "offset": 0x25C0C, "size": 0xC4, "mode": "Thumb"},
    ]
    manifest = json.loads((ROOT / "pilot/manifest.json").read_text())
    for function in manifest["functions"]:
        regions.append({"name": function["name"], "offset": function["rom_offset"],
                        "size": function["size"], "mode": "Thumb", "includes_literal_data": True})
    word = lambda offset: struct.unpack_from("<I", data, offset)[0]
    copies = []
    for literal_offset in (0x114, 0x120):
        source, start, end = (word(literal_offset + i) for i in (0, 4, 8))
        copies.append({"source": f"{source:#010x}", "destination": f"{start:#010x}",
                       "size": end - start})
    report = {
        "target": "us-eu", "reference_sha256": identity["sha256"],
        "entry": {"rom_entry_offset": 0, "startup_offset": 0xC0,
                  "thumb_entry_address": f"{word(0x12C):#010x}",
                  "thumb_entry_code_address": f"{word(0x12C) & ~1:#010x}"},
        "startup_ram_copies": copies,
        "irq_vector_pointer": f"{word(0x110):#010x}",
        "irq_dispatcher_address": "0x08000160", "regions": regions,
        "limitations": ["Bounded static map, not a complete code/data inventory.",
                        "Executable extents inside the RAM copies are not established.",
                        "Pilot extents include literal data; not every byte is an instruction."],
        "player_signature_matches": [{"offset": m.start(), "text": m.group().decode()}
                                     for m in re.finditer(rb"\$Id: player\.c[^\x00]*", data)],
    }
    other = json.loads((ROOT / "config/targets/us-rev1.json").read_text())
    other_path = ROOT / other["rom_path"]
    if other_path.is_file():
        revision, rev_identity = audit(other_path, other)
        if not rev_identity["accepted"]:
            return 1
        report["revision_comparison"] = {
            "rev1_sha256": hashlib.sha256(revision).hexdigest(),
            "first_header_difference": next(i for i in range(0xC0) if data[i] != revision[i]),
            "first_post_header_difference": next(i for i in range(0xC0, len(data)) if data[i] != revision[i]),
            "same_offset_differing_bytes": sum(x != y for x, y in zip(data, revision)),
            "interpretation": "Same-offset bytes only; relocation shifts can inflate differences.",
        }
    path = ROOT / "reports/us-eu/initial-disassembly.txt"
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w") as stream:
        for region in regions:
            stream.write(f"\n{region['name']} at {0x08000000 + region['offset']:#x}, {region['size']} bytes; includes literal data: {region.get('includes_literal_data', False)}\n")
            disassembler = Cs(CS_ARCH_ARM, CS_MODE_ARM if region["mode"] == "ARM" else CS_MODE_THUMB)
            start = region["offset"]
            for instruction in disassembler.disasm(data[start:start + region["size"]], 0x08000000 + start):
                stream.write(f"{instruction.address:08x} {instruction.mnemonic:8} {instruction.op_str}\n")
    write_report("initial-analysis", report)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
