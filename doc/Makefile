PASS3=YES
LATEX=pdflatex
DVIPS=dvips
PS2PDF=ps2pdf

LATEXOPTS=-file-line-error -halt-on-error

all: numbat-user.pdf

devel:
	mkdir -p html/
	cd .. && doxygen doxy.cfg > doc/html/doxygen.log 2>doc/html/doxygen-error.log
	echo `grep -i ": warning:" html/doxygen-error.log | wc -l` warnings detected.

version.tex:
	@echo "[GREP   ] $(SUBDIR)/$@"
	@../test/xtract_version > $@
	@echo "[PERL   ] $(SUBDIR)/$@"
	perl -i -pe 's/_/\\_/g' version.tex
	perl -i -pe 's/^/\\newcommand{\\version}{/' version.tex
	perl -i -pe 's/$$/ }/' version.tex

clean:
	@echo "[CLEAN  ] $(SUBDIR)"
	@rm -f *.aux *.idx *.log *.toc *.out *~ *.ps *.dvi *.tmp version.tex

clobber: clean
	@rm -f *.pdf

.PHONY: version.tex devel
