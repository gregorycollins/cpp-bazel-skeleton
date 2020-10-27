#include <cinttypes>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "etcd/Client.hpp"
#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

DEFINE_int32(remote_port, 2379, "remote port");
DEFINE_string(remote_address, "127.0.0.1", "remote address");

class Incrementer {
public:
  Incrementer(const std::string& url, std::string k = "counter0")
    : client_(url), key_(std::move(k)) {}

  void increment() {
    while (true) {
      auto r = client_.get(key_).get();
      if (r.is_ok()) {
        int idx = r.index();
        uint64_t v = std::stoull(r.value().as_string());
        std::string vv = std::to_string(v + 1);
        auto r2 = client_.modify_if(key_, vv, idx).get();
        if (r2.is_ok()) {
          std::cout << "successfully wrote " << vv << "\n";
          return;
        } else {
          if (r2.error_code() != TEST_FAILED) fail(r2);
        }
      } else {
        if (r.error_code() != NOT_FOUND) fail(r);
        auto r2 = client_.add(key_, "0").get();
        if (r2.is_ok()) {
          std::cout << "successfully wrote 0\n";
          return;
        }
        if (r2.error_code() != EXISTS) fail(r2);
      }
      std::cout << "concurrent modification, retrying\n";
    }
  }

private:
  static constexpr int NOT_FOUND = 100;
  static constexpr int TEST_FAILED = 101;
  static constexpr int EXISTS = 105;

  void fail(etcd::Response& r) {
    throw std::runtime_error(r.error_message());
  }

  etcd::Client client_;
  std::string key_;
};

static std::string mk_url() {
  std::ostringstream ss;
  ss << "http://" << FLAGS_remote_address
     << ":" << FLAGS_remote_port;
  return ss.str();
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::string server_address = mk_url();
  std::cout << "Client querying server address: " << server_address << std::endl;

  Incrementer client(server_address);
  for (int i = 0; i < 100; i++) {
    client.increment();
  }

  std::cout << "Done\n";
  return 0;
}
