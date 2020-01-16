#include <string>
#include <fstream>
#include "LinkedList.h"

void ListInit(List * plist) // 리스트 초기화
{
	plist->head = NULL;
	plist->current = NULL;
	plist->prev = NULL;
}

void ascSort(List * plist, Node * nAcc) // 오름차순 정렬
{
	plist->current = NULL; plist->prev = NULL;
	if (plist->head == NULL) // 첫 계좌일 때
	{
		plist->head = nAcc;
		return;
	}

	if ((nAcc->acc.name) < (plist->head->acc.name)) // 새 계좌의 사전편찬순위가 head보다 낮을 때
	{
		nAcc->link = plist->head;
		plist->head = nAcc;
	}
	else // 새 계좌의 사전편찬순위가 head보다 높을 때
	{
		plist->current = plist->head;
		while ((plist->current != NULL) && (nAcc->acc.name) >= (plist->current->acc.name)) // 순위를 찾았을 경우
		{
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
		plist->prev->link = nAcc;
		nAcc->link = plist->current;
	}
}

void CreateAccount(List * plist, int & num) // 계좌 생성
{
	int overlap = 1; // 계좌번호의 중복여부
	int balance;
	string name, idNum, pw;

	cout << "이름 입력: "; cin >> name;
	while (overlap)
	{
		cout << "계좌번호 입력: "; cin >> idNum;

		if (plist->head == NULL) // 첫 계좌 생성일 경우
			break;
		else // 아닐 경우
		{
			plist->current = plist->head;
			plist->prev = NULL;

			while (plist->current)
			{
				if (plist->current->acc.idNumber == idNum) // 중복될 경우 계좌번호 입력 반복
				{
					overlap = 1;
					cout << "중복된 계좌번호입니다." << endl;
					cout << endl;
					break;
				}
				else
					overlap = 0;
				plist->current = plist->current->link;
			}
		}
	}
	cout << "비밀번호 입력: "; cin >> pw;
	cout << "금액 입력: "; cin >> balance;

	Node * newAcc = new Node;
	newAcc->acc.getData(name, idNum, pw, balance); newAcc->link = NULL;
	ascSort(plist, newAcc);
	cout << endl << "계좌생성이 완료되었습니다.\n" << endl;
	num++;
}

void RemoveAccount(List * plist, int & num) // 계좌 삭제
{
	string rIDNum;
	plist->current = plist->head;
	plist->prev = NULL;

	cout << "삭제할 계좌번호 입력: "; cin >> rIDNum;
	while (plist->current)
	{
		if (plist->current->acc.idNumber == rIDNum)
		{
			if (plist->prev)
				plist->prev->link = plist->current->link;
			else
				plist->head = plist->current->link;
			delete plist->current;
			cout << endl << "계좌삭제가 완료되었습니다.\n" << endl;
			num--;
			return;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
}

void ShowAllAccount(List * plist, int & num) // 모든 정보 출력
{
	plist->current = plist->head;

	cout << "총 생성된 계좌의 수 >> " << num << endl;
	for (int i = 0; i<num; i++)
	{
		cout << "[ " << i + 1 << "번째 계좌 정보 ]" << endl;
		cout << "이름: " << plist->current->acc.name << endl;
		cout << "계좌번호: " << plist->current->acc.idNumber << endl;
		cout << "비밀번호: " << plist->current->acc.password << endl;
		cout << "잔액: " << plist->current->acc.balance << endl;
		cout << endl;
		plist->current = plist->current->link;
	}
}

int UserLogIn(List * plist, string id, string pw) // 일반사용자 로그인
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

int Deposit(List * plist, string id, int money) // 입금
{
	plist->current = plist->head;
	plist->prev = NULL;

	while (plist->current)
	{
		if (plist->current->acc.idNumber == id)
		{
			plist->current->acc.balance += money;
			cout << money << "원이 입금되었습니다.\n" << endl;
			return 1;
		}
		plist->prev = plist->current;
		plist->current = plist->current->link;
	}
	return 0;
}

int Withdraw(List * plist, string id, string pw, int money) // 출금
{
	int check = 0; // 비밀번호 체크
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
				cout << money << "원이 출금되었습니다.\n" << endl;
				return 1;
			}
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
	}
	else if (check == 0)
		cout << "비밀번호가 틀렸습니다.\n" << endl;
	return 0;
}

int Remmittance(List * plist, string receiveID, string sendID, string pw, int money) // 송금
{
	int checkPW = 0, checkID = 0; // 비밀번호와 받는 계좌를 검사하기위한 변수
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
		cout << "비밀번호가 틀렸습니다.\n" << endl;
	else if (checkPW == 1)
	{
		plist->current = plist->head;
		plist->prev = NULL;
		while (plist->current) // 받는 계좌의 존재 유무 검사
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
			cout << "받는 계좌가 존재하지 않습니다.\n" << endl;
			return -1;
		}
		if (checkID == 1)
		{
			plist->current = plist->head;
			plist->prev = NULL;

			while (plist->current) // 보내는 계좌의 잔액 감소
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

			while (plist->current) // 받는 계좌의 잔액 증가
			{
				if (plist->current->acc.idNumber == receiveID)
				{
					plist->current->acc.balance += money;
					cout << money << "원을 " << "계좌번호 " << receiveID << "에게 송금했습니다.\n" << endl;
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

int Show(List * plist, string id, string pw) // 정보 조회
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
				cout << "---- 계좌 정보 출력 ----" << endl;
				cout << "이름: " << plist->current->acc.name << endl;
				cout << "계좌번호: " << plist->current->acc.idNumber << endl;
				cout << "잔액: " << plist->current->acc.balance << endl << endl;
				return 1;
			}
			plist->prev = plist->current;
			plist->current = plist->current->link;
		}
	}
	else if (check == 0)
		cout << "비밀번호가 틀렸습니다.\n" << endl;
	return 0;
}

void StoreData(List * plist) // 데이터 저장
{
	ofstream fout("data.txt");
	if (!fout)
	{
		cout << "파일 열기 실패\n" << endl;
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
	cout << "파일 저장 성공\n" << endl;
	fout.close();
}

void LoadData(List * plist, int &num) // 데이터 불러오기
{
	string tName, tID, tPW;
	int tBalance;
	ifstream fin("data.txt");
	if (!fin)
	{
		cout << "파일 열기 실패\n" << endl;
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
	cout << "파일 불러오기 성공\n" << endl;
	fin.close();
}