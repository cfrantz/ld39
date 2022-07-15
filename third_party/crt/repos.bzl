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
            url = "https://github.com/cfrantz/crt/archive/refs/tags/v0.2.0.tar.gz",
            sha256 = "262410ec73513930d4c9a84629db19395f9085911d9f4a10917d65a305b051d2",
            strip_prefix = "crt-0.2.0",
        )
