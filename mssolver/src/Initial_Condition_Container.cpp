#include "Initial_Condition_Container.h"

#include "Initial_Condition_Impl.h"
#include "msstring/string.h"

std::shared_ptr<Initial_Condition> Initial_Condition_Container::get(const ms::config::Data& problem_data)
{
  const auto& intial_condition_name = problem_data.get_data<std::string>("intial_condition");
  const auto  dimension             = problem_data.get_data<int>("dimension");
  const auto  KEY                   = ms::string::upper_case(intial_condition_name);

  if (!THIS::_container.contains(KEY))
  {
    THIS::create_and_store(KEY, problem_data);
  }

  return THIS::_container.at(KEY);
}

void Initial_Condition_Container::create_and_store(const std::string_view KEY, const ms::config::Data& problem_data)
{
  const auto& intial_condition_name = problem_data.get_data<std::string>("intial_condition");

  if (KEY == "CONSTANT1")
  {
    THIS::_container.emplace(KEY, std::make_shared<Constant1>());
  }
  else if (KEY == "SINE_WAVE")
  {
    const auto  dimension        = problem_data.get_data<int>("dimension");
    const auto& sine_wave_option = problem_data.get_data<ms::config::Data>("sine_wave_option");

    std::vector<double> wave_length(dimension);
    for (int i = 0; i < dimension; ++i)
    {
      wave_length[i] = sine_wave_option.get_data<double>("x" + std::to_string(i) + "_wave_length");
    }

    THIS::_container.emplace(KEY, std::make_shared<Sine_Wave>(wave_length.data(), dimension));
  }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supprorted initial condition");
  }
}
