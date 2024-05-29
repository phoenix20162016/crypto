package(default_visibility = ["//visibility:public"])
cc_library(
  name = "rsa_util",
  hdrs = ["rsa_util.h"],
  srcs = ["rsa_util.cc"],
  deps = [
    "@openssl",
  ],
)

cc_library(
  name = "aes_util",
  hdrs = ["aes_util.h"],
  srcs = ["aes_util.cc"],
  deps = [
    ":padding_util",
    "@openssl",
    "//util:util",
    "@com_github_glog_glog//:glog",
  ],
)

cc_library(
  name = "padding_util",
  hdrs = ["padding.h"],
  srcs = ["padding.cc"],
  deps = [
    "@com_github_glog_glog//:glog",
  ],
)
