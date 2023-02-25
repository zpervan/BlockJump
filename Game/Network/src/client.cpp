#include "client.h"

#include <spdlog/spdlog.h>

namespace Network
{

grpc::Status Client::TestConnection(const rpc::DummyRequest& request)
{
    grpc::ClientContext context;
    rpc::DummyResponse response;

    return stub_->TestConnection(&context, request, &response);
}

}  // namespace Network