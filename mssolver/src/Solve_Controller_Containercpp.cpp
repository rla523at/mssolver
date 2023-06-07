#include "Solve_Controller_Container.h"

#include "Solve_Controller_Impl.h"
#include "msstring/string.h"

const std::shared_ptr<Solve_End_Controller>& Solve_End_Controller_Container::get_ptr(const ms::config::Data& solve_end_option)
{
  const auto& end_condition = solve_end_option.get_data<std::string>("condition");
  const auto  KEY           = ms::string::upper_case(end_condition);

  if (!THIS::_container.contains(KEY))
  {
    const auto criterion = solve_end_option.get_data<double>("criterion");
    THIS::create_and_store(KEY, criterion);
  }

  return THIS::_container.at(KEY);
}

const Solve_End_Controller& Solve_End_Controller_Container::get(const ms::config::Data& solve_end_option)
{
  return *THIS::get_ptr(solve_end_option);
}

void Solve_End_Controller_Container::create_and_store(const std::string_view KEY, const double criterion)
{
  if (KEY == "TIME")
  {
    THIS::_container.emplace(KEY, std::make_shared<Solve_End_Controller_By_Time>(criterion));

    // auto solve_end_time = configuration.solve_end_time();
    // if (solve_end_time < 0.0)
    //{
    //   const auto initial_condition = Initial_Condition_Factory::make_unique(configuration);
    //   solve_end_time               = initial_condition->target_end_time();

    //  if (solve_end_time < 0.0)
    //  {
    //    EXCEPTION("Initial condition in configuration file does not provide target end time, Please write down solve end time at configuration file");
    //    return nullptr;
    //  }
    //}
  }
  else if (KEY == "ITER")
  {
    THIS::_container.emplace(KEY, std::make_shared<Solve_End_Controller_By_Iter>(criterion));
  }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supported solve end condition");
  }
}
