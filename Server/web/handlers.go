package web

import (
	"context"
	"fmt"
	"server/core"
	"server/proto"
)

type GameServer struct {
	logger *core.Logger
	proto.UnimplementedBlockJumpServer
	listOfGames *proto.ListOfGames
}

func NewServer(logger *core.Logger) *GameServer {
	server := &GameServer{}

	server.logger = logger
	server.listOfGames = &proto.ListOfGames{}

	return server
}

func (gs *GameServer) TestConnection(_ context.Context, in *proto.DummyRequest) (*proto.DummyResponse, error) {
	gs.logger.Info("received test connection request from client")

	if in.DummyData == "" {
		return &proto.DummyResponse{}, nil
	}

	return &proto.DummyResponse{DummyData: "received following data - " + in.DummyData}, nil
}

// CreateGame
// todo: Add some input data validation
// todo: Make sure game names are unique
func (gs *GameServer) CreateGame(_ context.Context, in *proto.Game) (*proto.Empty, error) {
	message := fmt.Sprintf("creating new game.\nname: %s\nmap name: %s", in.Name, in.MapName)
	gs.logger.Info(message)

	gs.listOfGames.AvailableGames = append(gs.listOfGames.AvailableGames, in)
	return &proto.Empty{}, nil
}

func (gs *GameServer) ListAllGames(_ context.Context, _ *proto.Empty) (*proto.ListOfGames, error) {
	message := fmt.Sprintf("fetching all available online games. count: %d", len(gs.listOfGames.AvailableGames))
	gs.logger.Info(message)
	return gs.listOfGames, nil
}
