#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessBoardTest
{
	TEST_CLASS(ChessBoardTest)
	{
	public:

		TEST_METHOD(setupBoard)
		{
			ChessBoard board;
			board.setupBoard();
			
		}
	};
}