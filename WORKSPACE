workspace(name = "BlockJump")

local_repository(
    name = "bazel_skylib",
    path = "ThirdParty/BazelSkylib/",
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# ------- gRPC -------

http_archive(
    name = "rules_proto_grpc",
    sha256 = "fb7fc7a3c19a92b2f15ed7c4ffb2983e956625c1436f57a3430b897ba9864059",
    strip_prefix = "rules_proto_grpc-4.3.0",
    urls = ["https://github.com/rules-proto-grpc/rules_proto_grpc/archive/4.3.0.tar.gz"],
)

http_archive(
    name = "rules_proto",
    sha256 = "dc3fb206a2cb3441b485eb1e423165b231235a1ea9b031b4433cf7bc1fa460dd",
    strip_prefix = "rules_proto-5.3.0-21.7",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/5.3.0-21.7.tar.gz",
    ],
)

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "92fdb11e9bdc770e16caedf9c13d1688ce476a0c763c11d3871781af3881ac28",
    strip_prefix = "grpc-0a82c02a9b817a53574994374dcff53f2e961df2",
    urls = [
        "https://github.com/grpc/grpc/archive/0a82c02a9b817a53574994374dcff53f2e961df2.tar.gz",
    ],
)

load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_repos", "rules_proto_grpc_toolchains")

rules_proto_grpc_toolchains()

rules_proto_grpc_repos()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

load("@rules_proto_grpc//cpp:repositories.bzl", rules_proto_grpc_cpp_repos = "cpp_repos")

rules_proto_grpc_cpp_repos()

# ------- Manually imported libraries -------

local_repository(
    name = "protomessageslib",
    path = "ProtoMessages/",
)

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

local_repository(
    name = "stduuidlib",
    path = "ThirdParty/stduuid/",
)
