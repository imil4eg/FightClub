#include "BoostCommon.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {
            namespace Network {

                response_t buildResponse(const request_t& request, http::status status, const std::string& message)
                {
                    response_t response{status, request.version()};
                    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                    response.set(http::field::content_type, "application/json");
                    response.keep_alive(request.keep_alive());
                    response.body() = message;
                    response.prepare_payload();

                    return response;
                }

            }
        }
    }
}