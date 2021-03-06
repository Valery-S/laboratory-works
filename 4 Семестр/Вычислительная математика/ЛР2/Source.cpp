#include <iostream>
#include <vector>
#include <iomanip>
double const E = 0.001;
using namespace std;

/*����� ������
��������� �������� � ���� a*x_1+b*x_2+c*x_3=d
��������� �������:
	1)a_f,b_f,c_f,d_f - ��������� ������� ���������
	2)a_s,b_s,c_s,d_s - ��������� ������� ���������
	3)a_t,b_t,c_t,d_t - ��������� �������� ���������
������� ������:
	1)��������� ������� b ���������� �������
	2)���������� ������� A ������������� ������� ����������� ����������
	3)����� ������������ ������������ 
	4)������������ ������ ������ � ������ � ������������ ������������� � ������� A
	5)������������ ������ ������ � ������ � ������������ ������������� � ������� b 
	6)������������ ������� ������� � ������� � ������������ ������������� � ������� A
	7)���������� ������� � ������������ ����
	8)�������� ��� ������ ������ ��� ������ ������ �������
*/
vector<double> Gauss(double a_f, double b_f, double c_f, double d_f, double a_s, double b_s, double c_s, double d_s, double a_t, double b_t, double c_t, double d_t) {
	vector<double>x(3);
	vector<double>b(3);
	vector<vector<double>>a(3);
	double a_max = 0;
	int i_max = 0, j_max=0;

	//��������� ������ ��� ������� �������������
	for (int i = 0; i < 3; i++) { a[i].resize(3); }


	//��������� ������� b ���������� �������
	b[0] = d_f;  b[1] = d_s;  b[2] = d_t;


	//���������� ������� A ������������� ������� ����������� ����������
	a[0][0] = a_f;  a[0][1] = b_f;  a[0][2] = c_f;
	a[1][0] = a_s;  a[1][1] = b_s;  a[1][2] = c_s;
	a[2][0] = a_t;  a[2][1] = b_t;  a[2][2] = c_t;


	//����� ������������� ������������ � ������� A
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (a[i][j] > a_max) { 
				a_max = a[i][j]; 
				i_max = i;
				j_max = j;
			}
		}
	}
	

	//������������ ������ ������ � ������ � ������������ ������������� � ������� a
	double tmp = 0;
	for (int j = 0; j < 3; j++){
		tmp = a[0][j];
		a[0][j] = a[i_max][j];
		a[i_max][j] = tmp;
	}


	//������������ ������ ������ � ������ � ������������ ������������� � ������� b
	tmp = b[0];
	b[0] = b[i_max];
	b[i_max] = tmp;


	//������������ ������� ������� � ������� � ������������ ������������� � ������� a
	for (int i = 0; i < 3; i++) {
		double tmp = 0;
		tmp = a[i][0];
		a[i][0] = a[i][j_max];
		a[i][j_max] = tmp;
	}

	//���������� ������� � ������������ ����
	tmp = a[0][0];
	a[0][0] = 1;
	a[0][1] = a[0][1] / tmp;
	a[0][2] = a[0][2] / tmp;
	b[0] = b[0] / tmp;

	tmp = a[1][0];
	a[1][0] = a[1][0] - a[0][0] * tmp;
	a[1][1] = a[1][1] - a[0][1] * tmp;
	a[1][2] = a[1][2] - a[0][2] * tmp;
	b[1] = b[1] - b[0] * tmp;

	
	tmp = a[2][0];
	a[2][0] = a[2][0] - a[0][0] * tmp;
	a[2][1] = a[2][1] - a[0][1] * tmp;
	a[2][2] = a[2][2] - a[0][2] * tmp;
	b[2] = b[2] - b[0] * tmp;

	tmp = a[1][1];
	a[0][0] = 1;
	a[1][1] = a[1][1] / tmp;
	a[1][2] = a[1][2] / tmp;
	b[1] = b[1] / tmp;
	
	tmp = a[2][1];
	a[2][0] = a[2][0] - a[1][0] * tmp;
	a[2][1] = a[2][1] - a[1][1] * tmp;
	a[2][2] = a[2][2] - a[1][2] * tmp;
	b[2] = b[2] - b[1] * tmp;


	//����� ������� �� �������
	cout<<"�������, ����������� � ������������ ����\n"<<"\n\u001B[32m"
			<< a[0][0] << " * x1 + (" << a[0][1] << ") * x2 + (" << a[0][2] << ") * x3 = " << b[0] << "\n"
			<< a[1][0] << " * x1 + " << a[1][1] << " * x2 + (" << a[1][2] << ") * x3 = " << b[1] << "\n"
			<< a[2][0] << " * x1 + " << a[2][1] << " * x2 + (" << a[2][2] << ") * x3 = " << b[2] << "\n";

			
	//�������� ��� ������ ������ ��� ������ ������ �������
	x[2] = b[2] / a[2][2];
	x[1] = (b[1] - a[1][2] * x[2]) / a[1][1];
	x[0] = (b[0] - a[0][1] * x[1] - a[0][2] * x[2]) / a[0][0];


	return x;
}

/*����� ������� ��������
��������� �������� � ���� a*x_1+b*x_2+c*x_3=d
��������� �������:
	1)a_f,b_f,c_f,d_f - ��������� ������� ���������
	2)a_s,b_s,c_s,d_s - ��������� ������� ���������
	3)a_t,b_t,c_t,d_t - ��������� �������� ���������
������� ������:
	1)����������� ��������� ������� ������� ��������� - ����
	2)�� ������� ��������� ���������� ������
		(�� �������-������, �� �������-������, �� ��������-������)
	3)��������� �����, ��������� �� ���������� ����, ������ ����� �����
		�� ��� ���, ���� �������� ������ �� ��������� ��������
*/
vector<double> iteration(double a_f, double b_f, double c_f, double d_f, double a_s, double b_s, double c_s, double d_s, double a_t, double b_t, double c_t, double d_t) {
	vector<double> x_prev(3);
	vector<double>x(3,DBL_MAX);

	int n = 0;
	cout << "\n\u001B[32m" << setw(5) << "n|" << setw(16)
			 << "X_1|" << setw(16) << "X_2|" << setw(17) << "X_3|\n"
			 << "---- --------------- --------------- ---------------\n"
			 <<setw(4)<<n<<"|"<<setw(15)<<0<<"|" << setw(15) << 0 << "|"
			 << setw(15) << 0 << "|\n"
			<< "---- --------------- --------------- ---------------\n";


	while (true){
		x[0] = (d_f - b_f * x_prev[1] - c_f * x_prev[2]) / a_f;
		x[1] = (d_s - a_s * x_prev[0] - c_s * x_prev[2]) / b_s;
		x[2] = (d_t - a_t * x_prev[0] - b_t * x_prev[1]) / c_t;

		n++;
		cout << setw(4) << n << "|" << setw(15)  << x[0] << "|"
			<< setw(15) << x[1] << "|" << setw(15) << x[2] << "|\n"
			<< "---- --------------- --------------- ---------------\n";

		double max_lim = 0;
		for (int i = 0; i < 3; i++){
			if (abs(x[i] - x_prev[i]) > max_lim) { max_lim = abs(x[i] - x_prev[i]); }
		}

		if (max_lim < E) {break;}
		else {
			x_prev[0] = x[0];
			x_prev[1] = x[1];
			x_prev[2] = x[2];
		}
	}
	return x;
}

/*����� �����-�������
��������� �������� � ���� a*x_1+b*x_2+c*x_3=d
��������� �������:
	1)a_f,b_f,c_f,d_f - ��������� ������� ���������
	2)a_s,b_s,c_s,d_s - ��������� ������� ���������
	3)a_t,b_t,c_t,d_t - ��������� �������� ���������
������� ������:
	1)����������� ��������� ������� ������� ��������� - ����
	2)�� ������� ��������� ���������� ������
		(�� �������-������, �� �������-������, �� ��������-������)
	3)��������� �����, ��������� �� ���������� � ������� ����, 
		������ ����� ����� �� ��� ���, ���� �������� ������ �� ��������� ��������
*/
vector<double> Gauss_Seidel(double a_f, double b_f, double c_f, double d_f, double a_s, double b_s, double c_s, double d_s, double a_t, double b_t, double c_t, double d_t) {
	vector<double> x_prev(3);
	vector<double>x(3, DBL_MAX);

	int n = 0;
	cout << "\n\u001B[32m" << setw(5) << "n|" << setw(16)
		<< "X_1|" << setw(16) << "X_2|" << setw(17) << "X_3|\n"
		<< "---- --------------- --------------- ---------------\n"
		<< setw(4) << n << "|" << setw(15) << 0 << "|" << setw(15) << 0 << "|"
		<< setw(15) << 0 << "|\n"
		<< "---- --------------- --------------- ---------------\n";

	while (true) {
		x[0] = (d_f - b_f * x_prev[1] - c_f * x_prev[2]) / a_f;
		x[1] = (d_s - a_s * x[0] - c_s * x_prev[2]) / b_s;
		x[2] = (d_t - a_t * x[0] - b_t * x[1]) / c_t;

		n++;
		cout << setw(4) << n << "|" << setw(15) << x[0] << "|"
			<< setw(15) << x[1] << "|" << setw(15) << x[2] << "|\n"
			<< "---- --------------- --------------- ---------------\n";

		double max_lim = 0;
		for (int i = 0; i < 3; i++) {
			if (abs(x[i] - x_prev[i]) > max_lim) { max_lim = abs(x[i] - x_prev[i]); }
		}

		if (max_lim < E) { break; }
		else {
			x_prev[0] = x[0];
			x_prev[1] = x[1];
			x_prev[2] = x[2];
		}
	}
	return x;
}

int main() {
	double a_f = 0, b_f =0, c_f = 0,d_f=0;
	double a_s = 0, b_s =0, c_s = 0, d_s = 0;
	double a_t = 0, b_t = 0, c_t = 0, d_t = 0;
	char metod=0;
	setlocale(LC_ALL, "Russian");

	//���� �������� ������
	cout <<"\u001B[33m������ ��������� �������������� ��� ������� ������� ��� �������� ���������.\n"
			 <<"��������� �������������� � ���� a*x_1+b*x_2+c*x_3=d.\n"
			 <<"������� ������������ ������� ���������\n"
				<<"\u001B[36m\ta = ";
	cin >> a_f;
	cout << "\tb = ";
	cin >> b_f;
	cout << "\tc = ";
	cin >> c_f;
	cout << "\td = ";
	cin >> d_f;
	cout<< "\u001B[33m\n������� ������������ ������� ���������\n"
			<< "\u001B[36m\ta = ";
	cin >> a_s;
	cout << "\tb = ";
	cin >> b_s;
	cout << "\tc = ";
	cin >> c_s;
	cout << "\td = ";
	cin >> d_s;
	cout << "\u001B[33m\n������� ������������ �������� ���������\n"
			 << "\u001B[36m\ta = ";
	cin >> a_t;
	cout << "\tb = ";
	cin >> b_t;
	cout << "\tc = ";
	cin >> c_t;
	cout << "\td = ";
	cin >> d_t;

	
	while (metod!='q') {
		cout << "\u001B[31m\n\n-------------------------------------------------------\n";
		//����� ������ ������� �������
		cout << "\u001B[33m\n�������� ����� ������� ���������:\n"
			<< "\u001B[36m\t{1} - ����� ������\n"
			<< "\t{2} - ����� ������� ��������\n"
			<< "\t{3} - ����� �����-�������\n"
			<< "\t{q} - ��� ������ �� ���������\n\t";
		cin >> metod;

		//������� ��������� �������
		vector<double>x(3);
		time_t start = clock();
		switch (metod) {
		case '1':
			x = Gauss(a_f, b_f, c_f, d_f, a_s, b_s, c_s, d_s, a_t, b_t, c_t, d_t);
			break;
		case '2':
			x = iteration(a_f, b_f, c_f, d_f, a_s, b_s, c_s, d_s, a_t, b_t, c_t, d_t);
			break;
		case '3':
			x = Gauss_Seidel(a_f, b_f, c_f, d_f, a_s, b_s, c_s, d_s, a_t, b_t, c_t, d_t);
			break;
		}

		if (metod != 'q') {
			//����� ���������� �������
			cout << "\u001B[36m\n�����, ����������� �� ���������� ������ = "
				<< (double)(clock() - start) / CLOCKS_PER_SEC
				<< " ������\n";

			for (int i = 0; i < 3; i++) {
				cout << i + 1 << " ������ = "<< x[i] << "\n";
			}
		}
	}
	return 0;
}