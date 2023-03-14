reset
k = 10 #number of intervals
max = 1. #max value
min = 0. #min value
width = (max - min)/k #interval width
norm = k/1E6

#prob_density
f(x) = 0.8 * (1 + x - x**3)

#////////////////////////////////////////////////////////////////////////////////////
# PLOT 1

#function used to map a value to the intervals
    hist(x,width)=width*floor(x/width)+width/2.0
    set term png #output terminal and file
    set output "compositeHist.png"
    set xrange [min:max]
    set yrange [0.8:]

#to put an empty boundary around the
#data inside an autoscaled graph.
    set offset graph 0.05, 0.05, 0.05, 0.0
    set xtics min,(max-min)/5,max
    set boxwidth width*0.9
    set style fill solid 0.5 #fillstyle
    set tics out nomirror
    set xlabel "x"
    set ylabel "P"

#count and plot (1.0*norm)
    plot "composite.txt" u (hist($1,width)):(1.0*norm) smooth freq w boxes lc rgb"green" notitle, \
    f(x) with lines lt rgb 'red'

#////////////////////////////////////////////////////////////////////////////////////
# PLOT 2

#function used to map a value to the intervals
    hist(x,width)=width*floor(x/width)+width/2.0
    set term png #output terminal and file
    set output "markovHist.png"
    set xrange [min:max]
    set yrange [0.8:]

#to put an empty boundary around the
#data inside an autoscaled graph.
    set offset graph 0.05, 0.05, 0.05, 0.0
    set xtics min,(max-min)/5,max
    set boxwidth width*0.9
    set style fill solid 0.5 #fillstyle
    set tics out nomirror
    set xlabel "x"
    set ylabel "P"

#count and plot (1.0*norm)
    plot "markov.txt" u (hist($1,width)):(1.0*norm) smooth freq w boxes lc rgb"green" notitle, \
    f(x) with lines lt rgb 'red'

#////////////////////////////////////////////////////////////////////////////////////
# PLOT 3

#function used to map a value to the intervals
    hist(x,width)=width*floor(x/width)+width/2.0
    set term png #output terminal and file
    set output "rejectHist.png"
    set xrange [min:max]
    set yrange [0.8:]

#to put an empty boundary around the
#data inside an autoscaled graph.
    set offset graph 0.05, 0.05, 0.05, 0.0
    set xtics min,(max-min)/5,max
    set boxwidth width*0.9
    set style fill solid 0.5 #fillstyle
    set tics out nomirror
    set xlabel "x"
    set ylabel "P"

#count and plot (1.0*norm)
    plot "reject.txt" u (hist($1,width)):(1.0*norm) smooth freq w boxes lc rgb"green" notitle, \
    f(x) with lines lt rgb 'red'