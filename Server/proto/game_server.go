package proto

import (
	"context"
	"net/http"
)

type GameServer struct {
	UnimplementedGrpcServer
}

func (gs *GameServer) Connect(ctx context.Context, _ *ConnectRequest) (*ConnectResponse, error) {
	return &ConnectResponse{Token: "nonfornow", Status: http.StatusOK}, nil
}
