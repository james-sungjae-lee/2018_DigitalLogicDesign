#include "TABULAR.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void List::AddData(int table_Number,int minterm,int input_var)
{
	Node *newNode = new Node();
	Node *temp = list[table_Number];

	newNode->binary = new int[input_var];  // binary
	newNode->digit = minterm;
	newNode->check = false;
	newNode->minterms[minterm] = true;
	newNode->next = 0;

	for (int j = 0; j < input_var; j++)
	{
		newNode->binary[j] = 0;
	}

	getBinary(newNode);

	if (temp == 0)
	{
		list[table_Number] = newNode;
		//cout << "temp == 0" << endl;
	}
	else if(temp->next ==0 && temp != 0)
	{
		newNode->next = temp->next;
		temp->next = newNode;
		//cout << "temp->next ==0 && temp != 0" << endl;
	}
	else
	{
		newNode->next = temp->next;
		temp->next = newNode;
		//cout << "temp->next !=0 && temp != 0" << endl;
	}

	return;
}


void List::CompareData(int table_Number, int input_var, int numOfminterms)
{
	Node *curp = list[table_Number];
	Node *nextp = list[table_Number];

	Node *getP = list[table_Number + 1];	// new table

	int binarySize = input_var;
	int count = 0; // �ٸ����� ������ ã�� ī��Ʈ��

	while (curp->next != NULL || nextp != NULL)
	{
		if (abs(curp->ones - nextp->ones) == 1)  // ones ����
		{
			for (int i = 0; i < binarySize; i++)
			{
				if (curp->binary[i] != nextp->binary[i])
				{
					count++;
				}
			} // count ��

			if (count == 1)
			{
				//cout << curp->digit << ' ' << nextp->digit << endl;
				count = 0; // count �� �ʱ�ȭ
				int i = 0;
				Node *newNode = new Node();

				newNode->binary = new int[input_var];  // binary
				newNode->digit = -1;
				newNode->check = false;
				newNode->next = 0;
				for (int t = 0; t < 65; t++)
				{
					if ((curp->minterms[t] || nextp->minterms[t]) == true)
						newNode->minterms[t] = true;
				}

				// ���� �ʱ�ȭ
				for (i = binarySize; i >=0; i--)
				{
					if (curp->binary[i] == nextp->binary[i] && curp->binary[i] == 1)
					{
						newNode->binary[i] = 1;
						newNode->ones++;
						//cout << "1����" << endl;
					}
					else if (curp->binary[i] == nextp->binary[i] && curp->binary[i] == 0)
					{
						newNode->binary[i] = 0;
						//cout << "0����" << endl;
					}
					else if (curp->binary[i] == nextp->binary[i] && curp->binary[i] == 2)
					{
						newNode->binary[i] = 2;
						//cout << "2����" << endl;
					}
					else
					{
						newNode->binary[i] = 2;
						//cout << "2��ȯ" << endl;
					}
				} // digit ��ȯ


				if (getP == NULL)
				{
					list[table_Number+1] = newNode;
					getP = list[table_Number + 1];
					//cout << "getP == NULL" << endl;
				}
				else if (getP != NULL && getP->next == NULL)
				{
					getP->next = newNode;
					//cout << "getP != NULL && getP->next == NULL" << endl;
				}
				else
				{
					newNode->next = getP->next;
					getP->next = newNode;
					//cout << "getP != NULL && getP->next != NULL" << endl;
				}
				// ���� �߰�
				curp->check = true;
				nextp->check = true;

				if (nextp->next == NULL)
				{
					curp = curp->next;
					nextp = curp->next;
				}
				else
				{
					nextp = nextp->next;
				}

			}
			else
			{
				count = 0;
				if (nextp->next == NULL)
				{
					curp = curp->next;
					nextp = curp->next;
				}
				else
				{
					nextp = nextp->next;
				}
			}
		}
		else // count != 1
		{
			count = 0; // ī��Ʈ�� �ʱ�ȭ
			if (nextp->next == NULL && curp == NULL)
			{
				curp = curp->next;
				nextp = curp;
			}
			else if (nextp->next == NULL)
			{
				curp = curp->next;
				nextp = curp->next;
			}
			else
			{
				nextp = nextp->next;
			}
		}
	} // while�� ��

}


int List::printData(int tableNumber)
{

	Node *temp = list[tableNumber];
	int count = 0;
	int binarySize = _msize(temp->binary) / sizeof(temp->binary[0]);
	while (temp != NULL)
	{
		cout << tableNumber << endl;
		for (Node *now = temp; temp != 0; temp = temp->next)
		{
			if (temp->check == false) count++;
			cout << temp->digit << ' ';
			for (int i = 0; i < binarySize; i++)
			{
				cout << temp->binary[i] << ' ';
			}
			cout << temp->ones << ' ' << temp->check <<endl;
		}
		cout << endl;
		temp = list[++tableNumber];
	}

	return count;
}

bool List::checkList(int tableNumber)
{
	Node *temp = list[tableNumber];

	for (Node *now = temp; temp != 0; temp = temp->next)
	{
		if (temp->check == true)
			return false;
	}

	return true;  // ���� üũ�� false �϶�����
}

void getBinary(Node *data)
{
	int binary = data->digit;
	int yidx = _msize(data->binary) / sizeof(data->binary[0])-1;
	//cout << yidx << endl;
	while (binary != 0) {
		if (binary % 2 == 1)
		{
			data->binary[yidx] = 1;
			binary /= 2;
			yidx--;
			data->ones++;
		}
		else
		{
			binary /= 2;
			yidx--;
		}
	}


	return;
}

void Result::deleteOverlap(int count,int input_var)
{
	int overlap = 0;
	for (int i = 0; i < count-1; i++)
	{
		overlap = 0;
		for (int j = i + 1; j < count; j++)
		{
			for (int k = 0; k < input_var; k++)
			{
				if (result[i]->binary[k] == result[j]->binary[k])
					overlap++;
			}
			if (overlap == input_var)
			{
				for (int k = 0; k < input_var; k++)
				{
					result[j]->binary[k] = -1;
				}
				overlap = 0;
			}
			else
			{
				overlap = 0;
			}
		}
	}
}

void Result::getEpi(int *mintermList,int epiNum, int input_var,int numOfMinterm)
{
	int mintermIdx;
	for (int k = 0; k < numOfMinterm; k++)
	{
		mintermIdx = mintermList[k];

		for (int i = 0; i < epiNum - 1; i++)
		{
			for (int j = i+1; j < epiNum; j++)
			{
				if (result[i]->minterms[mintermIdx] == result[j]->minterms[mintermIdx])
				{
					cout << i <<' '<< j << endl;
					result[i]->digit = 100; // nepi
					result[j]->digit = 100; // nepi
				}
			}

		}
	}
}
