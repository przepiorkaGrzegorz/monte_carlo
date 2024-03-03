reset

## Particles positions
set terminal qt 1 size 800, 660
set xlabel 'x' font "Arial, 11"
set ylabel 'y' font "Arial, 11"
set tics font "Arial, 11"
set xrange [-14 : 14]
set yrange [-14 : 14]

set multiplot layout 1, 2 rows scale 1.0, 1.0
set size ratio 1

    set title 'time step = 1' font "Arial, 15"
    plot "./data/pos1.dat" u 1:2 w d title ''

    set title 'time step = 45' font "Arial, 15"
    plot "./data/pos40.dat" u 1:2 w d title ''

unset multiplot

## Diffusion coefficients in time
reset
set terminal qt 2 size 800, 660
set xlabel 'time step' font "Arial, 12"
set ylabel 'D' font "Arial, 12"
set tics font "Arial, 11"

set multiplot layout 2,2

do for [i = 2:5] {
    set title sprintf("n\\\_particles = %d", 10**i) font "Arial, 15"

    plot sprintf("./data/coeffs_open_%d.dat", i) u 1 w l lw 1.5 title 'Dxx(t)', \
        sprintf("./data/coeffs_open_%d.dat", i) u 2 w l lw 1.5 title 'Dxy(t)', \
        sprintf("./data/coeffs_open_%d.dat", i) u 3 w l lw 1.5 title 'Dyy(t)'
}

unset multiplot