# -*- bazel -*-

package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

COPTS = [
    "-Wall",
]

filegroup(
    name = "all_targets",
    srcs = [
        "//etcd_client:all_targets",
        "//grpc_pong:all_targets",
        "//web_server:all_targets",
    ]
)

