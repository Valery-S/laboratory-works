#include <iostream>
using namespace std;
int main()
{
	float  a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите 3 числа   ";
	cin >> a >> b >> c;
	
	if (c-b==b-a)
	{
		cout << "„исла €вл€ютс€ алгебраической последовательностью  ";
	}
	else {
		if (c / b == b / a)
		{
			cout << "„исла €вл€ютс€ геометрической последовательностью  ";
		}else{
			cout << "„исла не €вл€ютс€  последовательностью  ";
		}
	}

	return 0;
}