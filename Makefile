LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

# content/contest/hash.sh (used for the per-file hashes) needs `cpp -fpreprocessed`.
# On macOS `cpp` is clang, which lacks that flag and silently yields the hash of
# an empty string (d41d8c). In that case put Homebrew's GNU cpp first in PATH.
CPP_SHIM =
ifneq ($(shell echo | cpp -fpreprocessed >/dev/null 2>&1 || echo broken),)
GNU_CPP := $(firstword $(foreach v,16 15 14 13 12 11 10,$(shell command -v cpp-$(v) 2>/dev/null)))
CPP_SHIM = build/bin/cpp
export PATH := $(CURDIR)/build/bin:$(PATH)
endif

help:
	@echo "This makefile builds KACTL (KTH Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build KACTL, quickly (only runs LaTeX once)"
	@echo "	make kactl		- to build KACTL"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove kactl.pdf"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

fast: | build $(CPP_SHIM)
	$(LATEXCMD) content/kactl.tex </dev/null
	cp build/kactl.pdf kactl.pdf

kactl: test-session.pdf | build $(CPP_SHIM)
	$(LATEXCMD) content/kactl.tex && $(LATEXCMD) content/kactl.tex
	cp build/kactl.pdf kactl.pdf

clean:
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc

veryclean: clean
	rm -f kactl.pdf test-session.pdf

.PHONY: help fast kactl clean veryclean

build:
	mkdir -p build/

build/bin/cpp: | build
	@if [ -z "$(GNU_CPP)" ]; then echo "error: cpp lacks -fpreprocessed and no GNU cpp-N found (brew install gcc)" >&2; exit 1; fi
	mkdir -p build/bin
	printf '#!/bin/sh\nexec "%s" "$$@"\n' "$(GNU_CPP)" > $@
	chmod +x $@

test:
	./doc/scripts/run-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build $(CPP_SHIM)
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
