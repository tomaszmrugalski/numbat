PASS3=YES
LATEX=pdflatex
DVIPS=dvips
PS2PDF=ps2pdf

LATEXOPTS=-file-line-error -halt-on-error

all: numbat-user.pdf

numbat-user.pdf: *.tex
	@echo "[LATEX  ] $(SUBDIR)/$@"
	$(LATEX) $(LATEXOPTS) numbat-user.tex >numbat-user-1st_pass.log
	if [ "$(PASS3)"=="YES" ]; then                                       \
	  echo "[LATEX  ] $(SUBDIR)/$@";                                     \
	  $(LATEX) $(LATEXOPTS) numbat-user.tex >numbat-user-2nd_pass.log; \
	  echo "[LATEX  ] $(SUBDIR)/$@";                                     \
	  $(LATEX) $(LATEXOPTS) numbat-user.tex >numbat-user-3rd_pass.log; \
	fi

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

.PHONY: version.tex
