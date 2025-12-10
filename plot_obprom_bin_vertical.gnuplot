set terminal pngcairo size 800,1800
set output 'grafica_obprom_bin_search_vertical.png'

set multiplot layout 3,1 title "Número promedio de OBs - Búsqueda binaria"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "OB promedio"

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'bin_1_ob.dat' using 1:2 with linespoints title "bin_search"

# ---------- n_times = 100 ----------
set title "n_times = 100"
set ylabel "OB promedio"
plot 'bin_100_ob.dat' using 1:2 with linespoints title "bin_search"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
set ylabel "OB promedio"
plot 'bin_10000_ob.dat' using 1:2 with linespoints title "bin_search"

unset multiplot
