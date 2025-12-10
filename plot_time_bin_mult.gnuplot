set terminal pngcairo size 1800,600
set output 'grafica_time_bin_search.png'

set multiplot layout 1,3 title "Tiempo promedio de búsqueda binaria"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "Tiempo promedio (s)"
set format y "%.1e"

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'bin_1_time.dat' using 1:2 with linespoints title "bin_search"

# ---------- n_times = 100 ----------
set title "n_times = 100"
unset ylabel
plot 'bin_100_time.dat' using 1:2 with linespoints title "bin_search"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
plot 'bin_10000_time.dat' using 1:2 with linespoints title "bin_search"

unset multiplot
