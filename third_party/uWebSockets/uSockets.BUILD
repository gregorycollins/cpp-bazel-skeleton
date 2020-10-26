load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")
package(default_visibility = ["//visibility:private"])
filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:private"])

make(
    name = "main",
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
    visibility = ["//visibility:public"],
    deps = [
        "@boringssl//:ssl",
        ],
    )
