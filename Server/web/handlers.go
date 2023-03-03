package web

import (
	"context"
	"fmt"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"io"
	"log"
	"server/core"
	"server/proto"
	"sync"
	"time"
)

type Player struct {
	Username       string
	EntitySnapshot proto.EntitySnapshot
}

type GameServer struct {
	mutex       *sync.Mutex
	logger      *core.Logger
	listOfGames *proto.ListOfGames
	players     map[string]Player
	proto.UnimplementedBlockJumpServer
}

func NewServer(logger *core.Logger) *GameServer {
	server := &GameServer{}

	server.mutex = &sync.Mutex{}
	server.logger = logger
	server.listOfGames = &proto.ListOfGames{}
	server.players = map[string]Player{}

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
	gs.listOfGames.AvailableGames[len(gs.listOfGames.AvailableGames)-1].ActivePlayerCount++
	// todo: Add game creator to player list

	return &proto.Empty{}, nil
}

func (gs *GameServer) ListAllGames(_ context.Context, _ *proto.Empty) (*proto.ListOfGames, error) {
	message := fmt.Sprintf("fetching all available online games. count: %d", len(gs.listOfGames.AvailableGames))
	gs.logger.Info(message)
	return gs.listOfGames, nil
}

func (gs *GameServer) Stream(stream proto.BlockJump_StreamServer) error {
	req, err := stream.Recv()

	if err != nil {
		gs.logger.Error("error obtaining username from client. reason: " + err.Error())
		return err
	}

	playerUsername := req.Username

	err = gs.joinGame(playerUsername, req.EntitySnapshot)
	if err != nil {
		gs.logger.Error("could not join game. reason: " + err.Error())
		return err
	}

	welcomeMessage := &proto.GameResponse{Message: fmt.Sprintf("welcome to the game, %s", playerUsername)}
	err = stream.Send(welcomeMessage)

	if err != nil {
		errorMessage := fmt.Sprintf("cannot send welcome message for player \"%s\"", playerUsername)
		gs.logger.Error(errorMessage)
		return err
	}

	for {
		// Just temporary so the thread is not abused, i.e. spammed with data
		time.Sleep(1 * time.Second)

		req, err := stream.Recv()

		if err == io.EOF {
			gs.logger.Warn(fmt.Sprintf("nothing to read from player \"%s\" - skipping update", playerUsername))
			continue
		}

		if err != nil {
			// Remove the player once the stream is canceled
			if status.Code(err) == codes.Canceled {
				gs.mutex.Lock()

				delete(gs.players, playerUsername)

				gs.logger.Info(fmt.Sprintf("player \"%s\" left the game", playerUsername))
				gs.mutex.Unlock()

				return err
			}

			gs.logger.Error("error - " + err.Error())
			continue
		}

		gs.logger.Info(fmt.Sprintf("updating player \"%s\"", playerUsername))

		gs.mutex.Lock()

		player := gs.players[playerUsername]
		player.EntitySnapshot.Position = req.EntitySnapshot.Position

		gs.players[playerUsername] = player

		gs.mutex.Unlock()

		// Broadcast the updated player positions to all connected players (except the sender)
		gs.mutex.Lock()

		for username, player := range gs.players {
			if username != playerUsername {
				playerSnapshot := &proto.GameResponse{
					Username:     player.Username,
					PlayerEntity: &player.EntitySnapshot,
				}

				if err := stream.Send(playerSnapshot); err != nil {
					log.Printf("error broadcasting player snapshot to player %s: %v", username, err)
				}
			}
		}
		gs.mutex.Unlock()
	}
}

func (gs *GameServer) joinGame(username string, playerSnapshot *proto.EntitySnapshot) error {
	gs.mutex.Lock()
	gs.players[username] = Player{Username: username, EntitySnapshot: *playerSnapshot}
	gs.mutex.Unlock()

	message := fmt.Sprintf("player \"%s\" joined the game", username)
	gs.logger.Info(message)

	return nil
}
