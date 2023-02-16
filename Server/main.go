package main

import (
	"fmt"
	"google.golang.org/grpc"
	"log"
	"net"
	"server/core"
	"server/proto"
)

func main() {
	logger := core.NewLogger()

	logger.Info("starting server...")

	listener, err := net.Listen("tcp", ":9000")
	if err != nil {
		panic(err)
	}

	server := grpc.NewServer()
	proto.RegisterGrpcServer(server, &GameServer{})
	if err := server.Serve(listener); err != nil {
		logger.Fatal("failed to serve: " + err.Error())
	}
}
