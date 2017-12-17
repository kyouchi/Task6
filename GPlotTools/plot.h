#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <complex>

class plot
{
protected:
   std::ofstream writing_file;
   std::ofstream writing_command_file;

   std::vector<double> x;
   std::vector<double> y;
   std::vector<std::complex<double>> y_complex;
   std::string xlabel;
   std::string ylabel;
   std::string graph_title;
   std::string filename;
   std::string command_filename;

   bool printFile();
   bool printFile_abs();
   bool printCommandFile();
   bool printCommandFile_abs();

public:
   plot(std::vector<double> x, std::vector<double> y, std::string xlabel, std::string ylabel, std::string graph_title, std::string Filename, std::string command_filename);
   plot(std::vector<double> x, std::vector<std::complex<double>> y, std::string xlabel, std::string ylabel, std::string graph_title, std::string Filename, std::string command_filename);
   ~plot();

   void executionPlot();
   void executionPlot_abs();
};
