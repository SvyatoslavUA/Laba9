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
		case IF:
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
				<< p[i].program << " |" << endl;
			break;
		case IF:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[i].methods << " |" << endl;
			break;
		case RT:
			cout << "| " << setw(7) << right << setw(8) << left
				<< p[i].pedagog << " |" << endl;
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
	return sum / 3;
}


void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].specialnist > p[i1 + 1].specialnist)
				||
				(p[i1].specialnist == p[i1 + 1].specialnist &&
					CalcAverageScore(p[i1]) > CalcAverageScore(p[i1 + 1]))
				||
				(p[i1].specialnist == p[i1 + 1].specialnist &&
				    CalcAverageScore(p[i1]) == CalcAverageScore(p[i1 + 1]) && 
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
					p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[i].specialnist > p[i + 1].specialnist)
				||
				(p[i].specialnist == p[i + 1].specialnist &&
					CalcAverageScore(p[i]) > CalcAverageScore(p[i + 1]))
				||
				(p[i].specialnist == p[i + 1].specialnist &&
					CalcAverageScore(p[i]) == CalcAverageScore(p[i + 1]) && 
					p[i].prizv > p[i + 1].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "========================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Математика | Фізика | Предмет |"
		<< endl;
	cout << "------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(11) << left << specialnistStr[p[I[i]].specialnist]
		<< "| " << setw(10) << left << p[i].matesha << " "
			<< "| " << setw(7) << left << p[i].phizika;
		switch (p[I[i]].specialnist)
		{
		case IT:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[I[i]].program << " |" << endl;
			break;
		case IF:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[I[i]].methods << " |" << endl;
			break;
		case RT:
			cout << "| " << setw(7) << right << setw(8) << left
				<< p[I[i]].pedagog << " |" << endl;
			break;
		}
	}
	cout << "========================================================================"
		<< endl;
	cout << endl;
}int BinSearch(Student* p, const int N, const string prizv, const Specialnist specialnist)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].specialnist == specialnist)
			return m;
		if ((p[m].specialnist < specialnist)
			||
			(p[m].specialnist == specialnist &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispecialnist;
	Specialnist specialnist;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук працівника за посадою та прізвищем" << endl;
		cout << " [5] - індексне впорядкування та вивід даних"
			<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Спеціальність (0 - IT, 1 - ІФ, 2 - РТ): ";
			cin >> ispecialnist;
			specialnist = (Specialnist)ispecialnist;
			cin.get();
			cin.sync(); 

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, specialnist)) != -1)
				cout << "Знайдено стулента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}