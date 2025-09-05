#include <iostream>
#include <memory>
#include <service/listener.hpp>
#include <service/auth.hpp>

int main()
{
  try
  {
    auto service = std::make_shared<Authenticator::Login_Validator>();

    listener server("0.0.0.0:50051", service, "AuthService");
    server.Start();

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

  std::cout << "Build Success!" << std::endl;
  return 0;
}
