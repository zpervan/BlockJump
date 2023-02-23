#include "client.h"

#include <spdlog/spdlog.h>

namespace Network
{

grpc::Status Client::TestConnection(const rpc::DummyRequest& request)
{
    grpc::ClientContext context;
    rpc::DummyResponse response;

    auto status = stub_->TestConnection(&context, request, &response);
    if (status.ok())
    {
        spdlog::info("Ping was successful");
    }
    else
    {
        spdlog::warn("Failed to ping server");
    }

    return status;
}

}  // namespace Network