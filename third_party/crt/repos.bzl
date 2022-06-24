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
            sha256 = "477df93f5fe89b9be48be756a1060705cef16fc3c7b9fb09fc4cc28cb4b87891",
            strip_prefix = "crt-cc65-2022-06-23",
        )
