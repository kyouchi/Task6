#include "stdafx.h"
#include "plot.h"
#include <iostream>
#include <algorithm>
#include <cassert>

bool plot::printFile()
{
   std::cout << "plot[Info]:" << filename << "に書き込んでいます。" << std::endl;

   writing_file.open(filename, std::ios::out);
   try
   {
      if (!this->writing_file.is_open()) throw "指定したファイルが開けませんでした。";
      if (this->x.size() != this->y_complex.size()) throw "std::vectorの変数のsizeが違います。";
      if (this->xlabel.empty()) throw "x軸ラベルが無記名です。";
      if (this->ylabel.empty()) throw "y軸ラベルが無記名です。";
      if (this->graph_title.empty()) throw "グラフタイトルが無記名です。";
      if (this->filename.empty()) throw "ファイル名が無記名です。";
   }
   catch (const char* Error)
   {
      std::cout << "plot[Error]:" << Error << std::endl;
      return false;
   }

   //ヘッダーの作成
   writing_file << "# " << xlabel << " " << ylabel << " " << std::endl;

   y.resize(x.size());
   for (auto i = 0; i < x.size(); ++i)
   {
      y[i] = y_complex[i].real();
      writing_file << x[i] << " " << y[i] << std::endl;
   }

   std::cout << "plot[Info]:" << filename << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool plot::printFile_abs()
{
   std::cout << "plot[Info]:" << filename << "に書き込んでいます。" << std::endl;

   writing_file.open(filename, std::ios::out);
   try
   {
      if (!this->writing_file.is_open()) throw "指定したファイルが開けませんでした。";
      if (this->x.size() != this->y_complex.size()) throw "std::vectorの変数のsizeが違います。";
      if (this->xlabel.empty()) throw "x軸ラベルが無記名です。";
      if (this->ylabel.empty()) throw "y軸ラベルが無記名です。";
      if (this->graph_title.empty()) throw "グラフタイトルが無記名です。";
      if (this->filename.empty()) throw "ファイル名が無記名です。";
   }
   catch (const char* Error)
   {
      std::cout << "plot[Error]:" << Error << std::endl;
      return false;
   }

   //ヘッダーの作成
   writing_file << "# " << xlabel << " " << ylabel << " " << std::endl;

   y.resize(x.size());
   for (auto i = 0; i < x.size(); ++i)
   {
      y[i] = abs(y_complex[i]);
      writing_file << x[i] << " " << y[i] << std::endl;
   }

   std::cout << "plot[Info]:" << filename << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool plot::printCommandFile()
{
   std::cout << "plot[Info]:GNU Plot用のコマンドファイルを生成します。" << std::endl;
   std::cout << "plot[Info]:" << command_filename << "に書き込んでいます。" << std::endl;

   writing_command_file.open(command_filename, std::ios::out);
   try
   {
      if (!this->writing_command_file.is_open()) throw "指定したコマンドファイルが開けませんでした。";
      if (this->command_filename.empty()) throw "コマンドファイル名が無記名です。";
   }
   catch (const char* Error)
   {
      std::cout << "plot[Error]:" << Error << std::endl;
      return false;
   }

   //範囲指定
   auto itr = min_element(x.begin(), x.end());
   auto x_min_index = distance(x.begin(), itr);
   itr = max_element(x.begin(), x.end());
   auto x_max_index = distance(x.begin(), itr);
   itr = min_element(y.begin(), y.end());
   auto y_min_index = distance(y.begin(), itr);
   itr = max_element(y.begin(), y.end());
   auto y_max_index = distance(y.begin(), itr);

   writing_command_file << "set encoding utf8" << std::endl;
   writing_command_file << "set xl \"" << xlabel << "\"" << std::endl;
   writing_command_file << "set yl \"" << ylabel << "\"" << std::endl;
   writing_command_file << "set xrange [" << x[x_min_index] << ":" << x[x_max_index] << "]" << std::endl;
   writing_command_file << "set yrange [" << y[y_min_index] << ":" << y[y_max_index] << "]" << std::endl;
   writing_command_file << "set grid" << std::endl;
   writing_command_file << "set title \"" << graph_title << "\"" << std::endl;
   writing_command_file << "plot \"" << filename << "\" " << "with lp" << std::endl;

   std::cout << "plot[Info]:" << command_filename << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool plot::printCommandFile_abs()
{
   std::cout << "plot[Info]:GNU Plot用のコマンドファイルを生成します。" << std::endl;
   std::cout << "plot[Info]:" << command_filename << "に書き込んでいます。" << std::endl;

   writing_command_file.open(command_filename, std::ios::out);
   try
   {
      if (!this->writing_command_file.is_open()) throw "指定したコマンドファイルが開けませんでした。";
      if (this->command_filename.empty()) throw "コマンドファイル名が無記名です。";
   }
   catch (const char* Error)
   {
      std::cout << "plot[Error]:" << Error << std::endl;
      return false;
   }

   //範囲指定
   auto itr = min_element(x.begin(), x.end());
   auto x_min_index = distance(x.begin(), itr);
   itr = max_element(x.begin(), x.end());
   auto x_max_index = distance(x.begin(), itr);
   itr = min_element(y.begin(), y.end());
   auto y_min_index = distance(y.begin(), itr);
   itr = max_element(y.begin(), y.end());
   auto y_max_index = distance(y.begin(), itr);

   writing_command_file << "set encoding utf8" << std::endl;
   writing_command_file << "set xl \"" << xlabel << "\"" << std::endl;
   writing_command_file << "set yl \"" << ylabel << "\"" << std::endl;
   writing_command_file << "set xrange [" << 0 << ":" << x[x_max_index] << "]" << std::endl;
   writing_command_file << "set yrange [" << 0 << ":" << y[y_max_index] << "]" << std::endl;
   writing_command_file << "set grid" << std::endl;
   writing_command_file << "set title \"" << graph_title << "\"" << std::endl;
   writing_command_file << "plot \"" << filename << "\" " << "with lp" << std::endl;

   std::cout << "plot[Info]:" << command_filename << "に書き込みが終わりました。" << std::endl;
   return true;
}

plot::plot(std::vector<double> x, std::vector<double> y, std::string xlabel, std::string ylabel, std::string graph_title, std::string filename, std::string command_filename = "command.bat") : x(x), xlabel(xlabel), ylabel(ylabel), graph_title(graph_title), filename(filename), command_filename(command_filename)
{
   this->y_complex.resize(y.size());
   auto itr = 0;
   for (auto i : y)
   {
      this->y_complex[itr].real(i);
      itr++;
   }
   return;
}

plot::plot(std::vector<double> x, std::vector<std::complex<double>> y, std::string xlabel, std::string ylabel, std::string graph_title, std::string filename, std::string command_filename) : x(x), y_complex(y), xlabel(xlabel), ylabel(ylabel), graph_title(graph_title), filename(filename), command_filename(command_filename)
{
   return;
}

plot::~plot()
{
}

void plot::executionPlot()
{
   auto error = this->printFile();
   assert(error);//"printFile()に失敗"
   error = this->printCommandFile();
   assert(error);// "printcommandFile()に失敗"

   std::cout << "plot[Info]:" << "全ての処理を終了" << std::endl;

   //コマンド用batをwgnuplotで開く
   //auto command = "\"C:\\\\Program Files (x86)\\gnuplot\\bin\\wgnuplot.exe\" -persist " + command_filename;
   //if (system(command.c_str())) std::cout << "plot[Error]:" << command.c_str() << " " << "GNU Plotが開けません。" << std::endl;
}

void plot::executionPlot_abs()
{
   auto error = this->printFile_abs();
   assert(error);//"printFile()に失敗"
   error = this->printCommandFile_abs();
   assert(error);// "printcommandFile()に失敗"

   std::cout << "plot[Info]:" << "全ての処理を終了" << std::endl;

   //コマンド用batをwgnuplotで開く
   //auto command = "\"C:\\\\Program Files (x86)\\gnuplot\\bin\\wgnuplot.exe\" -persist " + command_filename;
   //if (system(command.c_str())) std::cout << "plot[Error]:" << command.c_str() << " " << "GNU Plotが開けません。" << std::endl;
}
