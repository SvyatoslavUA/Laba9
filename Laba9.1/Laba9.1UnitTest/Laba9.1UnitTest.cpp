#include "pch.h"
#include "CppUnitTest.h"
#include "../Laba9.1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Laba91UnitTest
{
	TEST_CLASS(Laba91UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 5;
			Student* p = new Student[N];
			GenerateTestStudents(p, N);
			double actual;
			double exp = 1;
			actual = FindStudentsWithFive(p, N);
			Assert::AreEqual(actual, exp);
		}
		void GenerateTestStudents(Student* p, int const N)
		{
			for (int i = 0; i < N; i++) {
				p[i].phizika = 2;
			}
			p[N - 1].phizika = 5;
		}
	};
}
