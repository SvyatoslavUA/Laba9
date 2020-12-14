#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Numbers { Single, Double };
string numbersStr[] = { "��������", "�������" };
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
		cout << "³������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " �������: "; 
		getline(cin, p[i].prizv); 
		cout << "������ �������: " << endl;
		getline(cin, p[i].init);
		cout << " ������ (0 - ��������, 1 - �������): ";
		cin >> numbers;

		p[i].numbers = (Numbers)numbers;
		switch (p[i].numbers)
		{
		case Single:
			cout << " ����� ���� � ���� �����: "; 
			cin >> p[i].roomNumber;
			break;
		case Double:
			cout << " ����� ���� � ������ �����: "; 
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
	cout << "| � | ������� | ��� ������ | ����� ������ |"
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

	cout << "������ �������: " << endl;
	cin >> init;
	for (int i = 0; i < N; i++) {
		if (p[i].prizv == prizv && p[i].init == init)
			return i;
	}
	return -1;
}	void SaveToFile(Visitors* p, const int N, const char* filename)
	{
		ofstream fout(filename); // ������� ������� ���� ������
		fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
		for (int i = 0; i < N; i++)
			fout.write((char*)&p[i], sizeof(Visitors)); // �������� �������� ������
		fout.close(); // ������� ����
	}
	 
	void LoadFromFile(Visitors*& p, int& N, const char* filename)
	{
		delete[] p; // ������� �������� ���
		ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
		fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
		p = new Visitors[N]; // �������� ��������� �����
		for (int i = 0; i < N; i++)
			fin.read((char*)&p[i], sizeof(Visitors)); // ��������� �������� ������
		fin.close(); // ������� ����
	}	void Remove(Visitors* p, int& N, const string prizv)
	{
		int K = N - 1; // ������� ��������, �� ������� ��������
		Visitors* t = new Visitors[K]; // ���������� �����

		int Index = Search(p, N, prizv);

		for (int i = 0, j = 0; i < N - 1; i++) 
		{
			if (Index)
				continue;
			t[j] = p[i];
			j++;
		}

		p = t; // ����������� �������� �� ���������� �����
		N = K; // ������� �������� ������� ��������
	}int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ����������: "; cin >> N;

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
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ����� ��������� �� ��������" << endl;
		cout << " [4] - ����� ����� � ����" << endl;
		cout << " [5] - ���������� ����� �� �����" << endl;
		cout << " [6] - ��������� ������" << endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; 
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

			cout << "������ ������� �������� ���������: "; 
			getline(cin, prizv);

			find = Search(p, N, prizv);

			if (find != -1)
			{
				cout << "�������� ��������� � ����� " << p[find].roomNumber << endl;
			}
			else
			{
				cout << "�������� ��������� �� ��������" << endl;
			}
					break;
		case 4:
			cin.get();
			cin.sync();

			cout << "������ ��'� �����: "; 
			cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 5:
			cin.get();
			cin.sync();

			cout << "������ ��'� �����: "; 
			cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 6:
			cin.get();
			cin.sync();

			cout << "������ ������� ��������� ����� ������� ��������: ";
			getline(cin, prizv);

			Remove(p, N, prizv);

				cout << " ��������� ������! " << endl;
			
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}