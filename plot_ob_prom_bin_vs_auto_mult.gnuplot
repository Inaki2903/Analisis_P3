set terminal pngcairo size 1800,600
set output 'grafica_ob_prom_bin_vs_auto.png'

set multiplot layout 1,3 title "Comparación del número promedio de OBs: Binaria vs Lineal Auto-organizada"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "OB promedio"

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'bin_1_ob.dat'       using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_1_ob.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

# ---------- n_times = 100 ----------
set title "n_times = 100"
unset ylabel
plot 'bin_100_ob.dat'       using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_100_ob.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
plot 'bin_10000_ob.dat'       using 1:2 with linespoints title "Búsqueda binaria", \
     'auto_lin_10000_ob.dat' using 1:2 with linespoints title "Búsqueda lineal auto-organizada"

unset multiplot
