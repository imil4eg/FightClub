#ifndef INPUT_PROCESSER_H
#define INPUT_PROCESSER_H

#include <iostream>

#include "IO/IInputProcesser.h"

namespace fightclub
{
	namespace io
	{
		class InputProcesser : public core::io::IInputProcesser
		{
		private:
			const std::string m_lineBeggining{ "FightClub>" };

		public:
			std::string getLine() const override
			{
				std::cout << m_lineBeggining;

				std::string input;
				std::getline(std::cin, input);

				return input;
			}
		};
	}
}

#endif // !INPUT_PROCESSER_H

