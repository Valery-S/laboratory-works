#include "Mystring.h"

char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 5. Task number 18. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
using namespace std;
int main()
{
	ifstream in("data.txt");
	ofstream out ("result.txt");
	char string[60];
	in.getline(string, 60);
	char* newstring = new char[len(string) - (position_closing(string) - position_opening(string))];
	if (newstring==0)
	{
		return -1;
	}
	out << logo;
	newstring = without_brackets(string,newstring);
	for (int i = 0; i < len(newstring); i++)
	{
		out << newstring[i];
	}
	in.close();
	out.close();
	delete[]newstring;
	return 0;
}