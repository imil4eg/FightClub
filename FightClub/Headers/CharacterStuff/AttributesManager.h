#pragma once

#include <vector>

#include "CharacterStuff/BaseAttributesManager.h"
#include "CharacterStuff/IAttributesManager.h"
#include "CharacterStuff/IAttributesFactory.h"
#include "IO/IInputProcesser.h"
#include "IO/ICommandLineParser.h"

namespace fightclub
{
	namespace characterstuff
	{
		class AttributesManager : public core::characterstuff::BaseAttributesManager
		{
		private:
			typedef fightclub::core::characters::Character character_t;
			typedef fightclub::core::characterstuff::AttributeType attributeType_t;

			const std::string CurrentAttributesCommandText{ "Current attributes" };
			const std::string EditAttributesCommandText{ "Edit attributes" };
			const std::string ExitCommandText{ "Exit" };
			const std::string IncreaseAttributeCommandText{ "Increase" };
			const std::string DecreaseAttributeCommandText{ "Decrease" };
			const std::string AttributeCommandParamsText{ "-t <attribute type> -v <value>" };
			const std::string TypeParamText{ "-t" };
			const std::string ValueParamText{ "-v" };
			const std::string StrengthAttributeTypeText{ "strength" };
			const std::string AgilityAttributeTypeText{ "agility" };

			core::io::IInputProcesser* m_inputProcesser;
			io::ICommandLineParser* m_commandLineParser;

			int m_tempStrength{};
			int m_tempAgility{};

		public:
			AttributesManager(core::io::IInputProcesser& inputProcesser,
							  core::characterstuff::IAttributesFactory& attributesFactory,
							  io::ICommandLineParser& commadLineParser) :
				BaseAttributesManager(attributesFactory),
				m_inputProcesser{ &inputProcesser },
				m_commandLineParser{ &commadLineParser}
			{
			}
			
			void enterAttributesManager(character_t& character) override;
			
		private:
			void editAttributes(character_t& character);
			bool containsSpecifiedCommand(const std::string& text, const std::string& command);
			attributeType_t getAttributeTypeFromText(std::string& text);
		};
	}
}