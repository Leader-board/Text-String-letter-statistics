/*
Letter finder string - Windows version
Has some modifications from the Linux side because getdelim() does not exist on Windows, and hence a getdelim() function was taken from https://github.com/ivanrad/getline.
Also, the 'secure' versions (scanf_s not scanf for example) were used to satisfy the compiler.
It is not perfect yet, as there are many warnings reported by Visual Studio, but it works for now.
*/
#include "stdafx.h"
#include "getline.h"
#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
unsigned long long letterno[26];
float percentage[26];
int param;
unsigned long long totalletter = 0, totalchar = 0, totalnum = 0, totalnospace = 0;
char display = 'A';
char* strings;
unsigned long long wordcount = 0;
double elapsedp1;
using namespace std;
clock_t beginl, endr;
int count = 0;
size_t sizer = 5000;
char* next_token;
void Prestart()
{
	// make every element 0

	for (int k = 0; k < 26; k++)
	{
		letterno[k] = 0;
		percentage[k] = 0;
	}
}
void letterfinder(char* str, int param = 1)
{
	if (param == 0 && !(strlen(str) == 1 && str[0] == ' ')) // was put to guard against " " cases. Doubt this will be a problem anymore though.
	{
		wordcount++;
		if (wordcount % 25000000 == 0)
			cout << "Word no " << wordcount << " reached!" << '\n';
	}
	for (unsigned long long i = 0; i < strlen(str); i++)
	{
		// check whether we've got a letter among the strings
		if ((isupper(str[i]) || islower(str[i])) == 1)
		{
			str[i] = toupper(str[i]);// for us not to worry about case
			//  increment value corresponding to the letter
			letterno[str[i] - 65]++;
			totalletter++;
		}
		// did we get a number?
		else if (((str[i]) >= '0' && (str[i]) <= '9') == 1)
			totalnum++;
		if ((str[i] != ' ') == 1)
			totalnospace++; // not a space
		totalchar++; // in any case
	}
}
void results()
{
	double elapsed_secs = double(endr - beginl) / CLOCKS_PER_SEC;
	// display the output
	cout << "The number of times each letter appears and the percentage of occurrence is:-" << '\n';
	cout << "Letter" << '\t' << "No of times" << '\t' << "Percentage" << '\n' << '\n';
	for (int l = 0; l < 26; l++)
	{
		percentage[l] = ((float)letterno[l] / (float)totalletter) * 100;
		cout << display << '\t' << letterno[l] << "  times" << '\t' << percentage[l] << '\n';
		display++;
	}
	cout << "The total number of letters counted is " << totalletter << '\n';
	cout << "The total number of numbers counted is " << totalnum << '\n';
	cout << "The total number of characters excluding spaces is " << totalnospace << '\n';
	cout << "The total number of characters including spaces is " << totalchar << '\n'; // will be same due to bug
	if (param == 0)
		cout << "The total number of words counted is " << wordcount << '\n';
	cout << "Time taken for Part 2 operation is " << elapsed_secs << " seconds" << '\n';
	cout << "Number of characters searched per second is " << floor(totalchar / elapsed_secs) << '\n';
}
int main(int argc, char* argv[])
{
	char filename[5550];
	int opt1 = -1;
	Prestart();
	if (argc == 2)
	{
		strcpy_s(filename, argv[1]);
		FILE* F;
		try {
			fopen_s(&F,filename, "r");
			system("cls");
			cout << "Loading... " << '\n';
			if (F)
			{
				cout << "Accessing file ..." << '\n';
				beginl = clock();
				/*
				Here, we first take each line, and then pass each word to the letter finding function.
				Not the best method, as strtok does not handle two instances of the same delimiter, causing extra spaces to be discarded.
				But while simply using getdelim with delimiter ' ' should be enough, if that file has no spaces, then funny things (like buffer overflow) can happen.
				Theortically it might still work, but this method is significantly faster.
				*/
				while (getdelim(&strings, &sizer, '\n', F) != -1)
				{
					char* str = strtok_s(strings, " ",&next_token);
					while (str != NULL)
					{
						letterfinder(str, 0);
						//	printf("%s\n", str);
						str = strtok_s(NULL, " ",&next_token);
					}
				}
			}
			else
			{
				throw "File opening error";
			}
		}
		catch (char* message)
		{
			cerr << message;
			getchar();
			exit(1);
		}
		endr = clock();
		fclose(F);
		results();
	}

	else
	{
		cout << "Enter 0 to copy string, enter 1 to open txt file in current directory" << '\n';
	base:cin >> opt1;
	}
	if (opt1 == 1)
	{
		FILE* F;
		try {
			cout << "Enter the filepath of file, appending file extension to it" << '\n';
			cin.ignore();
			scanf_s("%s", filename,5550);
			fopen_s(&F,filename, "r");
			system("cls");
			cout << "Loading... " << '\n';
			if (F)
			{
				cout << "Accessing file ..." << '\n';
				beginl = clock();
				while (getdelim(&strings, &sizer, ' ', F) != -1)
				{
					letterfinder(strings, 0);
				}
				free(strings);
			}
			else
			{
				throw "File opening error";
			}
		}
		catch (char* message)
		{
			cerr << message;
			getchar();
			exit(1);
		}
		endr = clock();
		fclose(F);
		results();
	}
	else if (opt1 == 0)
	{

		cout << "Enter the strings" << '\n';
		cin.ignore();
		scanf_s("%s", strings,8191);
		cout << "Press a key to continue" << '\n';
		getchar();
		system("cls");
		letterfinder(strings);
		results();
	}
	else if (opt1 == -1)
	{
		exit(0);
	}
	else
	{
		cout << "Invalid number. Select 1 or 0" << '\n';
		goto base;
	}
	getchar();
}
