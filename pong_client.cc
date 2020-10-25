#include <cinttypes>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

#include "pong.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using pong::Pong;
using google::protobuf::Empty;

DEFINE_int32(remote_port, 31337, "remote port");
DEFINE_string(remote_address, "127.0.0.1", "remote address");

class PongClient {
 public:
  PongClient(std::shared_ptr<Channel> channel)
    : stub_(Pong::NewStub(std::move(channel))) {}

  void Pong() {
    Empty request;
    Empty response;
    ClientContext context;
    Status status = stub_->Pong(&context, request, &response);
    if (!status.ok()) {
      std::ostringstream oss;
      oss << "Error received from server (code="
          << status.error_code() << "): " << status.error_message()
          << std::endl;
      std::cerr << oss.str();
      throw std::runtime_error(oss.str());
    }
  }

 private:
  std::unique_ptr<Pong::Stub> stub_;
};

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::string server_address;
  {
    std::ostringstream ss;
    ss << FLAGS_remote_address << ":" << FLAGS_remote_port;
    server_address = ss.str();
  }
  std::cout << "Client querying server address: " << server_address << std::endl;


  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  PongClient pong(grpc::CreateChannel(
      server_address, grpc::InsecureChannelCredentials()));

  pong.Pong();
  std::cout << "Pong received\n";
  return 0;
}
