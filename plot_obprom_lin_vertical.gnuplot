set terminal pngcairo size 800,1800
set output 'grafica_obprom_lin_search_vertical.png'

set multiplot layout 3,1 title "Número promedio de OBs - Búsqueda lineal"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "OB promedio"

# ---------- n_times = 1 ----------
set title "n_times = 1"
plot 'lin_1_ob.dat' using 1:2 with linespoints title "lin_search"

# ---------- n_times = 100 ----------
set title "n_times = 100"
set ylabel "OB promedio"
plot 'lin_100_ob.dat' using 1:2 with linespoints title "lin_search"

# ---------- n_times = 10000 ----------
set title "n_times = 10000"
set ylabel "OB promedio"
plot 'lin_10000_ob.dat' using 1:2 with linespoints title "lin_search"

unset multiplot
