#include "client.h"

#include <spdlog/spdlog.h>

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

void Client::Stream(std::string username)
{
    grpc::ClientContext empty_context;
    auto writer = stub_->Stream(&empty_context);
    if (!writer)
    {
        spdlog::error("Cannot establish stream connection while joining game");
        return;
    }

    auto* request = new rpc::GameRequest;
    request->set_username(username);
    request->mutable_entity_snapshot()->set_health(0);
    request->mutable_entity_snapshot()->mutable_position()->set_x(0);
    request->mutable_entity_snapshot()->mutable_position()->set_y(0);
    request->mutable_entity_snapshot()->mutable_orientation()->set_angle(0);

    std::thread([&writer]() {
        spdlog::info("Starting incoming stream");

        auto* response = new rpc::GameResponse;

        while (true)
        {
            spdlog::debug("Reading response...");
            writer->Read(response);

            spdlog::debug("Response for {}", response->username());
            spdlog::debug("Position x={} y={}",
                          response->player_entity().position().x(),
                          response->player_entity().position().x());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();

    while (true)
    {
        float dx = rand() % 10 - 5;
        float dy = rand() % 20 - 5;

        auto position = request->mutable_entity_snapshot()->mutable_position();

        position->set_x(dx + request->entity_snapshot().position().x());
        position->set_y(dy + request->entity_snapshot().position().y());

        spdlog::debug("Updating player position to x={}, y={}", position->x(), position->y());

        bool success = writer->Write(*request);
        if (!success)
        {
            spdlog::error("Error while updating player entity");
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    /// @TODO: Implement a clean-up routine when the player quits the game - currently unreachable
    writer->WritesDone();

    grpc::Status status = writer->Finish();
    if (!status.ok())
    {
        spdlog::error("Error joining game. Reason: {}", status.error_message());
    }
}

}  // namespace Network