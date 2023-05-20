#pragma once
#include <memory>
#include "msconfig/Data.h"
#include "msgrid/Grid.h"

class Time_Step_Calculator;

class Time_Step_Calculator_Factory
{
public:
  static std::unique_ptr<Time_Step_Calculator> make_unique(const ms::config::Data& Time_data, const ms::grid::Grid& grid);
};