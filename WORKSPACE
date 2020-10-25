# -*- bazel -*-

#-----------------------------------------------------------------------------
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

#-----------------------------------------------------------------------------
##### gRPC Rules for Bazel
##### See https://github.com/grpc/grpc/blob/master/src/cpp/README.md#make
#-----------------------------------------------------------------------------
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/v1.31.1.tar.gz",
    ],
    sha256 = "f20f92a09f7245e2c437fbd729849ffe3b2dd39a46c9378d201f8f95cc9f12ea",
    strip_prefix = "grpc-1.31.1",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

#-----------------------------------------------------------------------------
# gflags
#-----------------------------------------------------------------------------
git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tags = ["v2.2.2"]
)

#-----------------------------------------------------------------------------
# json
#-----------------------------------------------------------------------------
new_git_repository (
  name = "github_nlohmann_json",
  remote = "https://github.com/nlohmann/json.git",
  tag = "v3.9.1",
  build_file = "third_party/json.BUILD",
)

bind (
  name = "json",
  actual = "@github_nlohmann_json//:main",
)

#-----------------------------------------------------------------------------
# foreign make/cmake
#-----------------------------------------------------------------------------
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Rule repository
http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-master",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()


#-----------------------------------------------------------------------------
# http
#-----------------------------------------------------------------------------
http_archive(
    name = "github_unetworking_usockets",
    build_file_content = all_content,
    strip_prefix = "uSockets-master",
    urls = ["https://github.com/uNetworking/uSockets/archive/master.tar.gz"],
)
http_archive(
    name = "github_unetworking_uwebsockets",
    strip_prefix = "uWebSockets-18.15.0",
    urls = ["https://github.com/uNetworking/uWebSockets/archive/v18.15.0.tar.gz"],
    build_file = "@//:third_party/uWebSockets.BUILD",
)

#-----------------------------------------------------------------------------
# openssl
#-----------------------------------------------------------------------------

http_archive(
    name = "openssl",
    build_file_content = all_content,
    strip_prefix = "openssl-OpenSSL_1_1_1d",
    urls = ["https://github.com/openssl/openssl/archive/OpenSSL_1_1_1d.tar.gz"]
)
