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
		TEST_METHOD(fen_char_to_color)
		{
			Assert::IsTrue(white == get_color_of_fen_char('D'));
			Assert::IsTrue(black == get_color_of_fen_char('d'));

			try {
				get_color_of_fen_char('$');
				Assert::Fail();
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert Char to Color");
			}

			try {
				get_color_of_fen_char('_', "Test Error Prefix");
				Assert::Fail();
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Test Error Prefix Could not convert Char to Color");
			}
		}
		TEST_METHOD(fen_char_to_castling_type)
		{
			Assert::IsTrue(castle_short == get_castling_type_of_fen_char('K'));
			Assert::IsTrue(castle_long == get_castling_type_of_fen_char('Q'));
			Assert::IsTrue(castle_short == get_castling_type_of_fen_char('k'));
			Assert::IsTrue(castle_long == get_castling_type_of_fen_char('q'));
			
			try {
				get_color_of_fen_char('D');
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert Char to CastlingType");
			}

			try {
				get_color_of_fen_char('E', "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert Char to CastlingType");
			}
		}
		TEST_METHOD(string_to_square)
		{
			Assert::IsTrue(SQUARE_NONE == get_square_from_string("-"));
			Assert::IsTrue(A1 == get_square_from_string("a1"));
			Assert::IsTrue(H8 == get_square_from_string("h8"));
			Assert::IsTrue(E4 == get_square_from_string("e4"));
			Assert::IsTrue(D5 == get_square_from_string("d5"));
			Assert::IsTrue(D6 == get_square_from_string("d6"));
			Assert::IsTrue(D7 == get_square_from_string("d7"));
			Assert::IsTrue(D8 == get_square_from_string("d8"));

			try {
				get_square_from_string("a");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR Could not convert String to Square");
			}

			try {
				get_square_from_string("a1", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				get_square_from_string("h9", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				get_square_from_string("i1", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}

			try {
				get_square_from_string("a0", "Error Msg Prefix");
			}
			catch (const std::string& errorMsg)
			{
				Assert::IsTrue(errorMsg == "Error Msg Prefix Could not convert String to Square");
			}
		}
	};
}