#include "stdafx.h"
#include "generateWave.h"
#include "../FFT/fft.h"
#include <cassert>
#include <thread>

Graph::Graph(const std::vector<double> x, const std::vector<std::complex<double>> y) : x(x), y(y)
{
}

Graph::Graph(const Graph& obj)
{
   //まずは領域を確保(必要のない気もするが)
   this->x.resize(obj.x.size());
   this->y.resize(obj.y.size());

   //要素コピーを実施
   std::copy(obj.x.begin(), obj.x.end(), this->x.begin());
   std::copy(obj.y.begin(), obj.y.end(), this->y.begin());
}

Graph Graph::operator+(Graph gw) const
{
   if (this->x.size() != gw.x.size() || this->y.size() != gw.y.size() || this->x.size() != gw.y.size() || this->y.size() != gw.x.size())
   {
      //xのサイズが違う
      assert(this->x.size() != gw.x.size());
      //yのサイズが違う
      assert(this->y.size() != gw.y.size());

      //xとyでサイズが違う
      assert(this->x.size() != gw.y.size());
      assert(this->y.size() != gw.x.size());
   }

   const auto size = this->x.size();
   //コピーを作成
   auto new_gw = *this;

   for (unsigned int i = 0; i < size; ++i)
   {
      new_gw.y[i] = new_gw.y[i] + gw.y[i];
   }

   return new_gw;
}

GenerateWave::GenerateWave(const double fs, const double sec) : fs_(fs), sec_(sec)
{
   t_.resize(static_cast<unsigned>(sec * fs));
   v_.assign(static_cast<unsigned>(sec * fs), 0.0);//0で初期化
}

GenerateWave::~GenerateWave()
{
}

GenerateWave::GenerateWave(const GenerateWave &obj) : fs_(obj.fs_), sec_(obj.sec_)
{
   //まずは領域を確保(必要のない気もするが)
   this->t_.resize(obj.t_.size());
   this->v_.resize(obj.v_.size());
   this->output_frequence_.resize(obj.output_frequence_.size());
   this->output_amplitude_.resize(obj.output_amplitude_.size());

   //要素コピーを実施
   std::copy(obj.t_.begin(), obj.t_.end(), this->t_.begin());
   std::copy(obj.v_.begin(), obj.v_.end(), this->v_.begin());
   std::copy(obj.output_frequence_.begin(), obj.output_frequence_.end(), this->output_frequence_.begin());
   std::copy(obj.output_amplitude_.begin(), obj.output_amplitude_.end(), this->output_amplitude_.begin());
}

Graph GenerateWave::generateSquare(const double tau, const double a)
{
   const auto all_sum_point = (sec_ * fs_);
   const auto center_point = all_sum_point / 2.0;
   const auto range = (fs_ * (tau / 2.0));

   std::thread thread1([&] {
      for (auto i = static_cast<unsigned>(center_point); i < all_sum_point; ++i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point + range > i)
         {
            v_[i] = a;
         }
      }
   });
   std::thread thread2([&] {
      for (auto i = static_cast<unsigned>(center_point -1); i > 0; --i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point - range < i)
         {
            v_[i] = a;
         }
      }
   });
   thread1.join();
   thread2.join();
   return {t_,v_};
}

Graph GenerateWave::generateTriangle(const double tau, const double a)
{
   const auto all_sum_point = (sec_ * fs_);
   const auto center_point = all_sum_point / 2.0;
   const auto range = (fs_ * (tau / 2.0));

   std::thread thread1([&] {
      for (auto i = static_cast<unsigned>(center_point); i < all_sum_point; ++i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point + range > i)
         {
            v_[i] = a - (a / ((tau / 2.0) * fs_)) * (i - center_point);
         }
      }
   });
   std::thread thread2([&] {
      for (auto i = static_cast<unsigned>(center_point - 1); i > 0; --i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point - range < i)
         {
            v_[i] = a + (a / ((tau / 2.0) * fs_)) * (i - center_point);
         }
      }
   });
   thread1.join();
   thread2.join();
   return {t_,v_};
}

Graph GenerateWave::generateCosineWave(const double tau, const double a, const double cycle)
{
   const auto all_sum_point = (sec_ * fs_);
   const auto center_point = all_sum_point / 2.0;
   const auto range = (fs_ * (tau / 2.0));

   std::thread thread1([&] {
      for (auto i = static_cast<unsigned>(center_point); i < all_sum_point; ++i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point + range > i)
         {
            v_[i] = a * std::cos(cycle * pi * t_[i]);//Cosineを乗算
         }
      }
   });
   std::thread thread2([&] {
      for (auto i = static_cast<unsigned>(center_point - 1); i > 0; --i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point - range < i)
         {
            v_[i] = a * std::cos(cycle * pi * t_[i]);//Cosineを乗算
         }
      }
   });
   thread1.join();
   thread2.join();
   return {t_,v_};
}

Graph GenerateWave::generateCarrierWave(const double fc, const double a)
{
   const auto all_sum_point = (sec_ * fs_);
   const auto center_point = all_sum_point / 2.0;

   std::thread thread1([&] {
      for (auto i = static_cast<unsigned>(center_point); i < all_sum_point; ++i)
      {
         t_[i] = (i - center_point) / fs_;
         v_[i] = a * std::cos(2 * pi * fc * t_[i]);//Cosineを乗算
      }
   });
   std::thread thread2([&] {
      for (auto i = static_cast<unsigned>(center_point - 1); i > 0; --i)
      {
         t_[i] = (i - center_point) / fs_;
         v_[i] = a * std::cos(2 * pi * fc * t_[i]);//Cosineを乗算
      }
   });
   thread1.join();
   thread2.join();
   return {t_,v_};
}

Graph GenerateWave::generatePow2CosineWave(const double tau, const double a, const double cycle)
{
   const auto all_sum_point = (sec_ * fs_);
   const auto center_point = all_sum_point / 2.0;
   const auto range = (fs_ * (tau / 2.0));

   std::thread thread1([&] {
      for (auto i = static_cast<unsigned>(center_point); i < all_sum_point; ++i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point + range > i)
         {
            v_[i] = a * std::cos(cycle * pi * t_[i]) * std::cos(cycle * pi * t_[i]);//Cosineを乗算
         }
      }
   });
   std::thread thread2([&] {
      for (auto i = static_cast<unsigned>(center_point - 1); i > 0; --i)
      {
         t_[i] = (i - center_point) / fs_;
         if (center_point - range < i)
         {
            v_[i] = a * std::cos(cycle * pi * t_[i]) * std::cos(cycle * pi * t_[i]);//Cosineを乗算
         }
      }
   });
   return {t_,v_};
}

Graph GenerateWave::generatePrbsWave(const double ft, const std::vector<double> list,
                                     const std::function<Graph(double, double)> fn)
{
   //一つのstd::complexのサイズはftである。
   std::vector<Graph> prbs;
   for (auto date : list)
   {
      prbs.push_back(fn(ft, date));
   }

   const auto all_sum_point = (sec_ * fs_);
   //const auto all_prbs_sum_point = ft * prbs.size();
   //const auto diff_point = (all_sum_point - all_prbs_sum_point) / 2;//ずれる距離(Sample点)
   //const auto center_point = all_sum_point / 2.0;

   auto index = 0;
   auto itr = prbs.begin();
   for (auto i = 0; i < all_sum_point; ++i)
   {
      if (itr == prbs.end()) __asm int 3;//TODO: センタリング実装
      if (ft == index)
      {
         index = 0;
         ++itr;
      }
      t_[i] = (*itr).x[index];
      v_[i] = (*itr).y[index];
      ++index;
   }
   return {t_,v_};
}

Graph GenerateWave::getGraph() const
{
   return { this->t_,this->v_ };
}

std::vector<std::complex<double>> GenerateWave::getWaveData() const
{
   return v_;
}

bool GenerateWave::setWaveData(std::vector<std::complex<double>>* p_v)
{
   if (p_v->size() == this->t_.size())
   {
      this->v_ = *p_v;
   }
   else
   {
      //サイズが異なっている為、整合性が保たれない。
      assert(p_v->size() == this->t_.size());
      return false;
   }
   return true;
}

Graph GenerateWave::moveAmplitude(const double move_time)
{
   if (-(this->sec_ / 2) >= move_time || move_time >= this->sec_ / 2)
   {
      //開始時間が範囲外
      assert(move_time <= this->sec_ / 2);
      assert(-(this->sec_ / 2) <= move_time);
   }

   const auto range = (fs_ * move_time);
   for (auto i = 0; i < range; ++i)
   {
      v_.insert(v_.begin(), v_.back());//末端を先端にコピー
      v_.pop_back();//末端を削除
   }
   return {t_,v_};
}

GenerateWave GenerateWave::operator+(GenerateWave gw) const
{
   const auto size = this->v_.size();

   if (size != gw.v_.size() || this->sec_ != gw.sec_ || this->fs_ != gw.fs_)
   {
      //範囲時間が違う
      assert(this->sec_ != gw.sec_);
      //サンプリング周波数が違う
      assert(this->fs_ != gw.fs_);
   }

   //コピーを作成
   auto new_gw = *this;

   for (unsigned int i = 0; i < size; ++i)
   {
      new_gw.v_[i] = new_gw.v_[i] + gw.v_[i];
   }

   return new_gw;
}


Graph GenerateWave::applyFft()
{
   std::vector<int> ids;
   const auto n_level = lc_fft_calc_ids(static_cast<int>(fs_ * sec_), &ids);// FFT事前計算
   lc_fft(v_, ids, n_level, &output_amplitude_);// FFT変換

   output_frequence_.resize(output_amplitude_.size());
   for (unsigned int i = 0; i < output_frequence_.size(); ++i)output_frequence_[i] = (static_cast<double>(i) / sec_);
   return {output_frequence_,output_amplitude_};
}
