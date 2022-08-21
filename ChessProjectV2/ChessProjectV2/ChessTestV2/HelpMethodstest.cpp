#include "CppUnitTest.h"
#include "../ChessProjectV2/HelpMethods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HelpMethodsTest
{
	TEST_CLASS(HelpMethodsTest)
	{
	public:
		TEST_METHOD(testStringSplittingWithSpaces)
		{
			std::string testString = "this string is can be split into different parts";
			std::vector<std::string> expectedResult = 
			{ "this", "string", "is", "can", "be", "split", "into", "different", "parts" };
			
			std::vector<std::string> result = splitString(testString, ' ');
			Assert::AreEqual(expectedResult.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(expectedResult[i], result[i]);
			}
		}
		TEST_METHOD(testStringSplittingWithOtherCharacters)
		{
			//split it with the character a
			std::string testString = "it*can*even*be*split*with*other*characters";
			std::vector<std::string> expectedResult = 
			{ "it", "can", "even", "be", "split", "with", "other", "characters" };
			
			std::vector<std::string> result = splitString(testString, '*');
			Assert::AreEqual(expectedResult.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(expectedResult[i], result[i]);
			}
		}
		TEST_METHOD(testStringSplittingWithMultipleSplitChars)
		{
			//split it with the character a
			std::string testString = "this!!string!!!has!!!!multiple!!split!chars";
			std::vector<std::string> expectedResult =
				{ "this", "string", "has", "multiple", "split", "chars" };

			std::vector<std::string> result = splitString(testString, '!');
			Assert::AreEqual(expectedResult.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(expectedResult[i], result[i]);
			}
		}
		TEST_METHOD(upperAndLowerCaseTest)
		{
			Assert::IsTrue(isUpperCase('A'));
			Assert::IsTrue(isUpperCase('Q'));
			Assert::IsTrue(isUpperCase('Z'));

			Assert::IsFalse(isUpperCase('a'));
			Assert::IsFalse(isUpperCase('q'));
			Assert::IsFalse(isUpperCase('z'));

			Assert::IsTrue(isLowerCase('a'));
			Assert::IsTrue(isLowerCase('q'));
			Assert::IsTrue(isLowerCase('z'));
			
			Assert::IsFalse(isLowerCase('A'));
			Assert::IsFalse(isLowerCase('Q'));
			Assert::IsFalse(isLowerCase('Z'));
		}
		TEST_METHOD(toLowerTest)
		{
			Assert::IsTrue('a' == charToLower('A'));
			Assert::IsTrue('z' == charToLower('Z'));
		}
		TEST_METHOD(directionTesting)
		{
			Assert::IsTrue(NORTH == getForwardForColor(White));
			Assert::IsTrue(SOUTH == getForwardForColor(Black));

			Assert::IsTrue(SOUTH == getBackwardForColor(White));
			Assert::IsTrue(NORTH == getBackwardForColor(Black));
		}
	};
}