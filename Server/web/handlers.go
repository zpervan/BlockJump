package web

import (
	"context"
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

func (gs *GameServer) CreateGame(_ context.Context, in *proto.Game) (*proto.Empty, error) {
    // todo: Add some input data validation
    gs.logger.Info("creating new game")
    gs.listOfGames.AvailableGames = append(gs.listOfGames.AvailableGames, in)
    return &proto.Empty{}, nil
}

func (gs *GameServer) ListAllGames(_ context.Context, _ *proto.Empty) (*proto.ListOfGames, error) {
    gs.logger.Info("fetching list of all games")
    return gs.listOfGames, nil
}
