load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def crt_repos(local=None):
    if local:
        native.local_repository(
            name = "crt",
            path = local,
        )
    else:
        maybe(
            http_archive,
            name = "crt",
            url = "https://github.com/cfrantz/crt/archive/refs/tags/cc65-2022-06-23.tar.gz",
            sha256 = "8f0f05899e21d2baf2eee883399f1ab914236035fb383585a415b06ffab25fa6",
            strip_prefix = "crt-cc65-2022-06-23",
        )
