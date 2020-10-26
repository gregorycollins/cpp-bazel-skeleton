load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

_all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

def uWebSockets_dependency_imports():
    rules_foreign_cc_dependencies()

    #-----------------------------------------------------------------------------
    # http
    #-----------------------------------------------------------------------------
    http_archive(
        name = "github_unetworking_usockets",
        build_file = "@//:third_party/uWebSockets/uSockets.BUILD",
        strip_prefix = "uSockets-master",
        sha256 = "0c9fbabc1be5113fb353d087debdd6d78d81ab178f1ac7ac838139f02e16fca2",
        urls = ["https://github.com/uNetworking/uSockets/archive/master.tar.gz"],
    )
    http_archive(
        name = "github_unetworking_uwebsockets",
        strip_prefix = "uWebSockets-18.15.0",
        sha256 = "fd2fa7f63e68a949668d264c8ce74b4feda9841266ae0d0017a2f5fee293aab2",
        urls = ["https://github.com/uNetworking/uWebSockets/archive/v18.15.0.tar.gz"],
        build_file = "@//:third_party/uWebSockets/uWebSockets.BUILD",
    )

