#include <atomic>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

#include "pong.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using google::protobuf::Empty;
using pong::Pong;

DEFINE_int32(port, 31337, "port to listen on");
DEFINE_string(bind_address, "0.0.0.0", "bind address");

// Logic and data behind the server's behavior.
class PongServiceImpl final : public Pong::Service {
public:
  PongServiceImpl() {}
protected:
  Status
  Pong([[maybe_unused]] ServerContext* context,
       [[maybe_unused]] const Empty*  request,
       [[maybe_unused]] Empty* reply) override {
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address;
  {
    std::ostringstream ss;
    ss << FLAGS_bind_address << ":" << FLAGS_port;
    server_address = ss.str();
  }
  PongServiceImpl service{};
  ServerBuilder builder{};
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials())
    .RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  RunServer();
  return 0;
}
