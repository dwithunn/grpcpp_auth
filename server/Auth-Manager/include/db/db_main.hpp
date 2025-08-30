#include <pqxx/pqxx>
#include <iostream>

namespace db
{
  class main
  {
  
  private:
    /* data */
  public:
    std::unique_ptr<pqxx::connection> cx;
    bool connect();
  };
  
} // namespace db

  
