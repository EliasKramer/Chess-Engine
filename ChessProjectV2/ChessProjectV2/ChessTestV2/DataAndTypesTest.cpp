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
	};
}