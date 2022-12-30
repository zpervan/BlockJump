package main

import (
	"fmt"
	"google.golang.org/grpc"
	"log"
	"net"
	"server/proto"
)

func main() {
	fmt.Println("starting game server")

	listener, err := net.Listen("tcp", ":9000")
	if err != nil {
		panic(err)
	}

	server := grpc.NewServer()
	proto.RegisterGrpcServer(server, &proto.GameServer{})
	if err := server.Serve(listener); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
