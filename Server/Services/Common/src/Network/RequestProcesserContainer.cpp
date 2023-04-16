#include "RequestProcesserContainer.hpp"

#include "NetworkExceptions.hpp"

namespace FightClub {
    namespace Server {
        namespace Common { 

            struct RequestProcesserContainer::Impl
            {
                std::unordered_map<std::string, std::unordered_map<http::verb, RequestProcesser_t>> processers;
            };

            RequestProcesserContainer::RequestProcesserContainer() :
                pImpl(std::make_unique<Impl>())
            {
            }

            RequestProcesserContainer::~RequestProcesserContainer() = default;

            void RequestProcesserContainer::insert(const std::string& path, http::verb httpMethod, RequestProcesser_t processer)
            {
                if (pImpl->processers.find(path) == pImpl->processers.end())
                {
                    std::unordered_map<http::verb, RequestProcesser_t> handlers;
                    handlers[httpMethod] = processer;
                    pImpl->processers.insert(std::make_pair(path, std::move(handlers)));
                }
                else
                {
                    if (pImpl->processers[path].find(httpMethod) != pImpl->processers[path].end())
                    {
                        throw std::runtime_error("Handler of http type " + http::to_string(httpMethod).to_string()  + " already specified.");
                    }
                    else
                    {
                        pImpl->processers[path][httpMethod] = std::move(processer);
                    }
                }
            }

            RequestProcesser_t RequestProcesserContainer::get(const std::string& path, http::verb method) const
            {
                auto pathIterator = pImpl->processers.find(path);

                if (pathIterator == pImpl->processers.end())
                {
                    throw UriNotFoundException();
                }

                auto processerIterator = pathIterator->second.find(method);

                if (processerIterator == pathIterator->second.end())
                {
                    throw MethodNotAllowedException();
                }

                return processerIterator->second;
            }
        }
    }
}