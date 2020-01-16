#include <iostream>
#include <string>
#include "Account.h"
#include "LinkedList.h"
using namespace std;

void ShowAdminMenu(void); // 관리자메뉴 출력
void ShowUserMenu(void); // 일반사용자메뉴 출력

int main(void)
{
	int numOfData = 0; int &n = numOfData;
	int logIn = 1, mode;
	List list; // 계좌 연결리스트 생성
	string id, pw, rID;
	string adminId = "관리자", adminPw = "비밀번호";

	ListInit(&list); // 연결리스트의 초기화
	LoadData(&list, n); // 데이터 불러오기

	while (1)
	{
		cout << "1. 관리자    2. 일반이용자   3. 종료 >> "; cin >> mode; cout << endl;

		if (mode == 1)
		{
			while ((adminId != id) || (adminPw != pw))
			{
				cout << "---- 시작화면 (로그인) ----" << endl;
				cout << "ID(-1을 입력하면 초기화면으로 갑니다.) : "; cin >> id;
				if (id == "-1")
				{
					cout << "초기화면으로 돌아갑니다.\n" << endl;
					break;
				}
				cout << "비밀번호 : "; cin >> pw; cout << endl;
			}

			if ((id == adminId) && (pw == adminPw)) // 관리자 모드
			{
				logIn = 1;
				while (logIn)
				{
					int sel;
					ShowAdminMenu();

					cout << "메뉴 선택: "; cin >> sel; cout << endl;
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
						cout << "로그아웃을 합니다.\n" << endl;
						logIn = 0;
						break;
					default:
						cout << "잘못된 입력을 했습니다.\n" << endl;
						break;
					}
				}
			}
		}
		else if (mode == 2)
		{
			cout << "---- 시작화면 (로그인) ----" << endl;
			cout << "계좌번호(-1을 입력하면 초기화면으로 갑니다.) : "; cin >> id;
			if (id == "-1")
			{
				cout << "초기화면으로 돌아갑니다.\n" << endl;
				continue;
			}
			cout << "비밀번호 : "; cin >> pw; cout << endl;

			while (1)
			{
				logIn = UserLogIn(&list, id, pw);
				if (logIn == 1)
					break;
				else
				{
					cout << "계좌번호 혹은 비밀번호가 틀립니다.\n" << endl;
					break;
				}
			}

			while (logIn)
			{
				int sel;
				ShowUserMenu();

				cout << "메뉴 선택: "; cin >> sel; cout << endl;
				switch (sel)
				{
				case 1:
					int money;
					cout << "입금하실 금액을 입력하세요. >> "; cin >> money; cout << endl;
					Deposit(&list, id, money);
					break;
				case 2:
					cout << "비밀번호를 입력하세요. >> "; cin >> pw;
					cout << "출금하실 금액을 입력하세요. >> "; cin >> money; cout << endl;
					Withdraw(&list, id, pw, money);
					break;
				case 3:
					cout << "비밀번호를 입력하세요. >> "; cin >> pw;
					cout << "보내실 계좌를 입력하세요. >> "; cin >> rID;
					cout << "보내실 금액을 입력하세요. >> "; cin >> money; cout << endl;
					Remmittance(&list, rID, id, pw, money);
					break;
				case 4:
					cout << "비밀번호를 입력하세요. >> "; cin >> pw; cout << endl;
					Show(&list, id, pw);
					break;
				case 5:
					cout << "로그아웃을 합니다.\n" << endl;
					logIn = 0;
					break;
				default:
					cout << "잘못된 입력을 했습니다.\n" << endl;
					break;
				}
			}
		}
		else if (mode == 3)
		{
			StoreData(&list); // 데이터 저장
			cout << "프로그램을 종료합니다.\n" << endl;
			break;
		}
		else
			cout << "입력을 잘못하였습니다.\n" << endl;
	}

	return 0;
}

void ShowAdminMenu(void) // 관리자메뉴 출력
{
	cout << "---- 관리자 화면 ----" << endl;
	cout << "1. 계좌생성" << endl;
	cout << "2. 계좌삭제" << endl;
	cout << "3. 계좌조회" << endl;
	cout << "4. 로그아웃" << endl;
}

void ShowUserMenu(void) // 일반사용자메뉴 출력
{
	cout << "---- 일반사용자 화면 ----" << endl;
	cout << "1. 입금" << endl;
	cout << "2. 출금" << endl;
	cout << "3. 송금" << endl;
	cout << "4. 조회" << endl;
	cout << "5. 로그아웃" << endl;
}