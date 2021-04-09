#include <boost/algorithm/string.hpp>

#include "CharacterStuff/AttributesManager.h"

#include "Common/IntHelper.h"

namespace fightclub
{
	namespace characterstuff
	{
		void AttributesManager::enterAttributesManager(character_t& character)
		{
			while (true)
			{
				std::cout << "Please, enter the command\nCommands:\n1) " << CurrentAttributesCommandText 
						  << "\n2) " << EditAttributesCommandText << "\n3) " << ExitCommandText << '\n';

				std::string command{ m_inputProcesser->getLine() };

				if (command == "1" || boost::iequals(command, CurrentAttributesCommandText))
				{
					std::cout << "Current character attributes:\n" << character << '\n';
				}
				else if (command == "2" || boost::iequals(command, EditAttributesCommandText))
				{
					editAttributes(character);
				}
				else if (command == "3" || boost::iequals(command, ExitCommandText))
				{
					return;
				}
				else
				{
					std::cout << "\n\nUnrecognized command entered.\n\n";
				}
			}
		}

		void AttributesManager::editAttributes(character_t& character)
		{
			while (true)
			{
				try
				{
					int leftAttributesPoints{ BaseAttributesManager::calculateLeftAttributePoints(character) };

					std::cout << "\nYou have " << std::to_string(leftAttributesPoints) << " attributes points.\nPlease, enter"
						<< " command to edit attributes.\n Commands:\n1) " << IncreaseAttributeCommandText << " " << AttributeCommandParamsText
						<< "\nExample: " << IncreaseAttributeCommandText << " " << TypeParamText << " " << StrengthAttributeTypeText
						<< " " << ValueParamText << " 1\n"
						<< "2) " << DecreaseAttributeCommandText << " " << AttributeCommandParamsText
						<< "\nExample: " << DecreaseAttributeCommandText << " " << TypeParamText << " " << AgilityAttributeTypeText
						<< " " << ValueParamText << " 1\n"
						<< "3) " << ExitCommandText << '\n';

					std::string command{ m_inputProcesser->getLine() };

					std::string editAttributeCommand;
					if (command == "1" || containsSpecifiedCommand(command, IncreaseAttributeCommandText))
					{
						editAttributeCommand = IncreaseAttributeCommandText;
					}
					else if (command == "2" || containsSpecifiedCommand(command, DecreaseAttributeCommandText))
					{
						editAttributeCommand = DecreaseAttributeCommandText;
					}
					else if (command == "3" || boost::iequals(command, ExitCommandText))
					{
						BaseAttributesManager::saveChanges(character);
						return;
					}
					else
					{
						throw std::runtime_error("Unrecognized command entered.");
					}

					auto type{ getAttributeTypeFromText(command) };

					if (type == attributeType_t::max_attribute_type)
					{
						throw std::out_of_range("Entered type does not exist. Please, try again.");
					}

					auto valueStr{ m_commandLineParser->getValue(command, ValueParamText) };

					int valueInt{};
					if (!common::IntHelper::tryParse(valueStr, valueInt))
					{
						throw std::out_of_range("Value " + valueStr + " is not type of integer. Please, try again.");
					}

					if (editAttributeCommand == IncreaseAttributeCommandText)
					{
						increaseAttribute(character, type, valueInt);
					}
					else
					{
						decreaseAttribute(character, type, valueInt);
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << "\n\n" << ex.what() << "\n\n";
				}
			}
		}

		bool AttributesManager::containsSpecifiedCommand(const std::string& text, const std::string& command)
		{
			auto textToLower{ boost::to_lower_copy(text) };
			auto commandToLower{ boost::to_lower_copy(command) };

			return textToLower.find(commandToLower) != std::string::npos;
		}

		AttributesManager::attributeType_t AttributesManager::getAttributeTypeFromText(std::string& text)
		{
			auto typeText{ m_commandLineParser->getValue(text, TypeParamText) };

			if (boost::iequals(typeText, StrengthAttributeTypeText))
			{
				return attributeType_t::strong;
			}
			else if (boost::iequals(typeText, AgilityAttributeTypeText))
			{
				return attributeType_t::smooth;
			}
			else
			{
				return attributeType_t::max_attribute_type;
			}
		}
	}
}