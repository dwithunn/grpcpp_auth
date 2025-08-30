#include <iostream>
#include <service/listener.hpp>

int main()
{
  std::unique_ptr<listener> listen;
  try
  {
    listen->Start();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

  std::cout << "Build Success!" << std::endl;
  return 0;
}
