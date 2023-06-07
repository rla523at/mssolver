#pragma once
#include "msconfig/Data.h"
#include <map>
#include <memory>

class Solve_End_Controller;

class Solve_End_Controller_Container
{
public:
  static const Solve_End_Controller&                  get(const ms::config::Data& solve_end_option);
  static const std::shared_ptr<Solve_End_Controller>& get_ptr(const ms::config::Data& solve_end_option);

private:
  static void create_and_store(const std::string_view KEY, const double criterion);

private:
  inline static std::map<std::string, std::shared_ptr<Solve_End_Controller>> _container;

private:
  Solve_End_Controller_Container(void) = delete;

  using THIS = Solve_End_Controller_Container;
};