#pragma once
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <iostream>

class LoggerInterceptor final : public grpc::experimental::Interceptor
{
private:
  /* data */
public:
  explicit LoggerInterceptor(grpc::experimental::ServerRpcInfo *info)
  {
    std::string method = info->method();

    if (method == "unknown")
    {
      std::cout<<"Error: Method not found"<< std::endl;
      return;
    }
    std::cout << "Called: " << method << std::endl;
  }

  void Intercept(grpc::experimental::InterceptorBatchMethods *methods) override
  {
    methods->Proceed();
  }

};

class LoggerInterceptorFactory : public grpc::experimental::ServerInterceptorFactoryInterface {
public: 
  grpc::experimental::Interceptor* CreateServerInterceptor(grpc::experimental::ServerRpcInfo *info) override
  {
    return new LoggerInterceptor(info);
  }
};


