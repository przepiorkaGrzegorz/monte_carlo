reset
N = 1E05

set terminal qt 0 size 600, 600
    stats './data/in_circle_A.dat' u 1 name "Data_Ax" nooutput
    stats './data/in_circle_A.dat' u 2 name "Data_Ay" nooutput
    stats './data/in_circle_B.dat' u 1 name "Data_Bx" nooutput
    stats './data/in_circle_B.dat' u 2 name "Data_By" nooutput

    x_min_A = Data_Ax_min
    x_max_A = Data_Ax_max
    y_min_A = Data_Ay_min
    y_max_A = Data_Ay_max

    x_min_B = Data_Bx_min
    x_max_B = Data_Bx_max
    y_min_B = Data_By_min
    y_max_B = Data_By_max

    if(x_min_A < x_min_B){
        x_min = x_min_A
    }
    else{
        x_min = x_min_B
    }

    if(y_min_A < y_min_B){
        y_min = y_min_A
    }
    else{
        y_min = y_min_B
    }

    if(x_max_A > x_max_B){
        x_max = x_max_A
    }
    else{
        x_max = x_max_B
    }

    if(y_max_A > y_max_B){
        y_max = y_max_A
    }
    else{
        y_max = y_max_B
    }

    set tics font "Helvetica, 11"
    set xlabel 'x' font "Helvetica, 12"
    set ylabel 'y' font "Helvetica, 12"
    set xrange [x_min - 1.0 : x_max + 1.0]
    set yrange [y_min - 1.0 : y_max + 1.0]

    plot './data/in_circle_A.dat' u 1:2 w d title 'Circle A', \
        './data/in_circle_B.dat' u 1:2 w d title 'Circle B'


set terminal qt 1 size 600, 600
    reset
    set tics font "Helvetica, 11"
    set xlabel 'n' font "Helvetica, 12"
    set ylabel 'Common area' font "Helvetica, 12"
    set xrange [10 to 10*N]
    set logscale x
    set format x "10^{%L}"

    plot './data/common_area.dat' with errorbars pt 2 title ''
    unset logscale