#include <iostream>
#include <chrono>
#include <libi2pd/api.h>

static const char http_response[] = "HTTP/1.1 200 OK\r\n"
                                    "Content-Type: text/plain\r\n"
                                    "Connection: close\r\n"
                                    "\r\nHello World";

int main(int argc, char* argv[])
{
    i2p::api::InitI2P(argc, argv, "i2pwebsite");
    i2p::api::StartI2P();

    //isPublic = true
    auto dest = i2p::api::CreateLocalDestination(true);
    
    std::cout << "Listening on http://" << dest->GetIdentHash().ToBase32() << ".b32.i2p\n";

    i2p::api::AcceptStream(
        dest,
        [](std::shared_ptr<i2p::stream::Stream> stream)
        {
            uint8_t buffer[4096];
            
            auto n = stream->ReadSome(buffer, sizeof(buffer));
            if (n > 0)
            {
                std::cout.write(reinterpret_cast<char*>(buffer), n);
                std::cout << "\n";

                stream->Send(
                    reinterpret_cast<const uint8_t*>(http_response),
                    sizeof(http_response) - 1
                );
            }
            stream->Close();
            i2p::api::DestroyStream(stream);
        }
    );

    std::cout << "Destination is been prepared...\n";
    while (true) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        if (dest->IsReady()) break;
    }
    std::cout << "Destination is ready!\n";
    while (true) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    i2p::api::DestroyLocalDestination(dest);
    i2p::api::StopI2P();
    i2p::api::TerminateI2P();

    return 0;
}
