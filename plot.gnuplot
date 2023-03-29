set logscale x 10
set terminal png
set output "resultado.png"
set grid
set title "Inserção"
plot "resultados.dat" with lines lc 8 lw 2