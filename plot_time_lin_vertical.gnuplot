set terminal pngcairo size 800,1800
set output 'grafica_time_lin_search_vertical.png'

set multiplot layout 3,1 title "Tiempo promedio - Búsqueda lineal"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "Tiempo promedio (s)"
set format y "%.1e"

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'lin_1_time.dat' using 1:2 with linespoints title "lin_search"

# ---------- n_times = 100 ----------
set title "n_times = 100"
set ylabel "Tiempo promedio (s)"
plot 'lin_100_time.dat' using 1:2 with linespoints title "lin_search"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
set ylabel "Tiempo promedio (s)"
plot 'lin_10000_time.dat' using 1:2 with linespoints title "lin_search"

unset multiplot
