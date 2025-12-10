set terminal pngcairo size 800,1800
set output 'grafica_time_bin_vs_auto_vertical.png'

set multiplot layout 3,1 title "Comparación del tiempo promedio: bin_search vs lin_auto_search"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "Tiempo promedio (s)"
set format y "%.1e"   # notación científica para tiempos pequeños

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'bin_1_time.dat'      using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_1_time.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

# ---------- n_times = 100 ----------
set title "n_times = 100"
set ylabel "Tiempo promedio (s)"
plot 'bin_100_time.dat'      using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_100_time.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
set ylabel "Tiempo promedio (s)"
plot 'bin_10000_time.dat'      using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_10000_time.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

unset multiplot
