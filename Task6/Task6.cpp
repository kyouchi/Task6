// Task4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <memory>
#include "../GPlotTools/plot.h"
#include <iostream>
#include "../FFT/fft.h"
#include "../generateWaveHelper/generateWave.h"

constexpr double getSignal(const double t)
{
   auto output = 0.0;
   if (0 <= t || t <= 0.05) output = 20 * t;
   else if (0.1 <= t || t <= 0.15) output = 3 - 20 * t;
   else output = 0;
   return output;
}

int main()
{
   constexpr auto a = 1.0;
   constexpr auto fs = 8192;//サンプリング周波数(2のべき乗)
   constexpr auto k = 1.0;

   //情報信号
   GenerateWave graph1(fs, 0.5);
   graph1.generateTriangle(0.15, 1.5);
   graph1.generateSquare(0.05, 0.0);
   graph1.moveAmplitude(0.075);
   plot(graph1.getGraph().x, graph1.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform1.plt", "command1.bat").executionPlot();

   //搬送波
   GenerateWave graph2(fs, 0.5);
   graph2.generateCarrierWave(500, 1);
   plot(graph2.getGraph().x, graph2.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform2.plt", "command2.bat").executionPlot();

   //AM変調波
   auto graph3 = (graph1*k)*graph2+graph2;
   plot(graph3.getGraph().x, graph3.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform3.plt", "command3.bat").executionPlot();

   return 0;
}
