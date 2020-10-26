package(default_visibility = ["//visibility:private"])

cc_library(
    name = "boost_asio",
    srcs = ["build_asio_ssl.cc"],
    defines = ["BOOST_ASIO_SEPARATE_COMPILATION"],
    deps = [
        "@boost//:boost",
        "@boringssl//:ssl"
    ],
    visibility = ["//visibility:public"],
)
