#pragma once

namespace FightClub {
    namespace Server {
        namespace Common {

            class ICommand
            {
            };

            class ICommandHandler
            {
            public:
                virtual ~ICommandHandler() = default;

                inline void handle(ICommand& command) const
                {
                    handleImpl(command);
                }

            private:
                virtual void handleImpl(ICommand& command) const = 0;
            };

        }
    }
}