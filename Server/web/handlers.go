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
	// todo: Extend in such way that multiple games are present
	worldSnapshot *proto.WorldSnapshot
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
func (gs *GameServer) CreateGame(_ context.Context, in *proto.GameInfo) (*proto.Empty, error) {
	message := fmt.Sprintf("creating new game.\nname: %s\nmap name: %s", in.Name, in.MapName)
	gs.logger.Info(message)

	gs.listOfGames.AvailableGames = append(gs.listOfGames.AvailableGames, in)
	return &proto.Empty{}, nil
}

func (gs *GameServer) JoinGame(_ context.Context, in *proto.ConnectRequest) (*proto.GameInfo, error) {
	newPlayer := proto.EntitySnapshot{}
	newPlayer.Id = "NoneForNow"
	newPlayer.Name = in.Username
	newPlayer.Health = 3                                 // Full health
	newPlayer.Position = &proto.Position{X: 400, Y: 100} // todo: Dummy starting position
	newPlayer.Orientation = &proto.Orientation{Angle: 0} // todo: Dummy orientation

	gs.worldSnapshot.Entities = append(gs.worldSnapshot.Entities)

	// todo: Just for simplicity, make the first game joinable. Extend and refactor later on
	return gs.listOfGames.AvailableGames[0], nil
}

func (gs *GameServer) ListAllGames(_ context.Context, _ *proto.Empty) (*proto.ListOfGames, error) {
	message := fmt.Sprintf("fetching all available online games. count: %d", len(gs.listOfGames.AvailableGames))
	gs.logger.Info(message)
	return gs.listOfGames, nil
}

// Update
// todo: Implement updating world snapshot by ID so we can allow multiple games to be played at once
func (gs *GameServer) Update(_ context.Context, in *proto.EntitySnapshot) (*proto.WorldSnapshot, error) {
	// todo: Consider to use a map instead of slice (faster lookup)
	// todo: Implement update functionality!
	return gs.worldSnapshot, nil
}
