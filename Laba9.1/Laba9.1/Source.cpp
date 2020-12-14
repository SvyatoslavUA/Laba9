#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { IT, IF, RT };
string specialnistStr[] = { "ІТ", "ІФ", "РТ" };
struct Student
{
	string prizv;
	unsigned kurs;
	unsigned matesha;
	unsigned phizika;
	Specialnist specialnist;
	union
	{
		int program;
		int methods;
		int pedagog;
	};
};

void Create(Student* p, const int N)
{
	int specialnist;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " Прізвище: "; getline(cin, p[i].prizv);
		cout << " Курс: "; cin >> p[i].kurs;
		cout << " Спеціальність (0 - IT, 1 - ІФ, 2 - РТ): ";
		cin >> specialnist;
		cout << " Математика: "; cin >> p[i].matesha;
		cout << " Фізика: "; cin >> p[i].phizika;

		p[i].specialnist = (Specialnist)specialnist;
		switch (p[i].specialnist)
		{
		case IT:
			cout << " Програмування : "; cin >> p[i].program;
			break;
		case IF :
			cout << " Чисельних методів : "; cin >> p[i].methods;
			break;
		case RT:
			cout << " Педагогіка : "; cin >> p[i].pedagog;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Математика | Фізика | Предмет |"
		<< endl;
	cout << "------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << left << p[i].kurs << " "
			<< "| " << setw(14) << left << specialnistStr[p[i].specialnist]
			<< "| " << setw(10) << left << p[i].matesha << " "
			<< "| " << setw(7) << left << p[i].phizika;
		switch (p[i].specialnist)
		{
		case IT:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[i].program << " |" <<  endl;
			break;
		case IF:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[i].methods << " |" <<  endl;
			break;
		case RT:
			cout << "| " << setw(7) << right << "|" << " " << setw(8) << left
				<< p[i].pedagog << endl;
			break;
		}
	}
	cout << "========================================================================"
		<< endl;
		cout << endl;
}

double CalcAverageScore(Student p)
{
	int sum = p.matesha + p.phizika + p.program;
	return sum / 3.0;
}


void FindGoodStudents(Student* p, const int N)
{
	int res = 0;
	for (int i = 0; i < N; i++)
	{
		if (CalcAverageScore(p[i]) > 3)
		{
			++res;
			if(res == 1)
				cout << "Прізвища студентів що вчаться добре: " << endl;

			cout << setw(3) << right << res
				<< " " << p[i].prizv << endl;
		}
	}
	if(res == 0)
		cout << "Хороших студентів не знайдено" << endl;
}

int FindStudentsWithFive(Student* p, const int N)
{
	int res = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].phizika == 5)
		{
			res++;
		}

	}
	return res;
}int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 

	int N;
	cout << "Введіть кількість студентів: "; cin >> N;

	Student* p = new Student[N];
	Create(p, N);
	Print(p, N);

	FindGoodStudents(p, N);

	cout << "Кількість студентів, які мають 5 з фізики: " << endl;
	cout << FindStudentsWithFive(p, N) << endl;

	return 0;
}