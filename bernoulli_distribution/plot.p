reset
set logscale xy
set format x "10^{%L}"
set format y "10^{%L}"
set xlabel 'n [-]' font "Helvetica, 12"
set tics font "Helvetica, 11"
set key font ", 11"

## Chosen probabilities
p1 = 0.1
p2 = 0.5
p3 = 0.9


set terminal qt 0 size 800, 660
    set multiplot layout 1,2 columns scale 1.0, 1.0

    set title 'Expected value' font "Helvetica, 12"
    set ylabel '<x> [-]' font "Helvetica, 12"
    set key right bottom

    plot "data/exp.dat" u 1:2 w lp t sprintf("p = %.1f", p1), \
        "data/exp.dat" u 1:4 w lp t sprintf("p = %.1f", p2), \
        "data/exp.dat" u 1:6 w lp t sprintf("p = %.1f", p3), \
        "data/exp.dat" u 1:3 w lines t sprintf("p = %.1f (theory)", p1), \
        "data/exp.dat" u 1:5 w lines t sprintf("p = %.1f (theory)", p2), \
        "data/exp.dat" u 1:7 w lines t sprintf("p = %.1f (theory)", p3)

    set title 'Variance' font "Helvetica, 12"
    set ylabel 'var [-]' font "Helvetica, 12"
    set key right top

    plot "data/var.dat" u 1:2 w lp t sprintf("p = %.1f", p1), \
    "data/var.dat" u 1:4 w lp t sprintf("p = %.1f", p2), \
        "data/var.dat" u 1:6 w lp t sprintf("p = %.1f", p3), \
        "data/var.dat" u 1:3 w lines t sprintf("p = %.1f (theory)", p1), \
        "data/var.dat" u 1:5 w lines t sprintf("p = %.1f (theory)", p2), \
        "data/var.dat" u 1:7 w lines t sprintf("p = %.1f (theory)", p3)

    unset multiplot

set terminal qt 1 size 800, 660
    set multiplot layout 1,2 columns scale 1.0, 1.0

    set title 'Expected value error' font "Helvetica, 12"
    set ylabel '<x> err [-]' font "Helvetica, 12"
    
    plot "data/exp_err.dat" u 1:2 w lp title sprintf("p = %.1f", p1), \
        "data/exp_err.dat" u 1:3 w lp title sprintf("p = %.1f", p2), \
        "data/exp_err.dat" u 1:4 w lp title sprintf("p = %.1f", p3)

    set title 'Variance error' font "Helvetica, 12"
    set ylabel 'var err [-]' font "Helvetica, 12"

    plot "data/var_err.dat" u 1:2 w lp title sprintf("p = %.1f", p1), \
        "data/var_err.dat" u 1:3 w lp title sprintf("p = %.1f", p2), \
        "data/var_err.dat" u 1:4 w lp title sprintf("p = %.1f", p3)
    
    unset multiplot

unset logscale