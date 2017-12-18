set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:8190]
set yrange [0:2047]
set grid
set title "Apply FFT"
plot "spectrum3-2.plt" with lp
