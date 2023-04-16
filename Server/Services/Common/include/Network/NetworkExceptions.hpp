#pragma once

#include <exception>

namespace FightClub {
    namespace Server {
        namespace Common {

            class UriNotFoundException : public std::exception
            {
            public:
                const char* what() const noexcept override
                {
                    return "Specified Uri not found.";
                }
            };

            class MethodNotAllowedException : public std::exception
            {
            public:
                virtual const char* what() const noexcept override
                {
                    return "Specified method not allowed.";
                }
            };

            class InvalidParameterException : public std::exception
            {
            public:
                InvalidParameterException(const std::string& paramName) : 
                    m_message(paramName + " parameter not specified or of incorrect type.")
                {
                }

                virtual const char* what() const noexcept override
                {
                    return m_message.c_str();
                }

            private:
                std::string m_message;
            };

            class DataError : public std::exception
            {
            public:
                DataError(const std::string& message) : 
                    m_message(message)
                {
                }

                DataError(const std::string&& message) : 
                    m_message(std::move(message))
                {
                }

                virtual const char* what() const noexcept override
                {
                    return m_message.c_str();
                }

            private:
                std::string m_message;
            };
        }
    }
}