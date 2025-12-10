set terminal pngcairo size 800,1200
set output 'ob_normalized_lin_bin.png'

set multiplot layout 2,1 title "Normalización de OB promedio: lineal vs binaria"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "OB_prom/N"

# ----- ARRIBA: lin_search, OB_prom / N -----
set title "Búsqueda lineal: OB_promedio / N"
plot 'lin_100_ob.dat' using 1:($2/$1) with linespoints title "lin_search (OB_prom/N)"

# ----- ABAJO: bin_search, OB_prom / log2(N) -----
set title "Búsqueda binaria: OB_promedio / log2(N)"
set ylabel "OB_prom / log2(N)"

# log2(N) = log(N)/log(2) en gnuplot
plot 'bin_100_ob.dat' using 1:($2/(log($1)/log(2))) with linespoints title "bin_search (OB_prom/log2(N))"

unset multiplot
