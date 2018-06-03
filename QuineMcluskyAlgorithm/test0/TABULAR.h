#pragma once

#define MAX_TABLE 15  // ���� ���쿡�� ������ �� �� �ִ� ���̺� ����
#include <string>

class Node
{
public:
	int digit;
	int *binary;
	int ones;
	bool check;
	bool minterms[65] = { false, };

	Node *next;
	friend class List;
};

class Result
{
public:
	Node *result[100];
	void deleteOverlap(int count,int result);
	void getEpi(int* ,int epiNum, int input_var,int);
};

class List
{
public:
	Node *list[MAX_TABLE];

	List()
	{
		for (int i = 0; i < MAX_TABLE; i++)
			list[i] = 0;
	}

	void AddData(int,int,int);
	int printData(int);
	void CompareData(int table_Number, int input_var, int numOfMinterm);
	bool checkList(int tableNumber);

	friend class Node;
};


void getBinary(Node *data);
