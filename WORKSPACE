load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
  name = "com_github_bazel_rules_3rdparty",
  commit = "67ac7942969ee2224732a9b50b17180390c4fc97",
  remote = "https://gitee.com/primihub/bazel-rules-thirdparty.git",
)
http_archive(
  name = "rules_foreign_cc",
  sha256 = "484fc0e14856b9f7434072bc2662488b3fe84d7798a5b7c92a1feb1a0fa8d088",
  strip_prefix = "rules_foreign_cc-0.8.0",
  url = "https://primihub.oss-cn-beijing.aliyuncs.com/tools/rules_foreign_cc_cn-0.8.0.tar.gz",
)
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

http_archive(
  name = "openssl",
  urls = [
    "https://primihub.oss-cn-beijing.aliyuncs.com/tools/openssl-OpenSSL_1_1_1o.tar.gz",
  ],
  #sha256 = "f56dd7d81ce8d3e395f83285bd700a1098ed5a4cb0a81ce9522e41e6db7e0389",
  strip_prefix = "openssl-OpenSSL_1_1_1o",
  build_file = "@com_github_bazel_rules_3rdparty//:openssl.BUILD",
)
http_archive(
  name = "com_github_stduuid",
  build_file = "@com_github_bazel_rules_3rdparty//:BUILD.stduuid",
  sha256 = "f554f6a9fe4d852fa217de6ab977afbf3f49e4a1dcb263afd61a94253c4c7a48",
  strip_prefix = "stduuid-1.2.2",
  urls = [
    "https://primihub.oss-cn-beijing.aliyuncs.com/tools/stduuid-1.2.2.tar.gz",
  ]
)

http_archive(
  # gflags Needed for glog
  name = "com_github_gflags_gflags",
  sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
  strip_prefix = "gflags-2.2.2",
  urls = [
      "https://primihub.oss-cn-beijing.aliyuncs.com/tools/gflags-2.2.2.tar.gz",
  ],
)

http_archive(
  name = "com_github_glog_glog",
  # sha256 = "cbba86b5a63063999e0fc86de620a3ad22d6fd2aa5948bff4995dcd851074a0b",
  strip_prefix = "glog-0.6.0",
  urls = [
    "https://primihub.oss-cn-beijing.aliyuncs.com/tools/glog-0.6.0.zip"
  ],
)