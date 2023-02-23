#ifndef BLOCKJUMP_GAME_NETWORK_SRC_CLIENT_H_
#define BLOCKJUMP_GAME_NETWORK_SRC_CLIENT_H_

#include <grpcpp/grpcpp.h>

#include <memory>

#include "ProtoMessages/server/grpc_server.grpc.pb.h"
#include "ProtoMessages/server/grpc_server.pb.h"

namespace Network
{

/// @brief Contains all gRPC (network) related functionality in order for the client and server to communicate.
/// @TODO: Maybe add empty constructor for lazy initialization?
class Client
{
  public:
    /// @brief Network client constructor which accepts a gRPC channel which is used to establish a connection to the
    /// server.
    /// @param channel Connection endpoint to the server
    explicit Client(const std::shared_ptr<grpc::Channel>& channel) : stub_(rpc::BlockJump::NewStub(channel)){};
    ~Client() = default;

    // Copy and move operation are disabled, therefore enforce to have a single and fixed instance of the network client
    // available as they tend to be costly to copy and error-prone if moved.
    Client(Client&& rhs) = delete;
    Client& operator=(Client&& rhs) = delete;

    Client(const Client& rhs) = delete;
    Client operator=(const Client& rhs) = delete;

    /// @brief Send a dummy request in order to check whether the connection to the server is alive.
    /// @param request Dummy request
    /// @return Server status
    grpc::Status TestConnection(const rpc::DummyRequest& request);

  private:
    std::unique_ptr<rpc::BlockJump::Stub> stub_;
};

}  // namespace Network

#endif  // BLOCKJUMP_GAME_NETWORK_SRC_CLIENT_H_
