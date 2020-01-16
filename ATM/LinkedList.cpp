#include <string>
#include <fstream>
#include "LinkedList.h"

void ListInit(List * plist) // ����Ʈ �ʱ�ȭ
{
	plist->head = NULL;
	plist->current = NULL;
	plist->prev = NULL;
}

void ascSort(List * plist, Node * nAcc) // �������� ����
{
	plist->current = NULL; plist->prev = NULL;
	if (plist->head == NULL) // ù ������ ��
	{
		plist->head = nAcc;
		return;
	}

	if ((nAcc->acc.name) < (plist->head->acc.name)) // �� ������ �������������� head���� ���� ��
	{
		nAcc->link = plist->head;
		plist->head = nAcc;
	}
	else // �� ������ �������������� head���� ���� ��
	{
		plist->current = plist->head;
		while ((plist->current != NULL) && (nAcc->acc.name) >= (plist->current->acc.name)) // ������ ã���� ���
		{
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
		plist->prev->link = nAcc;
		nAcc->link = plist->current;
	}
}

void CreateAccount(List * plist, int & num) // ���� ����
{
	int overlap = 1; // ���¹�ȣ�� �ߺ�����
	int balance;
	string name, idNum, pw;

	cout << "�̸� �Է�: "; cin >> name;
	while (overlap)
	{
		cout << "���¹�ȣ �Է�: "; cin >> idNum;

		if (plist->head == NULL) // ù ���� ������ ���
			break;
		else // �ƴ� ���
		{
			plist->current = plist->head;
			plist->prev = NULL;

			while (plist->current)
			{
				if (plist->current->acc.idNumber == idNum) // �ߺ��� ��� ���¹�ȣ �Է� �ݺ�
				{
					overlap = 1;
					cout << "�ߺ��� ���¹�ȣ�Դϴ�." << endl;
					cout << endl;
					break;
				}
				else
					overlap = 0;
				plist->current = plist->current->link;
			}
		}
	}
	cout << "��й�ȣ �Է�: "; cin >> pw;
	cout << "�ݾ� �Է�: "; cin >> balance;

	Node * newAcc = new Node;
	newAcc->acc.getData(name, idNum, pw, balance); newAcc->link = NULL;
	ascSort(plist, newAcc);
	cout << endl << "���»����� �Ϸ�Ǿ����ϴ�.\n" << endl;
	num++;
}

void RemoveAccount(List * plist, int & num) // ���� ����
{
	string rIDNum;
	plist->current = plist->head;
	plist->prev = NULL;

	cout << "������ ���¹�ȣ �Է�: "; cin >> rIDNum;
	while (plist->current)
	{
		if (plist->current->acc.idNumber == rIDNum)
		{
			if (plist->prev)
				plist->prev->link = plist->current->link;
			else
				plist->head = plist->current->link;
			delete plist->current;
			cout << endl << "���»����� �Ϸ�Ǿ����ϴ�.\n" << endl;
			num--;
			return;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
}

void ShowAllAccount(List * plist, int & num) // ��� ���� ���
{
	plist->current = plist->head;

	cout << "�� ������ ������ �� >> " << num << endl;
	for (int i = 0; i<num; i++)
	{
		cout << "[ " << i + 1 << "��° ���� ���� ]" << endl;
		cout << "�̸�: " << plist->current->acc.name << endl;
		cout << "���¹�ȣ: " << plist->current->acc.idNumber << endl;
		cout << "��й�ȣ: " << plist->current->acc.password << endl;
		cout << "�ܾ�: " << plist->current->acc.balance << endl;
		cout << endl;
		plist->current = plist->current->link;
	}
}

int UserLogIn(List * plist, string id, string pw) // �Ϲݻ���� �α���
{
	plist->current = plist->head;
	plist->prev = NULL;

	while (plist->current)
	{
		if ((plist->current->acc.idNumber == id) && (plist->current->acc.password == pw))
			return 1;
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
	return 0;
}

int Deposit(List * plist, string id, int money) // �Ա�
{
	plist->current = plist->head;
	plist->prev = NULL;

	while (plist->current)
	{
		if (plist->current->acc.idNumber == id)
		{
			plist->current->acc.balance += money;
			cout << money << "���� �ԱݵǾ����ϴ�.\n" << endl;
			return 1;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
	return 0;
}

int Withdraw(List * plist, string id, string pw, int money) // ���
{
	int check = 0; // ��й�ȣ üũ
	plist->current = plist->head;
	plist->prev = NULL;
	
	while (plist->current)
	{
		if ((plist->current->acc.password) == pw)
		{
			check = 1;
			break;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
	if (check == 1)
	{
		plist->current = plist->head;
		plist->prev = NULL;

		while (plist->current)
		{
			if ((plist->current->acc.idNumber == id) && (plist->current->acc.password == pw))
			{
				plist->current->acc.balance -= money;
				cout << money << "���� ��ݵǾ����ϴ�.\n" << endl;
				return 1;
			}
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
	}
	else if (check == 0)
		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�.\n" << endl;
	return 0;
}

int Remmittance(List * plist, string receiveID, string sendID, string pw, int money) // �۱�
{
	int checkPW = 0, checkID = 0; // ��й�ȣ�� �޴� ���¸� �˻��ϱ����� ����
	plist->current = plist->head;
	plist->prev = NULL;
	while (plist->current)
	{
		if ((plist->current->acc.password) == pw)
		{
			checkPW = 1;
			break;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
	if (checkPW == 0)
		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�.\n" << endl;
	else if (checkPW == 1)
	{
		plist->current = plist->head;
		plist->prev = NULL;
		while (plist->current) // �޴� ������ ���� ���� �˻�
		{
			if (plist->current->acc.idNumber == receiveID)
			{
				checkID = 1;
				break;
			}
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
		if (checkID == 0)
		{
			cout << "�޴� ���°� �������� �ʽ��ϴ�.\n" << endl;
			return -1;
		}
		if (checkID == 1)
		{
			plist->current = plist->head;
			plist->prev = NULL;

			while (plist->current) // ������ ������ �ܾ� ����
			{
				if ((plist->current->acc.idNumber == sendID) && (plist->current->acc.password == pw))
				{
					plist->current->acc.balance -= money;
					break;
				}
				plist->prev = plist->current;
				plist->current = plist->current->link;
			}

			plist->current = plist->head;
			plist->prev = NULL;

			while (plist->current) // �޴� ������ �ܾ� ����
			{
				if (plist->current->acc.idNumber == receiveID)
				{
					plist->current->acc.balance += money;
					cout << money << "���� " << "���¹�ȣ " << receiveID << "���� �۱��߽��ϴ�.\n" << endl;
					checkID = 1;
					return 1;
				}
				plist->prev = plist->current;
				plist->current = plist->current->link;
			}
			return 1;
		}
	}
	return 0;
}

int Show(List * plist, string id, string pw) // ���� ��ȸ
{
	int check = 0;
	plist->current = plist->head;
	plist->prev = NULL;

	while (plist->current)
	{
		if ((plist->current->acc.password) == pw)
		{
			check = 1;
			break;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}

	plist->current = plist->head;
	plist->prev = NULL;

	if (check == 1)
	{
		while (plist->current)
		{
			if ((plist->current->acc.idNumber == id) && (plist->current->acc.password == pw))
			{
				cout << "---- ���� ���� ��� ----" << endl;
				cout << "�̸�: " << plist->current->acc.name << endl;
				cout << "���¹�ȣ: " << plist->current->acc.idNumber << endl;
				cout << "�ܾ�: " << plist->current->acc.balance << endl << endl;
				return 1;
			}
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
	}
	else if (check == 0)
		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�.\n" << endl;
	return 0;
}

void StoreData(List * plist) // ������ ����
{
	ofstream fout("data.txt");
	if (!fout)
	{
		cout << "���� ���� ����\n" << endl;
		return;
	}

	plist->current = plist->head;
	while (plist->current != NULL)
	{
		fout << plist->current->acc.name << "\n";
		fout << plist->current->acc.idNumber << "\n";
		fout << plist->current->acc.password << "\n";
		fout << plist->current->acc.balance << "\n";
		plist->current = plist->current->link;
	}
	cout << "���� ���� ����\n" << endl;
	fout.close();
}

void LoadData(List * plist, int &num) // ������ �ҷ�����
{
	string tName, tID, tPW;
	int tBalance;
	ifstream fin("data.txt");
	if (!fin)
	{
		cout << "���� ���� ����\n" << endl;
		return;
	}

	while (fin.eof() == 0)
	{
		Node * data = new node; data->link = NULL;
		getline(fin, tName); getline(fin, tID); getline(fin, tPW); fin >> tBalance; fin.ignore(1);
		if (tName == "")
			break;
		data->acc.name = tName; data->acc.idNumber = tID; data->acc.password = tPW; data->acc.balance = tBalance;

		if (plist->head == NULL)
			plist->head = data;
		else
		{
			plist->current = plist->head;
			while (plist->current->link != NULL)
				plist->current = plist->current->link;
			plist->current->link = data;
		}
		num++;
	}
	cout << "���� �ҷ����� ����\n" << endl;
	fin.close();
}