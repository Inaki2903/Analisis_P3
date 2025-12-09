set terminal pngcairo size 800,600
set output 'time_bin.png'

set title 'Tiempo promedio de reloj: búsqueda binaria'
set xlabel 'Tamaño N'
set ylabel 'Tiempo promedio (s)'
set grid
set key left top
set format y "%.1e"    # notación científica para ver mejor valores pequeños
# si quieres escala log en Y, descomenta la siguiente línea:
# set logscale y

plot 'bin_time.dat' using 1:2 with linespoints title 'Búsqueda binaria'
