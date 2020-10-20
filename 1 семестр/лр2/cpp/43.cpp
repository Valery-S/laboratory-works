#include <iostream>
using namespace std;
int main()
{
	int a, b;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите  день и мес€ц  ";
	cin >> a >> b;
	cout << "сейчас  " << (b/3) + 1<< " квартал"<< " от его начало прошло "<< ((b-1)*30+a)-(b/3)*3*30<<" дней";
	return 0;
}