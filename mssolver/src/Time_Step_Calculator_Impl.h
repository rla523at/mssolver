#pragma once
#include "Radii_Calculator.h"
#include "Time_Step_Calculator.h"

class CFL : public Time_Step_Calculator
{
public:
  CFL(const double cfl, const ms::grid::Grid& grid);

public:
  double calculate(const ms::math::Vector_View characteristic_velocity_vec, const int cell_number) const override;

private:
  double                            _CFL;
  std::vector<double>               _cell_number_to_volume;
  std::vector<std::vector<double>>  _cell_number_to_projected_volumes;
  std::unique_ptr<Radii_Calculator> _radii_calculator;
};

class Constant_Dt : public Time_Step_Calculator
{
public:
  Constant_Dt(const double constant_dt) : constant_dt_(constant_dt){};

public:
  double calculate(const ms::math::Vector_View characteristic_velocity_vec, const int cell_number) const override;

  //double calculate(const std::vector<ms::math::Vector_View>& cell_number_to_coordinate_projected_maximum_lambdas) const override;

private:
  double constant_dt_;
};
