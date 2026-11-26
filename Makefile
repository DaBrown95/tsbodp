PYTHON ?= python3
ANALYSIS_PYTHON ?= toolchains/analysis-venv/bin/python
TEST_PYTHON ?= $(if $(wildcard $(ANALYSIS_PYTHON)),$(ANALYSIS_PYTHON),$(PYTHON))
SHARE_PROJECT_HEADERS ?= 0
HEADER_SNAPSHOT_FLAGS = $(if $(filter 1,$(SHARE_PROJECT_HEADERS)),--share-project-headers,)

# Every per-target command takes TARGET=rev0 (USA/Europe) or TARGET=rev1 (USA revision 1).
TARGETS := rev0 rev1
TARGET ?= rev0
export TSBO_TARGET := $(TARGET)
# `make port` carries new matches from FROM into TARGET's manifest.
FROM ?= $(if $(filter rev0,$(TARGET)),rev1,rev0)

.DEFAULT_GOAL := build
.PHONY: setup setup-arm setup-old audit audit-all compare doctor test pilot pilot-matrix \
        build build-all ram-map inventory port prune

setup:
	$(PYTHON) tools/setup.py

setup-arm:
	$(PYTHON) tools/setup_arm.py

setup-old:
	$(PYTHON) tools/setup_old.py

audit:
	$(PYTHON) tools/project.py audit

audit-all:
	$(foreach t,$(TARGETS),$(PYTHON) tools/project.py audit --target $(t) &&) true

compare:
	$(PYTHON) tools/project.py compare

doctor:
	$(PYTHON) tools/project.py doctor

test:
	$(TEST_PYTHON) -m unittest discover -s tests -v

pilot:
	$(ANALYSIS_PYTHON) tools/pilot.py --negative-control $(HEADER_SNAPSHOT_FLAGS)

pilot-matrix:
	$(ANALYSIS_PYTHON) tools/pilot.py --negative-control --matrix $(HEADER_SNAPSHOT_FLAGS)

build:
	$(ANALYSIS_PYTHON) tools/build_rom.py $(HEADER_SNAPSHOT_FLAGS)

build-all:
	$(foreach t,$(TARGETS),$(MAKE) build TARGET=$(t) &&) true

ram-map:
	$(PYTHON) tools/map_ram.py

inventory:
	$(ANALYSIS_PYTHON) tools/inventory_rom.py

port:
	$(ANALYSIS_PYTHON) tools/port_target.py --from $(FROM) --to $(TARGET)

prune:
	$(PYTHON) tools/prune_runs.py
