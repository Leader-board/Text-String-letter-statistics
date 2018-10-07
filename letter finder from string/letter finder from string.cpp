// letter finder from strings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <WinUser.h>
#include <ctime>
#include <fstream>
float letterno[26], percentage[26];
int param;
unsigned long long totalletter = 0, totalchar = 0, totalnum = 0, totalnospace = 0;
char display = 'A';
char strings[8191];
unsigned long long wordcount = 0;
double elapsedp1;
using namespace std;
clock_t beginl , endr;
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void GetScreenResolution()
{
	RECT DesktopRect;
	// Gets the Desktop window
	HWND hDesktop = ::GetDesktopWindow();
	// Gets the Desktop window rect or screen resolution in pixels
	::GetWindowRect(hDesktop, &DesktopRect);
}
void Prestart()
{
	// make every element 0

	for (int k = 0; k < 26; k++)
	{
		letterno[k] = 0;
		percentage[k] = 0;
	}
}
void letterfinder(char strings[] , int param=1)
{
	if (param == 0)
	{
		wordcount++;
		if (wordcount % 25000000 == 0)
			cout << "Word no " << wordcount << " reached!" << '\n';
	}
	for (long i = 0; i < strlen(strings); i++)
	{
		// check whether we've got a letter among the strings
		if ((isupper(strings[i]) || islower(strings[i])) == 1)
		{
			strings[i] = toupper(strings[i]);// for us not to worry about case
											 // determine the letter used
			for (char j = 'A'; j <= 'Z'; j++)
			{
				if (strings[i] == j)
				{
					letterno[j - 65]++;
					totalletter++;
				}
			}
		}
		// did we get a number?
		else if (((strings[i]) >= '0' && (strings[i]) < '9') == 1)
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
		percentage[l] = (letterno[l] / totalletter) * 100;
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
int main()
{
	char filename[5550];
	Prestart();
	gotoxy(25, 15);
	cout << "Enter 0 to copy string , enter 1 to open txt file in current directory" << '\n';
	int opt1;
	base:cin >> opt1;
	if (opt1 == 1)
	{
		cout << "Enter the filepath of file , appending file extension to it" << '\n';
		cin.ignore();
		gets_s(filename);
		ifstream File;
		system("cls");
		cout << "Loading... " << '\n';
		File.open(filename);
		cout << "Accessing file ..." << '\n';
		beginl = clock();
		while (!File.eof())
		{
			File.getline(strings, 8191, ' ');
			letterfinder(strings , 0);
		}
		endr = clock();
		results();
	}
	else if (opt1==0)
	{
		cout << "Enter the strings" << '\n';
		cin.ignore();
		gets_s(strings);
		cout << "Press a key to continue" << '\n';
		_getch();
		system("cls");
		letterfinder(strings);
		results();
	}
	else
	{
		cout << "Invalid number. Select 1 or 0" << '\n';
		goto base;
	}
	_getch();
}
