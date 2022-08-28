#include "CppUnitTest.h"
#include "../ChessProjectV2/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoveTest
{
	TEST_CLASS(MoveTest)
	{
	public:

		TEST_METHOD(moveBasicFunctions)
		{
			Move m(A1, B3);
			Assert::IsTrue(A1 == m.getStart());
			Assert::IsTrue(B3 == m.getDestination());
			
			Move sameMove(A1, B3);
			Move differentStart(A2, B3);
			Move differentDestination(A1, B4);
			Move differentMove(A2, B4);

			Assert::IsTrue(m == sameMove);
			Assert::IsFalse(m == differentStart);
			Assert::IsFalse(m == differentDestination);
			Assert::IsFalse(m == differentMove);

			Assert::IsFalse(m != sameMove);
			Assert::IsTrue(m != differentStart);
			Assert::IsTrue(m != differentDestination);
			Assert::IsTrue(m != differentMove);
		}
	};
}	