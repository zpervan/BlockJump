#include "client.h"

#include <spdlog/spdlog.h>

#include <future>
#include <optional>
#include <thread>

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

    if (!status.ok())
    {
        spdlog::warn("Error while fetching all games. Reason: ", status.error_message());
        return std::nullopt;
    }

    return list_of_games_.get();
}

void Client::JoinGame(const std::string& username)
{
    context_ = std::make_unique<grpc::ClientContext>();
    stream_writer_ = stub_->Stream(context_.get());

    if (!stream_writer_)
    {
        spdlog::error("Cannot establish stream connection to server");
        return;
    }

    response_ = std::make_unique<rpc::GameResponse>();
    request_ = std::make_unique<rpc::GameRequest>();
    request_->set_username(username);

    rpc::GameRequest initial_request;
    initial_request.set_username(username);
    /// @TODO: The initial data needs to be extracted from the map
    initial_request.mutable_entity_snapshot()->mutable_position()->set_x(100);
    initial_request.mutable_entity_snapshot()->mutable_position()->set_y(100);
    initial_request.mutable_entity_snapshot()->mutable_orientation()->set_angle(0);
    initial_request.mutable_entity_snapshot()->set_health(3);

    stream_writer_->Write(initial_request);

    rpc::GameResponse response;
    if (stream_writer_->Read(&response))
    {
        spdlog::info("Response from server: {}", response.message());
    }
    else
    {
        spdlog::error("Error while joining game");
        return;
    }
}

void Client::UpdatePlayerEntity(EntitySnapshot& player_entity)
{
    if (!stream_writer_)
    {
        spdlog::error("No stream connection established");
        return;
    }

    request_->mutable_entity_snapshot()->mutable_position()->set_x(player_entity.position().x());
    request_->mutable_entity_snapshot()->mutable_position()->set_y(player_entity.position().y());

    if (!stream_writer_->Write(*request_))
    {
        spdlog::error("Error while updating player entity");
        return;
    }

    spdlog::debug("Updated player entity x={}, y={}",
                  request_->entity_snapshot().position().x(),
                  request_->entity_snapshot().position().y());
}

void Client::UpdateWorldSnapshot()
{
    if (!stream_writer_)
    {
        spdlog::error("No stream connection established");
        return;
    }

    spdlog::info("Starting incoming stream");

    while (true)
    {
        spdlog::debug("Reading response...");
        stream_writer_->Read(response_.get());

        spdlog::debug("Response for {}", response_->username());
        spdlog::debug("Position x={} y={}", response_->player_entity().position().x(), response_->player_entity().position().x());

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

}  // namespace Network