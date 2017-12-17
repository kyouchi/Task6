set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:4095]
set yrange [0:2047]
set grid
set title "Apply FFT"
plot "spectrum1-2.plt" with lp
