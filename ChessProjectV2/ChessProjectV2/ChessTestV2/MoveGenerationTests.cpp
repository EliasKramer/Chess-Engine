#include "../ChessProjectV2/BitBoard.h"
#include "CppUnitTest.h"
#include "../ChessProjectV2/ChessBoardTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoveGenerationTest
{
	TEST_CLASS(MoveGenerationTest)
	{
	public:
		TEST_METHOD(generatingKingMoves)
		{
			ChessBoardTest board("8/8/8/8/4K3/8/8/8 w -- - 0 1");
			
			
		}
	};
}