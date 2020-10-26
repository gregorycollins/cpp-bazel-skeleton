cc_library (
    name = "main",
    hdrs = glob(
        ["src/**/*.h",
         "src/f2/*.hpp"],
    ),
    includes = ["src"],
    strip_include_prefix = "src",
    visibility = ["//visibility:public"],
    deps = [ "@github_unetworking_usockets//:main" ],
)
