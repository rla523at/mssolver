#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"

class Post
{
public:
  static void initialize(const ms::config::Data& post_data);
  static void write_grid(const ms::grid::Grid& grid);

private:
  inline static bool _is_initialized         = false;
  inline static int  _partition_order        = 0;
  inline static bool _is_solution_location_center = false;

  using THIS = Post;
};