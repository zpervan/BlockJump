package main

import (
	"context"
	"net/http"
	"server/proto"
)

type GameServer struct {
	UnimplementedGrpcServer
}

func (gs *GameServer) Connect(ctx context.Context, _ *proto.ConnectRequest) (*proto.ConnectResponse, error) {
	return &proto.ConnectResponse{Token: "nonfornow", Status: http.StatusOK, ServerName: "Test server"}, nil
}
