#ifndef _Mystring_H_
#define _Mystring_H_
#include <fstream>
using namespace std;

int len( char* s) {
	int i = 0;
	while (s[i] != '\0') i++;
	return i;
}
int position_opening(char*str) {
	int opening = 0;
	for (int i = 0; i < len(str); i++)
	{
		if (str[i] == '(')
		{
			opening = i;
			break;//т.к. нужно найти первую открывающуюся скобку
		}
	}
	return opening;
}
int position_closing(char* str) {
	int  closing = 0;
	for (int i = 0; i < len(str); i++)
	{
		if (str[i] == ')')
		{
			closing = i;//т.к. нужно найти последнюю закрывающуюся скобку
		}
	}
	return closing;
}
char* without_brackets(char* str,char*newstr) {
	int closing = position_closing(str),opening= position_opening(str);
	
	for (int i = 0; i < opening; i++)
	{
		newstr[i] = str[i];
	}
	for (int i = closing; i < len(str); i++)
	{
		newstr[opening + i - closing] = str[i+1];
	}
	return newstr;
}

#endif
