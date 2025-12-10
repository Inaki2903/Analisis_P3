set terminal pngcairo size 800,1800
set output 'obmax_auto_vertical.png'

set multiplot layout 3,1 title "OB máximo - Búsqueda lineal auto-organizada"

set grid
set key top left
set xlabel "Tamaño del diccionario (N)"
set ylabel "OB máximo"

# n_times = 1
set title "lin_auto_search - n_times = 1"
plot 'auto_lin_1_obmax.dat' using 1:2 with linespoints title "OB_max"

# n_times = 100
set title "lin_auto_search - n_times = 100"
set ylabel "OB máximo"
plot 'auto_lin_100_obmax.dat' using 1:2 with linespoints title "OB_max"

# n_times = 10000
set title "lin_auto_search - n_times = 10000"
set ylabel "OB máximo"
plot 'auto_lin_10000_obmax.dat' using 1:2 with linespoints title "OB_max"

unset multiplot
