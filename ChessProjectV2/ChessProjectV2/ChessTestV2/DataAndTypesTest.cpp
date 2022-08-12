#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"
#include "../ChessProjectV2/ChessBoardTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataAndTypesTests
{
	TEST_CLASS(DataAndTypesTesting)
	{
	public:
		TEST_METHOD(fenCharToColor)
		{
			Assert::IsTrue(White == getColorOfFenChar('D'));
			Assert::IsTrue(Black == getColorOfFenChar('d'));

			try {
				getColorOfFenChar('$');
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert Char to Color");
			}

			try {
				getColorOfFenChar('_', "Test Error Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Test Error Prefix Could not convert Char to Color");
			}
		}
		TEST_METHOD(fenCharToCastlingType)
		{
			Assert::IsTrue(CastleShort == getCastlingTypeOfFenChar('K'));
			Assert::IsTrue(CastleLong == getCastlingTypeOfFenChar('Q'));
			Assert::IsTrue(CastleShort == getCastlingTypeOfFenChar('k'));
			Assert::IsTrue(CastleLong == getCastlingTypeOfFenChar('q'));
			
			try {
				getColorOfFenChar('D');
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert Char to CastlingType");
			}

			try {
				getColorOfFenChar('E', "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert Char to CastlingType");
			}
		}
		TEST_METHOD(stringToSquare)
		{
			Assert::IsTrue(SQUARE_NONE == getSquareFromString("-"));
			Assert::IsTrue(A1 == getSquareFromString("a1"));
			Assert::IsTrue(H8 == getSquareFromString("h8"));
			Assert::IsTrue(E4 == getSquareFromString("e4"));
			Assert::IsTrue(D5 == getSquareFromString("d5"));
			Assert::IsTrue(D6 == getSquareFromString("d6"));
			Assert::IsTrue(D7 == getSquareFromString("d7"));
			Assert::IsTrue(D8 == getSquareFromString("d8"));

			try {
				getSquareFromString("a");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert String to Square");
			}

			try {
				getSquareFromString("a1", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				getSquareFromString("h9", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				getSquareFromString("i1", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				getSquareFromString("a0", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}
		}
	};
}