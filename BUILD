# -*- bazel -*-

package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

COPTS = [
    "-pthread",
    "-Wall",
    "-Wextra",
#    "-Wformat=2",
#    "-Wimplicit-fallthrough",
#    "-Weffc++",
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
)


config_setting(
    name = "platform_osx",
    constraint_values = [
        "@bazel_tools//platforms:osx",
    ],
)

config_setting(
    name = "platform_linux",
    constraint_values = [
        "@bazel_tools//platforms:linux",
    ],
)

CONFIGURE_OPTIONS = [
    "no-weak-ssl-ciphers",
    "no-idea",
    "no-comp",
]

configure_make(
    name = "openssl_static",
    configure_command = "config",
    configure_env_vars = select({
        ":platform_osx": {"AR": ""},
        "//conditions:default": {},
    }),
    configure_in_place = True,
    configure_options = select({
        ":platform_osx": [
            "no-asm",
            "no-afalgeng",
            "no-shared",
            "ARFLAGS=r",
        ] + CONFIGURE_OPTIONS,
        "//conditions:default": [
            "no-shared",
        ] + CONFIGURE_OPTIONS,
    }),
    lib_source = "@openssl//:all",
    out_lib_dir = "lib",
    static_libraries = [
        "libssl.a",
        "libcrypto.a",
    ],
    visibility = ["//visibility:public"],
)

make(
    name = "uSockets",
    make_env_vars = {
        "WITH_OPENSSL": "1"
        },
    # make_commands = ["make"],
    make_commands = [
        "export WITH_OPENSSL=1 && make -C $$EXT_BUILD_ROOT$$/external/github_unetworking_usockets",
        "cp $$EXT_BUILD_ROOT$$/external/github_unetworking_usockets/uSockets.a $$INSTALLDIR$$/lib/uSockets.a",
        "cp $$EXT_BUILD_ROOT$$/external/github_unetworking_usockets/src/libusockets.h $$INSTALLDIR$$/include/",
        "cp -r $$EXT_BUILD_ROOT$$/external/github_unetworking_usockets/src/internal $$INSTALLDIR$$/include/internal",
        ],
    lib_source = "@github_unetworking_usockets//:all",
    static_libraries = ["uSockets.a"],
    deps = [
        ":openssl_static",
        ],
    )

cc_binary(
    copts = COPTS,
    name = "web_server",
    srcs = ["web_server.cc"],
    deps = [
        ":uSockets",
        "@github_unetworking_uwebsockets//:main",
        "@zlib//:zlib",
    ],
    linkopts = [
        "-lpthread",
        "-ldl"
        ]
)
