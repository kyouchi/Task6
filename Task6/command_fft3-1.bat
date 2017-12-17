set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:4095]
set yrange [0:410.2]
set grid
set title "Apply FFT"
plot "spectrum3-1.plt" with lp
