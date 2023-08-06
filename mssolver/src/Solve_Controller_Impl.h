#pragma once
#include "Solve_Controller.h"

class Solve_End_Controller_By_Time : public Solve_End_Controller
{
public:
  Solve_End_Controller_By_Time(const double end_time) : end_time_(end_time){};

public:
  bool        is_need_to_control_time_step(const double current_time, const double time_step) const override;
  void        control_time_step(const double current_time, double& time_step) const override;
  bool        is_time_to_end(const int current_iter, const double current_time) const override;
  std::string progress_percentage_str(const int current_iter, const double current_time) const override;

private:
  double end_time_ = 0.0;
};

/*








*/

class Solve_End_Controller_By_Iter : public Solve_End_Controller
{
public:
  Solve_End_Controller_By_Iter(const int end_iter) : end_iter_(end_iter){};

public:
  bool        is_need_to_control_time_step(const double current_time, const double time_step) const override;
  void        control_time_step(const double current_time, double& time_step) const override;
  bool        is_time_to_end(const int current_iter, const double current_time) const override;
  std::string progress_percentage_str(const int current_iter, const double current_time) const override;

private:
  int end_iter_ = 0;
};

/*








*/

class Solve_Post_Controller_No_Post : public Solve_Post_Controller
{
public:
  bool is_need_to_control_time_step(const double current_time, const double time_step) const override { return false; };
  void control_time_step(const double current_time, double& time_step) const override{};
  bool is_time_to_post(const int current_iter, const double current_time) const override { return false; };
  bool is_post_initial_solution(void) const override { return false; };
  bool is_post_final_solution(void) const override { return false; };
};

/*








*/

class Solve_Post_Controller_Initial_Final : public Solve_Post_Controller
{
public: // Query
  bool is_need_to_control_time_step(const double current_time, const double time_step) const override { return false; };
  void control_time_step(const double current_time, double& time_step) const override{};
  bool is_time_to_post(const int current_iter, const double current_time) const override { return false; };
  bool is_post_initial_solution(void) const override { return true; };
  bool is_post_final_solution(void) const override { return true; };
};

/*








*/

class Solve_Post_Controller_By_Time : public Solve_Post_Controller
{
public:
  Solve_Post_Controller_By_Time(const double post_time_unit, const bool is_post_initial, const bool is_post_final);

public: // Query
  void control_time_step(const double current_time, double& time_step) const override;
  bool is_time_to_post(const int current_iter, const double current_time) const override;
  bool is_need_to_control_time_step(const double current_time, const double time_step) const override;
  bool is_post_initial_solution(void) const override;
  bool is_post_final_solution(void) const override;

private:
  void update_post_time(void) const;

private:
  bool           _is_post_initiali_solution = false;
  bool           _is_post_final_solution    = false;
  double         _post_time_unit            = 0.0;
  mutable double _post_time                 = 0.0;
};

/*








*/

class Solve_Post_Controller_By_Iter : public Solve_Post_Controller
{
public:
  Solve_Post_Controller_By_Iter(const int post_iter_unit, const bool is_post_initial, const bool is_post_final);

public:
  void control_time_step(const double current_time, double& time_step) const override;
  bool is_time_to_post(const int current_iter, const double current_time) const override;
  bool is_need_to_control_time_step(const double current_time, const double time_step) const override;
  bool is_post_initial_solution(void) const override;
  bool is_post_final_solution(void) const override;

private:
  void update_post_iter(void) const;

private:
  bool        _is_post_initiali_solution = false;
  bool        _is_post_final_solution    = false;
  int         _post_iter_unit            = 0;
  mutable int _post_iter                 = 0;
};