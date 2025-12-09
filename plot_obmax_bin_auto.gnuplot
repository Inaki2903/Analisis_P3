set terminal pngcairo size 800,600
set output 'obmax_auto.png'

set title 'OB máximo: búsqueda lineal auto-organizada'
set xlabel 'Tamaño N'
set ylabel 'OB máximo'
set grid
set key left top

plot 'auto_obmax.dat' using 1:2 with linespoints title 'Búsqueda lineal auto-organizada'
