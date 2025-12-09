set terminal pngcairo size 800,600
set output 'ob_promedio_auto.png'

set title 'OB promedio: lineal auto-organizada'
set xlabel 'Tamaño N'
set ylabel 'OB promedio'
set grid
set key left top

plot 'lin_auto_search_ob.dat' using 1:2 with linespoints title 'Búsqueda lineal auto-organizada'
