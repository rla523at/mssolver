#pragma once
class Radii_Calculator
{
public:
  virtual double calculate(const double* projected_volumes, const double* characteristic_velocity) const = 0;
};

class Radii_Calculator_1D : public Radii_Calculator
{
public:
  double calculate(const double* projected_volumes, const double* characteristic_velocity) const;
};

class Radii_Calculator_2D : public Radii_Calculator
{
public:
  double calculate(const double* projected_volumes, const double* characteristic_velocity) const;
};