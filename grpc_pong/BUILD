# -*- bazel -*-

package(default_visibility = ["//visibility:private"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

COPTS = [
    "-Wall",
]

proto_library(
    name = "pong_proto",
    srcs = ["pong.proto"],
    deps = ["@com_google_protobuf//:empty_proto"],
)
cc_proto_library(
    name = "pong_cc_proto",
    deps = [":pong_proto"],
)
cc_grpc_library(
    name = "pong_cc_grpc",
    srcs = [":pong_proto"],
    grpc_only = True,
    deps = [":pong_cc_proto"],
)

cc_binary(
    copts = COPTS,
    name = "pong_client",
    srcs = ["pong_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":pong_cc_grpc",
        "//external:gflags",
        "@com_github_grpc_grpc//:grpc++",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    copts = COPTS,
    name = "pong_server",
    srcs = ["pong_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":pong_cc_grpc",
        "//external:gflags",
        "@com_github_grpc_grpc//:grpc++",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "all_targets",
    srcs = [
        ":pong_client",
        ":pong_server",
    ],
    visibility = ["//visibility:public"],
)
