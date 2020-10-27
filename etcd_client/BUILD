package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "etcd_incrementer",
    srcs = [
        "etcd_client.cc",
    ],
    deps = [
        "@etcd-cpp-apiv3//:etcd-cpp-apiv3",
        "//external:gflags",
    ],
    linkstatic = True,
)

filegroup(
    name = "all_targets",
    srcs = [
        ":etcd_incrementer",
    ],
)
