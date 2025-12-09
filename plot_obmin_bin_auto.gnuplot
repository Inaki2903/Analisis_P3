set terminal pngcairo size 800,600
set output 'obmin_auto.png'

set title 'OB mínimo: lineal auto-organizada'
set xlabel 'Tamaño N'
set ylabel 'OB mínimo'
set grid
set key left top

plot 'auto_obmin.dat' using 1:2 with linespoints title 'Búsqueda lineal auto-organizada'
