#include "client.h"

#include <spdlog/spdlog.h>

#include <optional>

namespace Network
{

Client::Client(const std::shared_ptr<grpc::Channel>& channel)
    : stub_(rpc::BlockJump::NewStub(channel)),
      list_of_games_(std::make_unique<rpc::ListOfGames>())
{
}

grpc::Status Client::TestConnection(const rpc::DummyRequest& request)
{
    spdlog::info("Testing connection to server...");

    grpc::ClientContext empty_context;
    rpc::DummyResponse response;

    return stub_->TestConnection(&empty_context, request, &response);;
}

std::optional<rpc::ListOfGames*> Client::ListAllGames()
{
    spdlog::info("Fetching list of available games");

    grpc::ClientContext empty_context;

    const auto status = stub_->ListAllGames(&empty_context, {}, list_of_games_.get());

    if (!status.ok() && list_of_games_->has_error())
    {
        spdlog::warn("Error while fetching all games. Reason: ", status.error_message());
        return std::nullopt;
    }

    return list_of_games_.get();
}

}  // namespace Network