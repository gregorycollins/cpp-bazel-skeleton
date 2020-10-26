# -*- bazel -*-

package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

COPTS = [
    "-Wall",
]

cc_binary(
    copts = COPTS,
    name = "web_server",
    srcs = ["web_server.cc"],
    deps = [
        "@github_unetworking_uwebsockets//:main",
        "@zlib//:zlib",
        "@cpprest//:cpprest",  # todo - remove
    ],
)

filegroup(
    name = "all_targets",
    srcs = [
        ":web_server",
    ],
)
