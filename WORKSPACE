# -*- bazel -*-

#-----------------------------------------------------------------------------
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl",
     "git_repository", "new_git_repository")

#-----------------------------------------------------------------------------
# foreign rules (make, cmake)
#-----------------------------------------------------------------------------
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

#-----------------------------------------------------------------------------
# openssl
# -----------------------------------------------------------------------------
# I hate to do this but there is no other way to get gRPC to use OpenSSL
# instead of BoringSSL -- one of the other libs insists on the real mccoy
http_archive(
    name = "boringssl",
    build_file = "@//:third_party/openssl/openssl.BUILD",
    strip_prefix = "openssl-OpenSSL_1_1_1d",
    urls = ["https://github.com/openssl/openssl/archive/OpenSSL_1_1_1d.tar.gz"]
)

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
    build_file = ":third_party/json.BUILD",
)
bind (
    name = "json",
    actual = "@github_nlohmann_json//:main",
)

#------------------------------------------------------------------------------
# uWebSockets http server
#------------------------------------------------------------------------------
load("@//:third_party/uWebSockets/workspace.bzl", "uWebSockets_dependency_imports")
uWebSockets_dependency_imports()

#------------------------------------------------------------------------------
# boost (booooo)
#------------------------------------------------------------------------------
http_archive(
    name = "boost",
    build_file = "@//:third_party/boost/boost.BUILD",
    sha256 = "afff36d392885120bcac079148c177d1f6f7730ec3d47233aa51b0afa4db94a5",
    strip_prefix = "boost_1_74_0",
    urls = [
        "https://mirror.bazel.build/dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz",
        "https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz",
    ],
)

#------------------------------------------------------------------------------
# cpprestsdk
#------------------------------------------------------------------------------
new_git_repository(
    name = "cpprest",
    build_file = "@//:third_party/cpprest/cpprest.BUILD",
    remote = "https://github.com/microsoft/cpprestsdk.git",
    commit = "18212a2a7967e12d740bfb957e500892b3463c88",
    init_submodules = True,
)
