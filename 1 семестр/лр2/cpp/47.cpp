#include <iostream>
using namespace std;
int main()
{
	int e, d, a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите длины кирпича   ";
	cin >> a >> b >> c;
	cout << "¬ведите  длины сечени€  ";
	cin >> d >> e;
	if ((a <= d && b <= e) || (a <= e && b <= d) || (a <= d && c <= e) || (a <= e && c <= d) || (b <= d && c <= e) || (b <= e && c <= d))
	{
		cout << " ирпич с длинами  " << a << " " << b << "  " << c << " можно переместить через отверстие сечением " << d << " " << e;
	}
	else {
		cout << " ирпич с длинами  " << a << " " << b << "  " << c << " нельз€ переместить через отверстие сечением " << d << " " << e;
	}

	return 0;
}