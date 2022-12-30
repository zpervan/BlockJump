[![Game(Ubuntu)](https://github.com/zpervan/BlockJump/actions/workflows/ubuntu_game.yml/badge.svg)](https://github.com/zpervan/BlockJump/actions/workflows/ubuntu_game.yml)
[![Game(Windows)](https://github.com/zpervan/BlockJump/actions/workflows/windows_game.yml/badge.svg)](https://github.com/zpervan/BlockJump/actions/workflows/windows_game.yml)
[![Server(Ubuntu)](https://github.com/zpervan/BlockJump/actions/workflows/ubuntu_server.yml/badge.svg)](https://github.com/zpervan/BlockJump/actions/workflows/ubuntu_server.yml)
[![Server(Windows)](https://github.com/zpervan/BlockJump/actions/workflows/windows_server.yml/badge.svg)](https://github.com/zpervan/BlockJump/actions/workflows/windows_server.yml)
## BlockJump ##

A simple jump-and-run platformer game. Also includes a map editor for creating custom maps.

Current state of the game:
![](.github/assets/game_preview.gif)

Current state of the map editor:
![](.github/assets/map_editor_preview.gif)

### Development setup ###

Used libraries:
- [curlcpp](https://github.com/JosephP91/curlcpp)
- [Google Test](https://github.com/google/googletest)
- [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)
- [ImGui](https://github.com/ocornut/imgui)
- [ImFileBrowser](https://github.com/AirGuanZ/imgui-filebrowser)
- [SFML](https://www.sfml-dev.org/)
- [spdlog](https://github.com/gabime/spdlog)

#### Ubuntu ####

1. Install [Bazel](https://www.bazel.build/) 6.0.0. Installation instructions can be found 
[here](https://bazel.build/install/ubuntu).
2. Open your terminal and install the following dependencies
```shell
$ sudo apt install bazel libgl-dev freeglut3-dev
```
3. Install the needed [protobuf](https://github.com/protocolbuffers/protobuf/tags) generator
4. Install the following `protobuf` dependencies for Go. Position your terminal in the `Server` folder and execute the following:
```shell
$ go install google.golang.org/protobuf/cmd/protoc-gen-go
$ go install google.golang.org/grpc/cmd/protoc-gen-go-grpc
```

#### Windows ####

1. Install [Bazel](https://www.bazel.build/) 6.0.0. Installation instructions can be found
      [here](https://bazel.build/install/windowsl).
2. Install Microsoft Visual Studio 19 - Community edition environment. Not sure about other MSVC version.

3. Install the needed [protobuf](https://github.com/protocolbuffers/protobuf/tags) generator
4. Install the following `protobuf` dependencies for Go. Position your terminal in the `Server` folder and execute the following:
```shell
$ go install google.golang.org/protobuf/cmd/protoc-gen-go
$ go install google.golang.org/grpc/cmd/protoc-gen-go-grpc
```

NOTE: Debug mode should work fine in both cases

### Run ###

To run the game, use the following command for Ubuntu:
```shell
$ bazel run //:main --config=linux # or --config=linux_debug for debug mode
```
And on Windows:
```shell
> bazel run //:main --config=windows
```

Running the server:
```shell
$ cd Server
$ go run .
```

