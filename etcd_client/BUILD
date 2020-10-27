package(default_visibility = ["//visibility:public"])

cc_library(
    name = "etcd_client_lib",
    srcs = [
        "etcd_client.cc",
    ],
    deps = [
        "@etcd-cpp-apiv3//:etcd-cpp-apiv3",
    ],
    linkstatic = True,
)

filegroup(
    name = "all_targets",
    srcs = [
        ":etcd_client_lib",
    ],
)
