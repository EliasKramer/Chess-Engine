#include "CppUnitTest.h"
#include "../ChessProjectV2/HelpMethods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HelpMethodsTest
{
	TEST_CLASS(HelpMethodsTest)
	{
	public:
		TEST_METHOD(test_splitting_string_with_spaces)
		{
			std::string test_string = "this string is can be split into different parts";
			std::vector<std::string> exptected_result = 
			{ "this", "string", "is", "can", "be", "split", "into", "different", "parts" };
			
			std::vector<std::string> result = split_string(test_string, ' ');
			Assert::AreEqual(exptected_result.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(exptected_result[i], result[i]);
			}
		}
		TEST_METHOD(test_string_splitting_with_other_characters)
		{
			//split it with the character a
			std::string test_string = "it*can*even*be*split*with*other*characters";
			std::vector<std::string> expected_result = 
			{ "it", "can", "even", "be", "split", "with", "other", "characters" };
			
			std::vector<std::string> result = split_string(test_string, '*');
			Assert::AreEqual(expected_result.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(expected_result[i], result[i]);
			}
		}
		TEST_METHOD(test_string_splitting_with_multiple_chars)
		{
			//split it with the character a
			std::string test_string = "this!!string!!!has!!!!multiple!!split!chars";
			std::vector<std::string> expected_result =
				{ "this", "string", "has", "multiple", "split", "chars" };

			std::vector<std::string> result = split_string(test_string, '!');
			Assert::AreEqual(expected_result.size(), result.size());
			for (int i = 0; i < result.size(); i++)
			{
				Assert::AreEqual(expected_result[i], result[i]);
			}
		}
		TEST_METHOD(upper_and_lower_case_test)
		{
			Assert::IsTrue(is_upper_case('A'));
			Assert::IsTrue(is_upper_case('Q'));
			Assert::IsTrue(is_upper_case('Z'));

			Assert::IsFalse(is_upper_case('a'));
			Assert::IsFalse(is_upper_case('q'));
			Assert::IsFalse(is_upper_case('z'));

			Assert::IsTrue(is_lower_case('a'));
			Assert::IsTrue(is_lower_case('q'));
			Assert::IsTrue(is_lower_case('z'));
			
			Assert::IsFalse(is_lower_case('A'));
			Assert::IsFalse(is_lower_case('Q'));
			Assert::IsFalse(is_lower_case('Z'));
		}
		TEST_METHOD(to_lower_test)
		{
			Assert::IsTrue('a' == char_to_lower('A'));
			Assert::IsTrue('z' == char_to_lower('Z'));
		}
		TEST_METHOD(direction_testing)
		{
			Assert::IsTrue(NORTH == get_forward_for_color(white));
			Assert::IsTrue(SOUTH == get_forward_for_color(black));

			Assert::IsTrue(SOUTH == get_backward_for_color(white));
			Assert::IsTrue(NORTH == get_backward_for_color(black));
		}
		TEST_METHOD(opposite_color)
		{
			Assert::IsTrue(black == get_opposite_color(white));
			Assert::IsTrue(white == get_opposite_color(black));
		}
		TEST_METHOD(is_ray_type_test)
		{
			Assert::IsTrue(is_ray_type(rook));
			Assert::IsTrue(is_ray_type(bishop));
			Assert::IsTrue(is_ray_type(queen));
			
			Assert::IsFalse(is_ray_type(king));
			Assert::IsFalse(is_ray_type(pawn));
			Assert::IsFalse(is_ray_type(knight));
		}
		TEST_METHOD(positionIsValidTest)
		{
			//new position is too far left
			Assert::IsFalse(destination_is_on_board(A3, WEST));
			Assert::IsFalse(destination_is_on_board(A3, NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(A3, SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(A3, EAST));
			Assert::IsTrue(destination_is_on_board(A3, NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(A3, SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(A3, SOUTH));
			Assert::IsTrue(destination_is_on_board(A3, NORTH));

			//new position is too far right
			Assert::IsFalse(destination_is_on_board(H3, EAST));
			Assert::IsFalse(destination_is_on_board(H3, NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H3, SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(H3, WEST));
			Assert::IsTrue(destination_is_on_board(H3, NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(H3, SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(H3, SOUTH));
			Assert::IsTrue(destination_is_on_board(H3, NORTH));

			//new position is too far up
			Assert::IsFalse(destination_is_on_board(E8, NORTH));
			Assert::IsFalse(destination_is_on_board(E8, NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(E8, NORTH_WEST));

			Assert::IsTrue(destination_is_on_board(E8, SOUTH));
			Assert::IsTrue(destination_is_on_board(E8, SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(E8, SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(E8, EAST));
			Assert::IsTrue(destination_is_on_board(E8, WEST));

			//new position is too far down
			Assert::IsFalse(destination_is_on_board(E1, SOUTH));
			Assert::IsFalse(destination_is_on_board(E1, SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(E1, SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(E1, NORTH));
			Assert::IsTrue(destination_is_on_board(E1, NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(E1, NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(E1, EAST));
			Assert::IsTrue(destination_is_on_board(E1, WEST));

			//knights move is too far left
			Assert::IsFalse(destination_is_on_board(B3, WEST_NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(B3, WEST_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(B3, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(B3, NORTH_NORTH_WEST));

			//knights move is too far right
			Assert::IsFalse(destination_is_on_board(G3, EAST_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(G3, EAST_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(G3, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(G3, NORTH_NORTH_EAST));

			//left lower corner
			Assert::IsTrue(destination_is_on_board(A1, NORTH));
			Assert::IsTrue(destination_is_on_board(A1, NORTH_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(A1, NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(A1, EAST_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(A1, EAST));

			Assert::IsFalse(destination_is_on_board(A1, EAST_SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(A1, SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(A1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(A1, SOUTH));
			Assert::IsFalse(destination_is_on_board(A1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A1, SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A1, WEST_SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A1, WEST));
			Assert::IsFalse(destination_is_on_board(A1, WEST_NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(A1, NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(A1, NORTH_NORTH_WEST));

			//right lower corner
			Assert::IsTrue(destination_is_on_board(H1, NORTH));

			Assert::IsFalse(destination_is_on_board(H1, NORTH_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, EAST_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, EAST));
			Assert::IsFalse(destination_is_on_board(H1, EAST_SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(H1, SOUTH));
			Assert::IsFalse(destination_is_on_board(H1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(H1, SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(H1, WEST_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(H1, WEST));
			Assert::IsTrue(destination_is_on_board(H1, WEST_NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(H1, NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(H1, NORTH_NORTH_WEST));

			//left upper corner
			Assert::IsFalse(destination_is_on_board(A8, NORTH));
			Assert::IsFalse(destination_is_on_board(A8, NORTH_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(A8, NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(A8, EAST_NORTH_EAST));

			Assert::IsTrue(destination_is_on_board(A8, EAST));
			Assert::IsTrue(destination_is_on_board(A8, EAST_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(A8, SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(A8, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(A8, SOUTH));

			Assert::IsFalse(destination_is_on_board(A8, SOUTH_SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A8, SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A8, WEST_SOUTH_WEST));
			Assert::IsFalse(destination_is_on_board(A8, WEST));
			Assert::IsFalse(destination_is_on_board(A8, WEST_NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(A8, NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(A8, NORTH_NORTH_WEST));

			//right upper corner
			Assert::IsFalse(destination_is_on_board(H8, NORTH));
			Assert::IsFalse(destination_is_on_board(H8, NORTH_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H8, NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H8, EAST_NORTH_EAST));
			Assert::IsFalse(destination_is_on_board(H8, EAST));
			Assert::IsFalse(destination_is_on_board(H8, EAST_SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(H8, SOUTH_EAST));
			Assert::IsFalse(destination_is_on_board(H8, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(H8, SOUTH));
			Assert::IsTrue(destination_is_on_board(H8, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(H8, SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(H8, WEST_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(H8, WEST));

			Assert::IsFalse(destination_is_on_board(H8, WEST_NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(H8, NORTH_WEST));
			Assert::IsFalse(destination_is_on_board(H8, NORTH_NORTH_WEST));

			//B2
			Assert::IsTrue(destination_is_on_board(B2, NORTH));
			Assert::IsTrue(destination_is_on_board(B2, NORTH_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(B2, NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(B2, EAST_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(B2, EAST));
			Assert::IsTrue(destination_is_on_board(B2, EAST_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(B2, SOUTH_EAST));

			Assert::IsFalse(destination_is_on_board(B2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(B2, SOUTH));

			Assert::IsFalse(destination_is_on_board(B2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(B2, SOUTH_WEST));

			Assert::IsFalse(destination_is_on_board(B2, WEST_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(B2, WEST));

			Assert::IsFalse(destination_is_on_board(B2, WEST_NORTH_WEST));

			Assert::IsTrue(destination_is_on_board(B2, NORTH_WEST));

			//G2
			Assert::IsTrue(destination_is_on_board(G2, NORTH));
			Assert::IsTrue(destination_is_on_board(G2, NORTH_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(G2, NORTH_EAST));

			Assert::IsFalse(destination_is_on_board(G2, EAST_NORTH_EAST));

			Assert::IsTrue(destination_is_on_board(G2, EAST));

			Assert::IsFalse(destination_is_on_board(G2, EAST_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(G2, SOUTH_EAST));

			Assert::IsFalse(destination_is_on_board(G2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(G2, SOUTH));

			Assert::IsFalse(destination_is_on_board(G2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(G2, SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(G2, WEST_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(G2, WEST));
			Assert::IsTrue(destination_is_on_board(G2, WEST_NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(G2, NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(G2, NORTH_NORTH_WEST));

			//B7
			Assert::IsTrue(destination_is_on_board(B7, NORTH));

			Assert::IsFalse(destination_is_on_board(B7, NORTH_NORTH_EAST));

			Assert::IsTrue(destination_is_on_board(B7, NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(B7, EAST_NORTH_EAST));
			Assert::IsTrue(destination_is_on_board(B7, EAST));
			Assert::IsTrue(destination_is_on_board(B7, EAST_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(B7, SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(B7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(B7, SOUTH));
			Assert::IsTrue(destination_is_on_board(B7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(B7, SOUTH_WEST));

			Assert::IsFalse(destination_is_on_board(B7, WEST_SOUTH_WEST));

			Assert::IsTrue(destination_is_on_board(B7, WEST));

			Assert::IsFalse(destination_is_on_board(B7, WEST_NORTH_WEST));

			Assert::IsTrue(destination_is_on_board(B7, NORTH_WEST));

			Assert::IsFalse(destination_is_on_board(B7, NORTH_NORTH_WEST));

			//G7
			Assert::IsTrue(destination_is_on_board(G7, NORTH));

			Assert::IsFalse(destination_is_on_board(G7, NORTH_NORTH_EAST));

			Assert::IsTrue(destination_is_on_board(G7, NORTH_EAST));

			Assert::IsFalse(destination_is_on_board(G7, EAST_NORTH_EAST));

			Assert::IsTrue(destination_is_on_board(G7, EAST));

			Assert::IsFalse(destination_is_on_board(G7, EAST_SOUTH_EAST));

			Assert::IsTrue(destination_is_on_board(G7, SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(G7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(destination_is_on_board(G7, SOUTH));
			Assert::IsTrue(destination_is_on_board(G7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(G7, SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(G7, WEST_SOUTH_WEST));
			Assert::IsTrue(destination_is_on_board(G7, WEST));
			Assert::IsTrue(destination_is_on_board(G7, WEST_NORTH_WEST));
			Assert::IsTrue(destination_is_on_board(G7, NORTH_WEST));

			Assert::IsFalse(destination_is_on_board(G7, NORTH_NORTH_WEST));
		}
	};
}