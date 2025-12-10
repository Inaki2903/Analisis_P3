set terminal pngcairo size 1800,600
set output 'grafica_time_lin_vs_bin.png'

set multiplot layout 1,3 title "Comparación del tiempo promedio: Búsqueda lineal vs binaria"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "Tiempo promedio (s)"
set format y "%.1e"   # notación científica para tiempos pequeños

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'lin_1_time.dat' using 1:2 with linespoints title "Búsqueda lineal", \
     'bin_1_time.dat' using 1:2 with linespoints title "Búsqueda binaria"

# ---------- n_times = 100 ----------
set title "n_times = 100"
unset ylabel
plot 'lin_100_time.dat' using 1:2 with linespoints title "Búsqueda lineal", \
     'bin_100_time.dat' using 1:2 with linespoints title "Búsqueda binaria"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
plot 'lin_10000_time.dat' using 1:2 with linespoints title "Búsqueda lineal", \
     'bin_10000_time.dat' using 1:2 with linespoints title "Búsqueda binaria"

unset multiplot
