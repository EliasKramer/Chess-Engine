#include "../ChessProjectV2/Medicrius.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MedicriusTest
{
	TEST_CLASS(MedicriusTest)
	{
	public:
		TEST_METHOD(testEvaluation)
		{
			Medicrius medicrius;

			/*ChessBoard board("8/7k/8/K7/8/8/8/8 w - - 0 1");
			Assert::AreEqual(0, medicrius.evaluateBoard(board));
			
			board = ChessBoard("8/7k/8/K7/8/8/8/8 b - - 0 1");
			Assert::AreEqual(0, medicrius.evaluateBoard(board));
			
			board = ChessBoard("8/1q6/8/5k2/8/8/4r3/K7 w - - 0 1");
			Assert::AreEqual(0, medicrius.evaluateBoard(board));
			
			board = ChessBoard("8/1q6/8/5k2/8/8/4r3/K7 b - - 0 1");
			Assert::AreNotEqual(0, medicrius.evaluateBoard(board));*/
		}
	};
}