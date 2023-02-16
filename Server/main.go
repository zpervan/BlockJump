package main

import (
	"google.golang.org/grpc"
	"net"
	"server/core"
	"server/proto"
	"server/web"
)

func main() {
	logger := core.NewLogger()

	listener, err := net.Listen("tcp", ":3500")
	if err != nil {
		logger.Fatal("")
	}

	serverOptions := []grpc.ServerOption{}

	server := grpc.NewServer(serverOptions...)
	proto.RegisterBlockJumpServer(server, web.NewServer(logger))

	logger.Info("starting server")
	
	if err := server.Serve(listener); err != nil {
		logger.Fatal("failed to serve: " + err.Error())
	}
}
