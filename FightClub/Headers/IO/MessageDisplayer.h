#ifndef MESSAGE_DISPLAYER_H
#define MESSAGE_DISPLAYER_H

#include <string>
#include <iostream>

#include "IO/IMessageDisplayer.h"

namespace fightclub
{
	namespace io
	{
		class MessageDisplayer : public core::io::IMessageDisplayer
		{
		public:
			void display(const std::string& message) const override
			{
				std::cout << message << '\n';
			}

			static void cmdLineBeggining()
			{
				std::cout << "FightClub>";
			}
		};

	}
}

#endif // !MESSAGE_DISPLAYER_H



