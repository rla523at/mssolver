#include "Governing_Equation_Container.h"

#include "Governing_Equation_Impl.h"
#include "msstring/string.h"

std::shared_ptr<Governing_Equation> Governing_Equation_Container::get(const ms::config::Data& problem_data)
{
  const auto& governing_equation_name = problem_data.get_data<std::string>("governing_equation");
  const auto  KEY                     = ms::string::upper_case(governing_equation_name);

  if (!THIS::_container.contains(KEY)) THIS::create_and_store(KEY, problem_data);

  return THIS::_container.at(KEY);
}

void Governing_Equation_Container::create_and_store(const std::string_view KEY, const ms::config::Data& problem_data)
{
  const auto dimension = problem_data.get_data<int>("dimension");

  if (KEY == "LINEAR_ADVECTION")
  {
    const auto& linear_advection_option = problem_data.get_data<ms::config::Data>("linear_advection_option");

    std::vector<double> advection_velocity(dimension);
    for (int i = 0; i < dimension; ++i)
    {
      advection_velocity[i] = linear_advection_option.get_data<double>("x" + std::to_string(i) + "_advection_speed");
    }

    THIS::_container.emplace(KEY, std::make_unique<Linear_Advection>(advection_velocity.data(), dimension));
  }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supprorted governing equation");
  }
}
