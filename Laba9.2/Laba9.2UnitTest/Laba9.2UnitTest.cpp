#include "pch.h"
#include "CppUnitTest.h"
#include "../Laba9.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Laba92UnitTest
{
	TEST_CLASS(Laba92UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 5;
			Student* p = new Student[N];
			p[1].phizika = 5;
			p[1].matesha = 4;
			p[1].program = 3;
			double actual;
			double exp = 4;
			actual = CalcAverageScore(p[1]);
			Assert::AreEqual(actual, exp);
		}
	};
}
