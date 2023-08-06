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

/*









*/

class Solve_Post_Controller;

class Solve_Post_Controller_Container // static class
{
public:
  static const Solve_Post_Controller&                  get(const ms::config::Data& solve_post_option);
  static const std::shared_ptr<Solve_Post_Controller>& get_ptr(const ms::config::Data& solve_post_option);

private:
  static void create_and_store(const std::string_view KEY, const ms::config::Data& solve_post_option);

private:
  inline static std::map<std::string, std::shared_ptr<Solve_Post_Controller>> _container;

private:
  Solve_Post_Controller_Container(void) = delete;

  using THIS = Solve_Post_Controller_Container;
};