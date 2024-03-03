reset
set xlabel "x" font "Helvetica, 12"
set ylabel "y" font "Helvetica, 12"
set tics font "Helvetica, 11"

set terminal qt 1 size 800, 660
set multiplot layout 1, 3 rows scale 1.0, 1.0
set size ratio 1

### Subplot 1 ###
    set title "Gauss" font "Helvetica, 12"
    set xrange [-5: 5]
    set yrange [-5: 5]
    plot './data/gauss.dat' u 1:2 w d title ''


### Subplot 2 ###
    set title "Circle" font "Helvetica, 12"
    set xrange [-1.5: 1.5]
    set yrange [-1.5: 1.5]
    plot './data/in_circle.dat' u 1:2 w d title ''


### Subplot 3 ###
    set title "Elipse" font "Helvetica, 12"
    set xrange [-1: 1]
    set yrange [-1: 1]
    plot './data/in_elipse.dat' u 1:2 w d title ''

unset multiplot