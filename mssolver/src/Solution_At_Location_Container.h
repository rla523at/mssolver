#pragma once
#include <map>
#include <memory>
#include <string_view>

class Solution_At_Location;

class Solution_At_Location_Container
{
public:
  Solution_At_Location_Container(void) = delete;

public:
  static const Solution_At_Location&                  get(const std::string_view location);
  static const std::shared_ptr<Solution_At_Location>& get_sptr(const std::string_view location);

private:
  static void create_and_store(const std::string_view KEY);

private:
  inline static std::map<std::string, std::shared_ptr<Solution_At_Location>> _container;

private:
  using THIS = Solution_At_Location_Container;
};