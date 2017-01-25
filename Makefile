all: git-hook alert compile clean

git-hook:
	@cp pre-commit .git/hooks/
alert:
	@echo "********************************************************************************"
	@echo " PAS DE _ TOUT SEUL SVP,  mettez \_"
	@echo " COMPILEZ AVANT DE PUSH/COMMIT"
	@echo " IL Y A DEJA EU PLUSIEURS COMMITS QUI NE COMPILAIT PAS"
	@echo " C'EST ASSEZ ENNUYANT."
	@echo "********************************************************************************"
	@sleep 2
compile:
	pdflatex main.tex
	pdflatex main.tex
view:
	evince main.pdf 2>/dev/null &
open:
	open main.pdf
clean:
	-@rm *.log *.nlo *.toc *.aux *.blg *.fls *.ilg *.bbl *.nls
