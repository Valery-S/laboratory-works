#include <iostream>
#include <vector>
char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 3. Task number 10. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
using namespace std;
int proverkaN() {
	int n = 0;
	char b = 1;
	while (cin.good()) {
		if (n == 0) {
			cout << "write array size ";
			while (b != 0)
			{
				b = cin.get();
				if (b >= '0' && b <= '9')
				{
					n = n * 10 + (b - 48);

				}
				else {
					if (b != '\n')
					{
						cout << "error, write again " << endl;
						n = 0;
					}
					else
					{
						break;
					}
				}

			}
		}
		else {
			break;
		}
	}
	return n;
}
int main()
{
	cout << logo;
	int n = proverkaN();
	float p = 1.0;
	vector<float> a(n);

	for (int i = 0; i < n; i++) {
		cout << "write  array element ";
		cin >> a[i];
		if (a[i] > 2) {
			p = p * a[i];
		}
	}

	cout << "proizvedenie >2 = " << p << endl;
	return 0;
}