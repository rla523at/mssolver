#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"
#include "mstecplot/Data.h"
#include <string>
#include <vector>

class Discrete_Solution_FVM;

class Post
{
public:
  static void initialize(const ms::config::Data& problem_data, const ms::config::Data& post_data);
  static void write_grid(const ms::grid::Grid& grid);
  static void write_solution(const Discrete_Solution_FVM& solution, const double time);

private:
  inline static bool                                        _is_initialized              = false;
  inline static int                                         _partition_order             = 0;
  inline static bool                                        _is_solution_location_center = false;
  inline static std::vector<std::string>                    _variable_strs;
  inline static std::vector<ms::tecplot::Variable_Location> _var_locations;

  using THIS = Post;
};