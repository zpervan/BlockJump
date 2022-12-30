workspace(name = "BlockJump")

local_repository(
    name = "bazel_skylib",
    path = "ThirdParty/BazelSkylib/",
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    sha256 = "e017528fd1c91c5a33f15493e3a398181a9e821a804eb7ff5acdd1d2d6c2b18d",
    strip_prefix = "rules_proto-4.0.0-3.20.0",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0-3.20.0.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

local_repository(
    name = "curlcpplib",
    path = "ThirdParty/curlcpp/",
)

local_repository(
    name = "gllib",
    path = "ThirdParty/GL/",
)

local_repository(
    name = "googletestlib",
    path = "ThirdParty/googletest/",
)

local_repository(
    name = "imguilib",
    path = "ThirdParty/imgui/",
)

local_repository(
    name = "sfmllib",
    path = "ThirdParty/SFML/",
)

local_repository(
    name = "spdloglib",
    path = "ThirdParty/spdlog/",
)
