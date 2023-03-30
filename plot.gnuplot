set logscale x 10
set terminal png font arial 14 size 1600,600
set key font "Arial, 24"
set title font "Arial, 30"
set output "resultado.png"
set grid
set title "Função de Inserção"
set format x "%2.0t{/Symbol \264}10^{%L}"
set format y "%2.0t{/Symbol \264}10^{%L}"
set xrange [1:10000000]
plot "resultados.dat" with points lw 5 lt rgb "red" title "Empirico", \
    x*log(x) lw 5 lt rgb "blue" title "Grafico"