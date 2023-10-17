#include "Discrete_Equation.h"
#include "Post.h"
#include "msconfig/Data.h"
#include "msconfig/Reader.h"
#include "msgrid/Grid.h"
#include "msgrid/Grid_Reader_Factory.h"

#include "Semi_Discrete_Equation_Factory.h"
#include "Time_Discrete_Scheme_Container.h"

int main(void)
{
  constexpr auto config_file_path = "rsc/config.dat";

  const auto config_data = ms::config::Reader::read(config_file_path);

  const auto& grid_config_data = config_data.get_data<ms::config::Data>("grid");
  const auto& grid_file_format = grid_config_data.get_data<std::string>("format");
  const auto& grid_file_path   = grid_config_data.get_data<std::string>("path");
  const auto& grid_dimension   = grid_config_data.get_data<int>("dimension");

  const auto grid_reader_ptr = ms::grid::Reader_Factory::make(grid_file_format, grid_dimension);
  auto       grid_data       = grid_reader_ptr->read(grid_file_path);
  const auto grid            = ms::grid::Grid(std::move(grid_data));

  Post::write_grid(grid);

  const auto& problem_data              = config_data.get_data<ms::config::Data>("problem");
  const auto& discretization_data       = config_data.get_data<ms::config::Data>("discretization");
  const auto& time_data                 = discretization_data.get_data<ms::config::Data>("time");
  auto        semi_discrete_eq_uptr     = Semi_Discrete_Equation_Factory::make(problem_data, discretization_data, grid);
  auto        time_discrete_scheme_sptr = Time_Discrete_Scheme_Container::get(time_data);
  auto        discrete_equation         = Discrete_Equation(std::move(semi_discrete_eq_uptr), time_discrete_scheme_sptr);

  const auto& solve_option_data = config_data.get_data<ms::config::Data>("solve_option");
  discrete_equation.solve(solve_option_data);

  // compile error 잡기
  // update residual code 수정하기
}