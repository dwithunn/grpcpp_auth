#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>
#include "Auth.grpc.pb.h"
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/security/server_credentials.h>
#include "Auth.pb.h"
#include "interceptors/logger.hpp"

class listener
{
private:
  std::string service_address_;
  std::string service_name_;
  std::unique_ptr<grpc::Server> listener_;
  std::shared_ptr<grpc::Service> service_;
  std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>> interceptor_creator;

public:
  explicit listener(const std::string &svr_adr,const std::shared_ptr<grpc::Service> service = nullptr,std::string service_name = "AuthManager");
  void Start();
  void Stop();

};

