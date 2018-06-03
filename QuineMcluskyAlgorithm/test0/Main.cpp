#include "TABULAR.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
	ifstream inStream;
	int input_var, numOfMinterm; // ��ǲ �� , minterm ����
	int mintermList[64];		// minterm list
	int tableNumber = 0;

	inStream.open("input.txt");
	if (inStream.fail())
	{
		cout << "File open failed" << endl;
		exit(1);
	}
	inStream >> input_var >> numOfMinterm;
	for (int i = 0; i < numOfMinterm; i++)
		inStream >> mintermList[i];
	//  �Է� ����

	List table;

	for(int i =0;i<numOfMinterm;i++)
		table.AddData(tableNumber, mintermList[i],input_var);
	// ù ���̺� ���� �Ϸ�

	for (int c = 0; c < input_var-1; c++)
	{

		table.CompareData(c, input_var, numOfMinterm);
		cout << table.checkList(c) << endl;
		if (table.checkList(c)) break;

		//table.deleteOverlap(tableNumber++, input_var);
	}

	int count = table.printData(0);
	cout << "non check count : " << count << endl;

	Result rs;
	Result Epi;

	int rsIdx = 0;

	for(int t=0;t<input_var;t++)
	{
		Node *temp = table.list[t];

		while(temp != NULL)
		{
			if (temp->check == false)
			{
				rs.result[rsIdx++] = temp;
			}
			temp = temp->next;
		}
	}
	cout << "result" << endl;
	rs.deleteOverlap(count,input_var);
	for (int t = 0; t < count; t++)
	{
		for (int i = 0; i < input_var; i++)
		{
			cout << rs.result[t]->binary[i] << ' ';
		}
		cout << endl;
	}

	int startIdx = 0;
	int epiNum = 0;
	for (int i = 0; i < count; i++)
	{
		if (rs.result[i]->binary[0] != -1)
		{
			Epi.result[startIdx++] = rs.result[i];
			epiNum++;
		}
	}
	cout <<"result" <<  endl;
	Epi.getEpi(mintermList, epiNum,input_var, numOfMinterm);


	for (int t = 0; t < epiNum; t++)
	{
		cout << Epi.result[t]->digit << ' ';
		for (int i = 0; i < input_var; i++)
		{
			cout << Epi.result[t]->binary[i] << ' ';
		}
		cout << endl;
	}


	return 0;
}
