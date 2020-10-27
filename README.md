# Skeleton BUILD configs for C++ distributed systems libs

`bazel build :all`

This is a test bed to evaluate and experiment with bazel build rules and
skeleton/example code for various C++ distributed systems tools and frameworks.
Contents:

  - `grpc`
  - `uWebSockets`
  - an `etcd` v3 client
  - nlohmann's `json` lib (sample code TODO)
  - Microsoft `cpprest` (sample code TODO)
  - `boost`
  - `OpenSSL`
  - `gflags`

## Notes/Status

  - had to swap `OpenSSL` in place of `boringssl` because one of the web server
    libraries uses it

  - `etcd-cpp-apiv3` required a patch to its proto files to get it working; I
    couldn't get the cmake build to work either due to a conflict with `absl` &
    `endian.h`
