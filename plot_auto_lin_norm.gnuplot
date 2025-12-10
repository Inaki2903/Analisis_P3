set terminal pngcairo size 800,1200
set output 'auto_lin_ob_normalized.png'

set multiplot layout 2,1 title "Normalización de OB promedio - lin_auto_search"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"

# ----- ARRIBA: n_times = 1, OB_prom / N -----
set title "lin_auto_search (n_times = 1): OB_promedio / N"
set ylabel "OB_prom / N"

plot 'auto_lin_1_ob.dat' using 1:($2/$1) with linespoints \
     title "auto_lin_search (OB_prom/N)"

# ----- ABAJO: n_times = 10000, OB_prom / log2(N) -----
set title "lin_auto_search (n_times = 10000): OB_promedio / log2(N)"
set ylabel "OB_prom / log2(N)"

# log2(N) = log(N)/log(2) en gnuplot
plot 'auto_lin_10000_ob.dat' using 1:($2/(log($1)/log(2))) with linespoints \
     title "auto_lin_search (OB_prom/log2(N))"

unset multiplot
