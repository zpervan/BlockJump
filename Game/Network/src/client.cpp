#include "client.h"

#include <spdlog/spdlog.h>

namespace Network
{

std::string Client::TestConnection(const rpc::DummyRequest& request)
{
    grpc::ClientContext context;
    rpc::DummyResponse response;

    const auto status = stub_->TestConnection(&context, request, &response);
    if (status.ok())
    {
        spdlog::info("Ping was successful");
    }
    else
    {
        spdlog::warn("Failed to ping server");
    }

    return response.dummy_data();
}

}  // namespace Network