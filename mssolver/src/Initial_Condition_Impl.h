#pragma once
#include "Initial_Condition.h"

#include <vector>

class Constant1 : public Initial_Condition
{
public:
  void calculate_solution(double* solution, const double* coordinates) const override;
};

class Sine_Wave : public Initial_Condition
{
public:
  Sine_Wave(const double* wave_lengths, const int dimension);

public:
  void calculate_solution(double* solution, const double* coordinates) const override;

private:
  int                 _dimension = 0;
  std::vector<double> _wave_numbers; // sin(kx)sin(ky)sin(kz)
};

// class Square_Wave : public Initial_Condition
//{
// public:
//   Square_Wave(const ushort space_dimension)
//       : space_dimension_(space_dimension){};
//
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//
// protected:
//   ushort space_dimension_ = 0;
// };
//
// class Circle_Wave : public Initial_Condition
//{
// public:
//   Circle_Wave(const ushort space_dimension);
//
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//
// private:
//   ushort           space_dimension_ = 0;
//   Euclidean_Vector center_v_;
// };
//
// class Gaussian_Wave : public Initial_Condition
//{
// public:
//   Gaussian_Wave(const ushort space_dimension);
//
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//
// private:
//   ushort           space_dimension_ = 0;
//   Euclidean_Vector center_v_;
// };

// class Euler_Shocktube_2D
//{
// protected:
//   Euclidean_Vector primitive_to_conservative(const Euclidean_Vector& primitive_variable) const;
// };
//
// class Euler_Shocktube_3D
//{
// protected:
//   Euclidean_Vector primitive_to_conservative(const Euclidean_Vector& primitive_variable) const;
// };
//
// class SOD_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class SOD_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class Modified_SOD_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.2; };
// };
//
// class Modified_SOD_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.2; };
// };
//
// class Supersonic_Expansion_2D : public Initial_Condition
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.15; };
// };
//
// class Supersonic_Expansion_3D : public Initial_Condition
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.15; };
// };
//
// class Left_Half_Blast_Wave_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.012; };
// };
//
// class Left_Half_Blast_Wave_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.012; };
// };
//
// class Double_Strong_Shock_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.035; };
// };
//
// class Double_Strong_Shock_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.035; };
// };
//
// class Slowly_Moving_Contact_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.012; };
// };
//
// class Slowly_Moving_Contact_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.012; };
// };
//
// class Harten_Lax_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class Harten_Lax_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class Shu_Osher_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.178; };
// };
//
// class Shu_Osher_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.178; };
// };
//
// class Blast_Wave_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.038; };
// };
//
// class Blast_Wave_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 0.038; };
// };
//
// class Leblanc_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
//   constexpr double target_end_time(void) const override { return 6.0; };
// };
//
// class Explosion_2D : public Initial_Condition, Euler_Shocktube_2D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class Explosion_3D : public Initial_Condition, Euler_Shocktube_3D
//{
// public:
//   Euclidean_Vector calculate_solution(const Euclidean_Vector& space_vector) const override;
// };
//
// class Initial_Condition_Factory // static class
//{
// public:
//   static std::unique_ptr<Initial_Condition> make_unique(const Configuration& configuration);
// };