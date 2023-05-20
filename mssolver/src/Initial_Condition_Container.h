#pragma once
#include "msconfig/Data.h"
#include <memory>
#include <string_view>

// forward declaration
class Initial_Condition;

// static class declaration
class Initial_Condition_Container
{
public:
  static std::shared_ptr<Initial_Condition> get(const ms::config::Data& problem_data);

private:
  static void create_and_store(const std::string_view KEY, const ms::config::Data& problem_data);

private:
  inline static std::map<std::string, std::shared_ptr<Initial_Condition>> _container;

private:
  // Static class doesn't need to create object.
  // Thus, access to the constructor is restricted to prevent unnecessary creation.
  Initial_Condition_Container(void) = delete;

private:
  using THIS = Initial_Condition_Container;
};
