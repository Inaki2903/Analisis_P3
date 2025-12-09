set terminal pngcairo size 800,600
set output 'ob_promedio_bin.png'

set title 'Número promedio de OBs: binaria'
set xlabel 'Tamaño N'
set ylabel 'OB promedio'
set grid
set key left top

plot 'bin_search_ob.dat' using 1:2 with linespoints title 'Búsqueda binaria'
