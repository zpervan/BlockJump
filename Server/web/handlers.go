package web

import (
	"context"
	"server/core"
	"server/proto"
)

type GameServer struct {
	logger *core.Logger
	proto.UnimplementedBlockJumpServer
}

func NewServer(logger *core.Logger) *GameServer{
	server := &GameServer{}

	server.logger = logger

	return server
}

func (gs *GameServer) TestConnection(_ context.Context, in *proto.DummyRequest) (*proto.DummyResponse, error) {
	gs.logger.Info("received request from client")
	return &proto.DummyResponse{DummyData: "received following data - " + in.DummyData}, nil
}
