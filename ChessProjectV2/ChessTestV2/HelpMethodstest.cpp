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
		TEST_METHOD(oppositeColor)
		{
			Assert::IsTrue(Black == getOppositeColor(White));
			Assert::IsTrue(White == getOppositeColor(Black));
		}
		TEST_METHOD(isRayTypeTest)
		{
			Assert::IsTrue(isRayType(Rook));
			Assert::IsTrue(isRayType(Bishop));
			Assert::IsTrue(isRayType(Queen));
			
			Assert::IsFalse(isRayType(King));
			Assert::IsFalse(isRayType(Pawn));
			Assert::IsFalse(isRayType(Knight));
		}
		TEST_METHOD(positionIsValidTest)
		{
			//new position is too far left
			Assert::IsFalse(destinationIsOnBoard(A3, WEST));
			Assert::IsFalse(destinationIsOnBoard(A3, NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A3, SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(A3, EAST));
			Assert::IsTrue(destinationIsOnBoard(A3, NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A3, SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A3, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(A3, NORTH));

			//new position is too far right
			Assert::IsFalse(destinationIsOnBoard(H3, EAST));
			Assert::IsFalse(destinationIsOnBoard(H3, NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H3, SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(H3, WEST));
			Assert::IsTrue(destinationIsOnBoard(H3, NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H3, SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H3, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(H3, NORTH));

			//new position is too far up
			Assert::IsFalse(destinationIsOnBoard(E8, NORTH));
			Assert::IsFalse(destinationIsOnBoard(E8, NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(E8, NORTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(E8, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(E8, SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(E8, SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(E8, EAST));
			Assert::IsTrue(destinationIsOnBoard(E8, WEST));

			//new position is too far down
			Assert::IsFalse(destinationIsOnBoard(E1, SOUTH));
			Assert::IsFalse(destinationIsOnBoard(E1, SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(E1, SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(E1, NORTH));
			Assert::IsTrue(destinationIsOnBoard(E1, NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(E1, NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(E1, EAST));
			Assert::IsTrue(destinationIsOnBoard(E1, WEST));

			//knights move is too far left
			Assert::IsFalse(destinationIsOnBoard(B3, WEST_NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(B3, WEST_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B3, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(B3, NORTH_NORTH_WEST));

			//knights move is too far right
			Assert::IsFalse(destinationIsOnBoard(G3, EAST_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(G3, EAST_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G3, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(G3, NORTH_NORTH_EAST));

			//left lower corner
			Assert::IsTrue(destinationIsOnBoard(A1, NORTH));
			Assert::IsTrue(destinationIsOnBoard(A1, NORTH_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A1, NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A1, EAST_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A1, EAST));

			Assert::IsFalse(destinationIsOnBoard(A1, EAST_SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(A1, SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(A1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(A1, SOUTH));
			Assert::IsFalse(destinationIsOnBoard(A1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, WEST_SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, WEST_NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A1, NORTH_NORTH_WEST));

			//right lower corner
			Assert::IsTrue(destinationIsOnBoard(H1, NORTH));

			Assert::IsFalse(destinationIsOnBoard(H1, NORTH_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, EAST_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, EAST_SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H1, SOUTH));
			Assert::IsFalse(destinationIsOnBoard(H1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(H1, SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(H1, WEST_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(H1, WEST));
			Assert::IsTrue(destinationIsOnBoard(H1, WEST_NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H1, NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H1, NORTH_NORTH_WEST));

			//left upper corner
			Assert::IsFalse(destinationIsOnBoard(A8, NORTH));
			Assert::IsFalse(destinationIsOnBoard(A8, NORTH_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(A8, NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(A8, EAST_NORTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(A8, EAST));
			Assert::IsTrue(destinationIsOnBoard(A8, EAST_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A8, SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A8, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(A8, SOUTH));

			Assert::IsFalse(destinationIsOnBoard(A8, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, WEST_SOUTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, WEST_NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(A8, NORTH_NORTH_WEST));

			//right upper corner
			Assert::IsFalse(destinationIsOnBoard(H8, NORTH));
			Assert::IsFalse(destinationIsOnBoard(H8, NORTH_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, EAST_NORTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, EAST_SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, SOUTH_EAST));
			Assert::IsFalse(destinationIsOnBoard(H8, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(H8, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(H8, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H8, SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H8, WEST_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(H8, WEST));

			Assert::IsFalse(destinationIsOnBoard(H8, WEST_NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(H8, NORTH_WEST));
			Assert::IsFalse(destinationIsOnBoard(H8, NORTH_NORTH_WEST));

			//B2
			Assert::IsTrue(destinationIsOnBoard(B2, NORTH));
			Assert::IsTrue(destinationIsOnBoard(B2, NORTH_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B2, NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B2, EAST_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B2, EAST));
			Assert::IsTrue(destinationIsOnBoard(B2, EAST_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B2, SOUTH_EAST));

			Assert::IsFalse(destinationIsOnBoard(B2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(B2, SOUTH));

			Assert::IsFalse(destinationIsOnBoard(B2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B2, SOUTH_WEST));

			Assert::IsFalse(destinationIsOnBoard(B2, WEST_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B2, WEST));

			Assert::IsFalse(destinationIsOnBoard(B2, WEST_NORTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B2, NORTH_WEST));

			//G2
			Assert::IsTrue(destinationIsOnBoard(G2, NORTH));
			Assert::IsTrue(destinationIsOnBoard(G2, NORTH_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(G2, NORTH_EAST));

			Assert::IsFalse(destinationIsOnBoard(G2, EAST_NORTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G2, EAST));

			Assert::IsFalse(destinationIsOnBoard(G2, EAST_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G2, SOUTH_EAST));

			Assert::IsFalse(destinationIsOnBoard(G2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G2, SOUTH));

			Assert::IsFalse(destinationIsOnBoard(G2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(G2, SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G2, WEST_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G2, WEST));
			Assert::IsTrue(destinationIsOnBoard(G2, WEST_NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G2, NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G2, NORTH_NORTH_WEST));

			//B7
			Assert::IsTrue(destinationIsOnBoard(B7, NORTH));

			Assert::IsFalse(destinationIsOnBoard(B7, NORTH_NORTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(B7, NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, EAST_NORTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, EAST_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(B7, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(B7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(B7, SOUTH_WEST));

			Assert::IsFalse(destinationIsOnBoard(B7, WEST_SOUTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B7, WEST));

			Assert::IsFalse(destinationIsOnBoard(B7, WEST_NORTH_WEST));

			Assert::IsTrue(destinationIsOnBoard(B7, NORTH_WEST));

			Assert::IsFalse(destinationIsOnBoard(B7, NORTH_NORTH_WEST));

			//G7
			Assert::IsTrue(destinationIsOnBoard(G7, NORTH));

			Assert::IsFalse(destinationIsOnBoard(G7, NORTH_NORTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G7, NORTH_EAST));

			Assert::IsFalse(destinationIsOnBoard(G7, EAST_NORTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G7, EAST));

			Assert::IsFalse(destinationIsOnBoard(G7, EAST_SOUTH_EAST));

			Assert::IsTrue(destinationIsOnBoard(G7, SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(G7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destinationIsOnBoard(G7, SOUTH));
			Assert::IsTrue(destinationIsOnBoard(G7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G7, SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G7, WEST_SOUTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G7, WEST));
			Assert::IsTrue(destinationIsOnBoard(G7, WEST_NORTH_WEST));
			Assert::IsTrue(destinationIsOnBoard(G7, NORTH_WEST));

			Assert::IsFalse(destinationIsOnBoard(G7, NORTH_NORTH_WEST));
		}
	};
}