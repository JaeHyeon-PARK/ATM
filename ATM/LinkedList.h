#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include "Account.h"
using namespace std;

typedef struct node
{
	Account acc;
	node * link;
} Node;

typedef struct linkedList
{
	Node * head;
	Node * current;
	Node * prev;
} LinkedList;

typedef LinkedList List;

void ListInit(List * plist); // 리스트 초기화
void ascSort(List * plist, Node * nAcc); // 오름차순 정렬
void CreateAccount(List * plist, int & num); // 계좌 생성
void RemoveAccount(List * plist, int & num); // 계좌 삭제
void ShowAllAccount(List * plist, int & num); // 모든 정보 출력
int UserLogIn(List * plist, string id, string pw); // 일반사용자 로그인

int Deposit(List * plist, string id, int money); // 입금
int Withdraw(List * plist, string id, string pw, int money); // 출금
int Remmittance(List * plist, string receiveID, string sendID, string pw, int money); // 송금
int Show(List * plist, string id, string pw); // 정보 조회

void StoreData(List * plist); // 데이터 저장
void LoadData(List * plist, int &num); // 데이터 불러오기

#endif