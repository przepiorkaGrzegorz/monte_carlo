reset
k = 20
N = 1E06
max = 10.0
min = 0.0
width = (max - min)
bin_size = width/k;
norm = 1.0/(bin_size * N)

set xlabel 'x' font "Helvetica, 12"
set ylabel 'f(x)' font "Helvetica, 12"
set tics font "Helvetica, 11"
set key font ", 11"


#probability_density
f(x) = 0.8 * (1.0 + x - x**3)


set terminal qt 1 size 800, 600
set multiplot layout 1, 2 rows scale 0.9, 0.9
### Subplot 1 ###

    hist(x, bin_size) = bin_size*floor(x/bin_size) + bin_size/2.0
    set xrange [min:max]
    # set yrange [0.8:]
    set title "markov-chain" font "Helvetica, 12"

    set xtics min, (max - min)/5, max
    set boxwidth bin_size*0.9
    set style fill solid 0.5
    set tics out nomirror

    plot "./data/markov_chain.dat" u (hist($1, bin_size)):(1.0*norm) \
        smooth freq w boxes lc rgb"green" notitle, f(x) w lines lt rgb 'red' title "pdf"


### Subplot 2 ###

    hist(x, bin_size) = bin_size*floor(x/bin_size) + bin_size/2.0
    set xrange [min:max]
    # set yrange [0.8:]
    set title "acception-rejection" font "Helvetica, 12"

    set xtics min, (max - min)/5, max
    set boxwidth bin_size*0.9
    set style fill solid 0.5
    set tics out nomirror

    plot "./data/acception_rejection.dat" u (hist($1, bin_size)):(1.0*norm) \
        smooth freq w boxes lc rgb"green" notitle, f(x) w lines lt rgb 'red' title "pdf"

unset multiplot