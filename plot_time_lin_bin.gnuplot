set terminal pngcairo size 800,600
set output 'time_lin_vs_bin_100.png'

set title 'Tiempo promedio de reloj: búsqueda lineal vs binaria'
set xlabel 'Tamaño N'
set ylabel 'Tiempo promedio (s)'
set grid
set key left top
set format y "%.1e"    # notación científica para ver mejor valores pequeños
# si quieres escala log en Y, descomenta la siguiente línea:
# set logscale y

plot 'lin_100_time.dat' using 1:2 with linespoints title 'Búsqueda lineal', \
     'bin_100_time.dat' using 1:2 with linespoints title 'Búsqueda binaria'
