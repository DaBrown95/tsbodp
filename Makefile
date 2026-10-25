PYTHON ?= python3
ANALYSIS_PYTHON ?= toolchains/analysis-venv/bin/python
PROGRESS_PYTHON ?= $(ANALYSIS_PYTHON)
SHARE_PROJECT_HEADERS ?= 0
HEADER_SNAPSHOT_FLAGS = $(if $(filter 1,$(SHARE_PROJECT_HEADERS)),--share-project-headers,)
TEST_PYTHON ?= $(if $(wildcard $(ANALYSIS_PYTHON)),$(ANALYSIS_PYTHON),$(PYTHON))
.DEFAULT_GOAL := build

.PHONY: setup setup-arm setup-old audit audit-all compare doctor test build pilot analyze pilot-matrix ram-map inventory progress
setup:
	$(PYTHON) tools/setup.py

setup-arm:
	$(PYTHON) tools/setup_arm.py

setup-old:
	$(PYTHON) tools/setup_old.py

audit:
	$(PYTHON) tools/project.py audit
audit-all: audit
	$(PYTHON) tools/project.py audit --target us-rev1

compare:
	$(PYTHON) tools/project.py compare

doctor:
	$(PYTHON) tools/project.py doctor

test:
	$(TEST_PYTHON) -m unittest discover -s tests -v

analyze:
	$(ANALYSIS_PYTHON) tools/analyze.py

pilot:
	$(ANALYSIS_PYTHON) tools/pilot.py --negative-control $(HEADER_SNAPSHOT_FLAGS)

pilot-matrix:
	$(ANALYSIS_PYTHON) tools/pilot.py --negative-control --matrix $(HEADER_SNAPSHOT_FLAGS)

build:
	$(ANALYSIS_PYTHON) tools/build_rom.py $(HEADER_SNAPSHOT_FLAGS)

ram-map:
	$(PYTHON) tools/map_ram.py

inventory:
	$(ANALYSIS_PYTHON) tools/inventory_rom.py

progress: build inventory
	$(PROGRESS_PYTHON) tools/render_progress.py
	$(PROGRESS_PYTHON) tools/triage.py
