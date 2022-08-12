#pragma once
#include <string>
#include <vector>

std::vector<std::string> splitString(
	std::string inputString,
	char charToSplit);

bool isUpperCase(char c);
bool isLowerCase(char c);

char charToLower(char c);