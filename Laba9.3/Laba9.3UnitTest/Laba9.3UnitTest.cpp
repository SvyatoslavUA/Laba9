#include "pch.h"
#include "CppUnitTest.h"
#include "../Laba9.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Laba93UnitTest
{
	TEST_CLASS(Laba93UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 5;
			Visitors* p = new Visitors[N];
			p[1].prizv = "Tad";
			p[2].prizv = "Bat";
			double actual;
			double exp = 2;
			actual = Search(p, N, p[2].prizv);
			Assert::AreEqual(actual, exp);
		}
	};
}
