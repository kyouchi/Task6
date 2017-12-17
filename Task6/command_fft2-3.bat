set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:4095]
set yrange [0:2088.08]
set grid
set title "Apply FFT"
plot "spectrum2-3.plt" with lp
