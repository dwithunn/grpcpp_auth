#include "service/listener.hpp"

listener::listener(const std::string &svr_adr,const std::shared_ptr<grpc::Service> service, std::string service_name) 
  : service_address_(svr_adr), service_(service), service_name_(service_name)
{
  this->interceptor_creator.emplace_back(std::make_unique<LoggerInterceptorFactory>());
}

void listener::Start(){
  grpc::ServerBuilder builder;
  builder.AddListeningPort(this->service_address_, grpc::InsecureServerCredentials());
  builder.RegisterService(this->service_.get());
  builder.experimental().SetInterceptorCreators(std::move(this->interceptor_creator));
  this->listener_ = builder.BuildAndStart();
  std::cout << this->service_name_ << " is listening on " << this->service_address_ << std::endl;
  this->listener_->Wait();
}