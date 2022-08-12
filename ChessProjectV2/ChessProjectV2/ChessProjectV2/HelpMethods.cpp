#include "HelpMethods.h"

std::vector<std::string> splitString(
	std::string inputString,
	char charToSplit)
{
	std::vector<std::string> splittedString;
	std::string tempString;
	for (int i = 0; i < inputString.size(); i++)
	{
		if (inputString[i] == charToSplit)
		{
			if (tempString != "")
			{
				splittedString.push_back(tempString);
			}
			tempString.clear();
		}
		else
		{
			tempString.push_back(inputString[i]);
		}
	}
	splittedString.push_back(tempString);
	return splittedString;
}

bool isUpperCase(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool isLowerCase(char c)
{
	return c >= 'a' && c <= 'z';
}

char charToLower(char c)
{
	return (c + ('a' - 'A'));
}