#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите  день и мес€ц  и год ";
	cin >> a >> b >> c;
	cout << "C 1 €нвар€ 1970 года прошло " << ((c - 1) * 365 + (b - 1) * 30 + a) - (1969 * 365) << " дней";
	return 0;
}