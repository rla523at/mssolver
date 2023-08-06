#pragma once
#include "Time_Discrete_Scheme.h"

class Time_Discrete_Scheme_Container;

class Euler_Explicit : public Time_Discrete_Scheme
{
public:
  void update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const override;
};

//class SSPRK33 : public Time_Discrete_Scheme
//{
//public:
//  void update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const override;
//
//private:
//  friend Time_Discrete_Scheme_Container;
//
//private:
//  // Time_Discrete_Scheme objects can be created only once in the Container class.
//  // To prevent unnecessary creation, acess to the constructor has been blocked
//  SSPRK33(void) = default;
//};
//
//class SSPRK54 : public Time_Discrete_Scheme
//{
//public:
//  void update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const override;
//
//private:
//  friend Time_Discrete_Scheme_Container;
//
//private:
//  // Time_Discrete_Scheme objects can be created only once in the Container class.
//  // To prevent unnecessary creation, acess to the constructor has been blocked
//  SSPRK54(void) = default;
//};