// letter finder from strings.cpp : Defines the entry point for the console application.
#include <iostream>
#include <string.h>
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
char strings[8191];
unsigned long long wordcount = 0;
double elapsedp1;
using namespace std;
clock_t beginl, endr;
void Prestart()
{
	// make every element 0

	for (int k = 0; k < 26; k++)
	{
		letterno[k] = 0;
		percentage[k] = 0;
	}
}
void letterfinder(char strings[], int param = 1)
{
	if (param == 0)
	{
		wordcount++;
		if (wordcount % 25000000 == 0)
			cout << "Word no " << wordcount << " reached!" << '\n';
	}
	for (unsigned long long i = 0; i < strlen(strings); i++)
	{
		// check whether we've got a letter among the strings
		if ((isupper(strings[i]) || islower(strings[i])) == 1)
		{
			strings[i] = toupper(strings[i]);// for us not to worry about case
			//  increment value corresponding to the letter
			letterno[strings[i] - 65]++;
			totalletter++;
		}
		// did we get a number?
		else if (((strings[i]) >= '0' && (strings[i]) <= '9') == 1)
			totalnum++;
		if ((strings[i] != ' ') == 1)
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
	cout << "The total number of characters including spaces is " << totalchar << '\n';
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
		strcpy(filename, argv[1]);
		try {
			ifstream File;
			system("cls");
			cout << "Loading... " << '\n';
			File.open(filename);
			cout << "Accessing file ..." << '\n';
			beginl = clock();
			if (File.fail())
			{
				throw "File does not exist";
			}
			while (!File.eof())
			{
				File.getline(strings, 8191, ' ');
				letterfinder(strings, 0);
			}
		}
		catch (char* message)
		{
			cerr << message;
			getchar();
			exit(1);
		}
		endr = clock();
		results();
	}

	else
	{
		cout << "Enter 0 to copy string, enter 1 to open txt file in current directory" << '\n';
	base:cin >> opt1;
	}
	if (opt1 == 1)
	{
		try {
			cout << "Enter the filepath of file, appending file extension to it" << '\n';
			cin.ignore();
			scanf("%s", filename);
			ifstream File;
			system("cls");
			cout << "Loading... " << '\n';
			File.open(filename);
			cout << "Accessing file ..." << '\n';
			beginl = clock();
			if (File.fail())
			{
				throw "File does not exist";
			}
			while (!File.eof())
			{
				File.getline(strings, 8191, ' ');
				letterfinder(strings, 0);
			}
		}
		catch (char* message)
		{
			cerr << message;
			getchar();
			exit(1);
		}
		endr = clock();
		results();
	}
	else if (opt1 == 0)
	{
		cout << "Enter the strings" << '\n';
		cin.ignore();
		scanf("%s", strings);
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