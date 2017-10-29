set terminal png size 800,500 enhanced font "Helvetica,20"
unset cblabel
set output 'erro_n_256.png'
set pal color 
unset pm3d
set surface
unset key
set format z
set palette
set title "Solução aproximada n=256"
set ticslevel 0
set border 4095
set xrange [0:1]; set yrange [0:1]
set hidden3d
set isosamples 40,40; set samples 40,40
set pal maxcolors 0
set xlabel "x"
set ylabel "y"
splot 'saida.txt' with lines palette

