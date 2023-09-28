#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"
#include "mstecplot/Data.h"
#include <string>
#include <vector>

class Discrete_Solution_FVM;
class Solution_At_Location;
class Solution_Type_Transformer;
class Governing_Equation;

class Post
{
public:
  static void initialize(const ms::config::Data& problem_data, const ms::config::Data& post_data);
  static void write_grid(const ms::grid::Grid& grid);
  static void write_solution(const Discrete_Solution_FVM& solution, const double time);

private:
  static void set_variable_strs(const std::string_view TYPE, const Governing_Equation& governing_equation);

private:
  inline static bool _is_initialized             = false;
  inline static int  _partition_order            = 0;
  inline static bool _is_continuous_display_type = false;

  inline static std::vector<std::string>                    _variable_strs;
  inline static std::vector<ms::tecplot::Variable_Location> _var_locations;
  inline static std::shared_ptr<Solution_At_Location>       _solution_at_location_sptr;
  inline static std::shared_ptr<Solution_Type_Transformer>  _solution_type_transformer_sptr;

  using THIS = Post;
};