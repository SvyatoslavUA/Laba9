#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Numbers { Single, Double };
string numbersStr[] = { "Одномісна", "Двомісна" };
struct Visitors
{
	string prizv;
	string init;
	Numbers numbers;

	int roomNumber;
};

void Create(Visitors* p, const int N)
{
	int numbers;
	for (int i = 0; i < N; i++)
	{
		cout << "Відвідувач № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " Прізвище: "; 
		getline(cin, p[i].prizv); 
		cout << "Введіть ініціали: " << endl;
		getline(cin, p[i].init);
		cout << " Номери (0 - Одномісна, 1 - Двомісна): ";
		cin >> numbers;

		p[i].numbers = (Numbers)numbers;
		switch (p[i].numbers)
		{
		case Single:
			cout << " Номер однієї з пяти кімнат: "; 
			cin >> p[i].roomNumber;
			break;
		case Double:
			cout << " Номер однієї з десяти кімнат: "; 
			cin >> p[i].roomNumber;
			break;
		}
		cout << endl;
	}
}


void Print(Visitors* p, const int N)
{
	cout << "========================================================================"
		<< endl;
	cout << "| № | Прізвище | Тип кімнати | Номер кімнати |"
		<< endl;
	cout << "------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(11) << left << numbersStr[p[i].numbers];
		switch (p[i].numbers)
		{
		case Single:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[i].roomNumber << " |" << endl;
			break;
		case Double:
			cout << "| " << setw(7) << setprecision(2) << fixed << left
				<< p[i].roomNumber << " |" << endl;
			break;
		}
		cout << "========================================================================"
			<< endl;
		cout << endl;
	}}int Search(Visitors* p, const int N, const string prizv)
{
	int counter = 0;
	int lastFindIndex = -1;
	for (int i = 0; i < N; i++)
	{
		if (p[i].prizv == prizv) {
			counter++;
			lastFindIndex = i;
		}
	}
	if (counter <= 1)
		return lastFindIndex;

	string init;

	cout << "Введіть ініціали: " << endl;
	cin >> init;
	for (int i = 0; i < N; i++) {
		if (p[i].prizv == prizv && p[i].init == init)
			return i;
	}
	return -1;
}	void SaveToFile(Visitors* p, const int N, const char* filename)
	{
		ofstream fout(filename); // відкрили бінарний файл запису
		fout.write((char*)&N, sizeof(N)); // записали кількість елементів
		for (int i = 0; i < N; i++)
			fout.write((char*)&p[i], sizeof(Visitors)); // записали елементи масиву
		fout.close(); // закрили файл
	}
	 
	void LoadFromFile(Visitors*& p, int& N, const char* filename)
	{
		delete[] p; // знищили попередні дані
		ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
		fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
		p = new Visitors[N]; // створили динамічний масив
		for (int i = 0; i < N; i++)
			fin.read((char*)&p[i], sizeof(Visitors)); // прочитали елементи масиву
		fin.close(); // закрили файл
	}	void Remove(Visitors* p, int& N, const string prizv)
	{
		int K = N - 1; // кількість елементів, які потрібно залишити
		Visitors* t = new Visitors[K]; // тимчасовий масив

		int Index = Search(p, N, prizv);

		for (int i = 0, j = 0; i < N - 1; i++) 
		{
			if (Index)
				continue;
			t[j] = p[i];
			j++;
		}

		p = t; // налаштовуємо вказівник на тимчасовий масив
		N = K; // змінюємо значення кількості елементів
	}int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість відвідувачів: "; cin >> N;

	Visitors* p = new Visitors[N];
	int Single;
	int Double;
	Numbers numbers;
	string prizv;
	int num;
	char filename[100];
	int find;
	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - пошук відвідувача за прізвищем" << endl;
		cout << " [4] - запис даних у файл" << endl;
		cout << " [5] - зчитування даних із файлу" << endl;
		cout << " [6] - видалення прізвищ" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; 
		cin >> menuItem;
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
			cin.get();
			cin.sync();

			cout << "Введіть прізвище шуканого відвідувача: "; 
			getline(cin, prizv);

			find = Search(p, N, prizv);

			if (find != -1)
			{
				cout << "Знайдено відвідувача в номері " << p[find].roomNumber << endl;
			}
			else
			{
				cout << "Шуканого відвідувача не знайдено" << endl;
			}
					break;
		case 4:
			cin.get();
			cin.sync();

			cout << "Введіть ім'я файлу: "; 
			cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 5:
			cin.get();
			cin.sync();

			cout << "Введіть ім'я файлу: "; 
			cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 6:
			cin.get();
			cin.sync();

			cout << "Введіть прізвище відвідувача якого потрібно видалити: ";
			getline(cin, prizv);

			Remove(p, N, prizv);

				cout << " Видалення успішно! " << endl;
			
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