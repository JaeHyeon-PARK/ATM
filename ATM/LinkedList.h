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

void ListInit(List * plist); // ����Ʈ �ʱ�ȭ
void ascSort(List * plist, Node * nAcc); // �������� ����
void CreateAccount(List * plist, int & num); // ���� ����
void RemoveAccount(List * plist, int & num); // ���� ����
void ShowAllAccount(List * plist, int & num); // ��� ���� ���
int UserLogIn(List * plist, string id, string pw); // �Ϲݻ���� �α���

int Deposit(List * plist, string id, int money); // �Ա�
int Withdraw(List * plist, string id, string pw, int money); // ���
int Remmittance(List * plist, string receiveID, string sendID, string pw, int money); // �۱�
int Show(List * plist, string id, string pw); // ���� ��ȸ

void StoreData(List * plist); // ������ ����
void LoadData(List * plist, int &num); // ������ �ҷ�����

#endif