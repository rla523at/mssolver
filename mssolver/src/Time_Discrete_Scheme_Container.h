#pragma once
#include "msconfig/Data.h"
#include <map>
#include <memory>

// forward declration
class Time_Discrete_Scheme;

// static class delcaration
class Time_Discrete_Scheme_Container
{
public:
  static std::shared_ptr<Time_Discrete_Scheme> get(const ms::config::Data& time_discretization_data);

private:
  static void create_and_store(const std::string_view KEY);

private:
  inline static std::map<std::string, std::shared_ptr<Time_Discrete_Scheme>> _container;

private:
  using THIS = Time_Discrete_Scheme_Container;

private:
  // Static class doesn't need to create object.
  // Thus, access to the constructor is restricted to prevent unnecessary creation.
  Time_Discrete_Scheme_Container(void) = delete;
};