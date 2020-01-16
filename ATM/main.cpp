#include <iostream>
#include <string>
#include "Account.h"
#include "LinkedList.h"
using namespace std;

void ShowAdminMenu(void); // �����ڸ޴� ���
void ShowUserMenu(void); // �Ϲݻ���ڸ޴� ���

int main(void)
{
	int numOfData = 0; int &n = numOfData;
	int logIn = 1, mode;
	List list; // ���� ���Ḯ��Ʈ ����
	string id, pw, rID;
	string adminId = "������", adminPw = "��й�ȣ";

	ListInit(&list); // ���Ḯ��Ʈ�� �ʱ�ȭ
	LoadData(&list, n); // ������ �ҷ�����

	while (1)
	{
		cout << "1. ������    2. �Ϲ��̿���   3. ���� >> "; cin >> mode; cout << endl;

		if (mode == 1)
		{
			while ((adminId != id) || (adminPw != pw))
			{
				cout << "---- ����ȭ�� (�α���) ----" << endl;
				cout << "ID(-1�� �Է��ϸ� �ʱ�ȭ������ ���ϴ�.) : "; cin >> id;
				if (id == "-1")
				{
					cout << "�ʱ�ȭ������ ���ư��ϴ�.\n" << endl;
					break;
				}
				cout << "��й�ȣ : "; cin >> pw; cout << endl;
			}

			if ((id == adminId) && (pw == adminPw)) // ������ ���
			{
				logIn = 1;
				while (logIn)
				{
					int sel;
					ShowAdminMenu();

					cout << "�޴� ����: "; cin >> sel; cout << endl;
					switch (sel)
					{
					case 1:
						CreateAccount(&list, n);
						break;
					case 2:
						RemoveAccount(&list, n);
						break;
					case 3:
						ShowAllAccount(&list, n);
						break;
					case 4:
						cout << "�α׾ƿ��� �մϴ�.\n" << endl;
						logIn = 0;
						break;
					default:
						cout << "�߸��� �Է��� �߽��ϴ�.\n" << endl;
						break;
					}
				}
			}
		}
		else if (mode == 2)
		{
			cout << "---- ����ȭ�� (�α���) ----" << endl;
			cout << "���¹�ȣ(-1�� �Է��ϸ� �ʱ�ȭ������ ���ϴ�.) : "; cin >> id;
			if (id == "-1")
			{
				cout << "�ʱ�ȭ������ ���ư��ϴ�.\n" << endl;
				continue;
			}
			cout << "��й�ȣ : "; cin >> pw; cout << endl;

			while (1)
			{
				logIn = UserLogIn(&list, id, pw);
				if (logIn == 1)
					break;
				else
				{
					cout << "���¹�ȣ Ȥ�� ��й�ȣ�� Ʋ���ϴ�.\n" << endl;
					break;
				}
			}

			while (logIn)
			{
				int sel;
				ShowUserMenu();

				cout << "�޴� ����: "; cin >> sel; cout << endl;
				switch (sel)
				{
				case 1:
					int money;
					cout << "�Ա��Ͻ� �ݾ��� �Է��ϼ���. >> "; cin >> money; cout << endl;
					Deposit(&list, id, money);
					break;
				case 2:
					cout << "��й�ȣ�� �Է��ϼ���. >> "; cin >> pw;
					cout << "����Ͻ� �ݾ��� �Է��ϼ���. >> "; cin >> money; cout << endl;
					Withdraw(&list, id, pw, money);
					break;
				case 3:
					cout << "��й�ȣ�� �Է��ϼ���. >> "; cin >> pw;
					cout << "������ ���¸� �Է��ϼ���. >> "; cin >> rID;
					cout << "������ �ݾ��� �Է��ϼ���. >> "; cin >> money; cout << endl;
					Remmittance(&list, rID, id, pw, money);
					break;
				case 4:
					cout << "��й�ȣ�� �Է��ϼ���. >> "; cin >> pw; cout << endl;
					Show(&list, id, pw);
					break;
				case 5:
					cout << "�α׾ƿ��� �մϴ�.\n" << endl;
					logIn = 0;
					break;
				default:
					cout << "�߸��� �Է��� �߽��ϴ�.\n" << endl;
					break;
				}
			}
		}
		else if (mode == 3)
		{
			StoreData(&list); // ������ ����
			cout << "���α׷��� �����մϴ�.\n" << endl;
			break;
		}
		else
			cout << "�Է��� �߸��Ͽ����ϴ�.\n" << endl;
	}

	return 0;
}

void ShowAdminMenu(void) // �����ڸ޴� ���
{
	cout << "---- ������ ȭ�� ----" << endl;
	cout << "1. ���»���" << endl;
	cout << "2. ���»���" << endl;
	cout << "3. ������ȸ" << endl;
	cout << "4. �α׾ƿ�" << endl;
}

void ShowUserMenu(void) // �Ϲݻ���ڸ޴� ���
{
	cout << "---- �Ϲݻ���� ȭ�� ----" << endl;
	cout << "1. �Ա�" << endl;
	cout << "2. ���" << endl;
	cout << "3. �۱�" << endl;
	cout << "4. ��ȸ" << endl;
	cout << "5. �α׾ƿ�" << endl;
}