#include "Solution_At_Location_Container.h"

#include "Solution_At_Location_Impl.h"
#include "msstring/string.h"

const Solution_At_Location& Solution_At_Location_Container::get(const std::string_view location)
{
  return *THIS::get_sptr(location);
}

const std::shared_ptr<Solution_At_Location>& Solution_At_Location_Container::get_sptr(const std::string_view location)
{
  const auto KEY = ms::string::upper_case(location);

  if (!THIS::_container.contains(KEY))
  {
    THIS::create_and_store(KEY);
  }

  return THIS::_container.at(KEY);
}

void Solution_At_Location_Container::create_and_store(const std::string_view KEY)
{
  if (KEY == "CENTER")
  {
    THIS::_container.emplace(KEY, std::make_shared<Solution_At_Center>());
  }
  else if (KEY == "NODE")
  {
    THIS::_container.emplace(KEY, std::make_shared<Solution_At_Node>());
  }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supported solution location");
  }
}
