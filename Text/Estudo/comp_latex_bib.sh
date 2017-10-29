echo "Inicio da compilacao"
pdflatex estudo_mult.tex
bibtex estudo_mult
pdflatex estudo_mult.tex
pdflatex estudo_mult.tex
echo "Fim da compilacao"

