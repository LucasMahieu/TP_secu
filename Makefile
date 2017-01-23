all: compile clean

compile:
	pdflatex main.tex
	pdflatex main.tex
view:
	evince main.pdf 2>/dev/null &
open:
	open main.pdf
clean:
	rm *.log *.nlo *.toc *.aux *.blg *.fls *.ilg *.bbl *.nls
