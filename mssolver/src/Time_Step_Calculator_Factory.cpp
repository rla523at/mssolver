#include "Time_Step_Calculator_Factory.h"

#include "Time_Step_Calculator_Impl.h"
#include "msstring/string.h"

std::unique_ptr<Time_Step_Calculator> Time_Step_Calculator_Factory::make_unique(const ms::config::Data& Time_data, const ms::grid::Grid& grid)
{
  const auto& time_step_type      = Time_data.get_data<std::string>("step_type");
  const auto  time_step_criterion = Time_data.get_data<double>("time_step_criterion");

  if (ms::string::contain_icase(time_step_type, "CFL"))
  {
    return std::make_unique<CFL>(time_step_criterion, grid);
  }
  else if (ms::string::contain_icase(time_step_type, "Constant", "dt"))
  {
    return std::make_unique<Constant_Dt>(time_step_criterion);
  }
  else
  {
    EXCEPTION(time_step_type + " in configuration file is not supported time step type");
    return nullptr;
  }
}