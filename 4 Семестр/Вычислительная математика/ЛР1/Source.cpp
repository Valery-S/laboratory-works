#include<iostream>
#include<iomanip>
#include <ctime> 
using namespace std;
double const E = 0.001;

/*������� ������ ������� ��� ���������� �����
��������� �������:
	1)*alpha,*beta  - ��������� �� ����������, ���������� ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a*x^3+b*x^2+c*x+d
������� ������:
	1)����������� �������� �������� -100 � -99 (���������� ��������� � ������ ������ ������)
	2)������� �������� ������� � ������ alpha � beta
	3)���� ��� ��������� �������� ������� ���� ������������ �������������,
		�� ������� ������ �������� � ������� �����������,
		����� ����������� �������� ���������� alpha � beta �� 1
	4)������ 2)-3) ����������� ���� �� ������� ������ �������� ��� �������
		�� ����� �� ��������� ���������� � ������ ������ ������ (99 � 100)
*/
void find_section(double *alpha, double *beta, double a, double b, double c, double d) {
	double f_a,f_b;

	*alpha = -100;
	*beta = -99;

	for (*alpha; *alpha < 100;  (*alpha)++) {
		f_a = a * (*alpha) * (*alpha) * (*alpha) + b * (*alpha) * (*alpha) + c * (*alpha) + d;
		f_b = a * (*beta) * (*beta) * (*beta) + b * (*beta) * (*beta) + c * (*beta) + d;
		if (f_a * f_b < 0) { break; }
		(*beta)++;
	}

}

/*����� �������
��������� �������:
	1)alpha,beta  - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a*x^3+b*x^2+c*x+d
������� ������:
	1)��������� �������� ������� [alpha,beta]
	2)����������� �������� �������� � �������� ������� � �� ��� ������
	3)���� ���� �������� �������� � �������� ������� ��������� �� ������
		�������� �� ����� �� ������, �� �������� ����� ����� ���������� ��
		�������� �������� �������
	4)������ 1)-3) ����������� ���� ������ �������� �������� � ��������
		������� ������ ����������� E
*/
double bisection(double alpha,double beta,double a,double b,double c,double d) {
	double x = 0;
	double f_a = 0,f_b=0,f_x=LONG_MAX;
	int n = 0;

	cout<<"\n\u001B[32m" << setw(5) << "n|" << setw(16) << "alpha_n|" << setw(16) << "beta_n|" << setw(16)
			  << "f(alpha_n)|" << setw(16) << "f(beta_n)|" << setw(20) << "|alpha_n-beta_n| |\n";
	cout << "---- --------------- --------------- --------------- --------------- -------------------\n";

	while (abs(f_x) > E) {
		x = (alpha + beta) / 2;
		f_x = a * x * x * x + b * x * x + c * x + d;
		f_a = a * alpha * alpha * alpha + b * alpha * alpha + c * alpha + d;
		f_b = a * beta * beta * beta + b * beta * beta + c * beta + d;

		cout << setw(4) << n<<"|" << setw(15) << setprecision(8) << alpha << "|" << setw(15) << setprecision(8) << beta << "|" << setw(15)
			<< setprecision(8) << f_a << "|" << setw(15) << setprecision(8) << f_b << "|" << setw(18) << setprecision(8) << abs(alpha - beta) << "|" << "\n";
		cout << "---- --------------- --------------- --------------- --------------- -------------------\n";
		n++;

		if (f_x * f_b > 0) { beta = x; }
		if (f_x * f_a > 0) { alpha = x; }

	}
	return x;
}

/*����� ����
��������� ������� :
	1)alpha, beta - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a * x ^ 3 + b * x ^ 2 + c * x + d
������� ������ :
	1)����������� �������� �������� �� ������ �������
	2)����������� ����� ����������� ����� � ���� �������
	3)����������� �������� �������� � ��������� �����
	4)���� ���� �������� �������� � ��������� ����� ��������� �� ������
		�������� �� ����� �� ������, �� �������� ������� ����� ����������
		�� �������� ��������� �����
	5)������ 1) - 4) ����������� ���� ������ �������� �������� � �������
		������ ����������� E
*/
double chords(double alpha, double beta, double a, double b, double c, double d) {
	double x = 0;
	double f_a = 0, f_b = 0, f_x = LONG_MAX;
	int n = 0;

	cout << "\n\u001B[32m" << setw(5) << "n|" << setw(16) << "Xn|" << setw(17) << "|f(Xn)| |\n";
	cout << "---- --------------- ---------------\n";

	while (abs(f_x) > E) {
		f_a = a * alpha * alpha * alpha + b * alpha * alpha + c * alpha + d;
		f_b = a * beta * beta * beta + b * beta * beta + c * beta + d;
		x = alpha - f_a * (beta - alpha) / (f_b - f_a);
		f_x = a * x * x * x + b * x * x + c * x + d;

		cout << setw(4) << n << "|" << setw(15) << x << "|" << setw(15) << f_x<<"|\n";
		cout << "---- --------------- ---------------\n";
		n++;

		if (f_a * f_x < 0) { beta = x; }
		if (f_b * f_x < 0) { alpha = x; }
	}
	return x;
}

/*����� �������
��������� ������� :
	1)alpha, beta - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a * x ^ 3 + b * x ^ 2 + c * x + d
������� ������ :
	1)����������� �������� ������������� �����������
	2)����������� �������� �������� � ��� ����������� � ����� beta
	3)����������� �������� ��������� �����
	4)����������� �������� �������� � ��� ����������� � ������� �����
	5)������ 3) - 4) ����������� ���� ������ �������� ���������� �
		������� ����� ������ ����������� E
*/
double Newtone(double alpha, double beta, double a, double b, double c, double d) {
	double x=0,x_prev=0;
	double f_d_a = 0, f_d_b = 0, f_d_c = 0;
	double f_x_prev = 0,f_d_x_prev =0;
	int n = 0;
	f_d_a = a * 3;
	f_d_b = b * 2;
	f_d_c = c * 1;
	x_prev = beta;

	cout << "\n\u001B[32m" << setw(5) << "n|" << setw(16) << "Xn|" << setw(17) << "|Xn-X(n-1)| |\n";
	cout << "---- --------------- ---------------\n";
	cout << setw(4) << n << "|" << setw(15) << x_prev << "|" << setw(17)<< "|\n";
	cout << "---- --------------- ---------------\n";

	f_x_prev = a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d;
	f_d_x_prev = f_d_a * x_prev * x_prev + f_d_b * x_prev + f_d_c;
	x = x_prev - f_x_prev / f_d_x_prev;

	while (abs(x - x_prev) > E) {
		double tmp = x;
		x_prev = tmp;
		f_x_prev = a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d;
		f_d_x_prev = f_d_a * x_prev * x_prev + f_d_b * x_prev + f_d_c;
		x = x_prev - f_x_prev / f_d_x_prev;

		n++;
		cout << setw(4) << n << "|" << setw(15) << x << "|" << setw(15)<<abs(x-x_prev) << "|\n";
		cout << "---- --------------- ---------------\n";
	}

	return x;
}

/*����� ������� ��������
��������� ������� :
	1)alpha, beta - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a * x ^ 3 + b * x ^ 2 + c * x + d
������� ������ :
	1)�������� ������������ ������ �����, ������������� ������� [alpha,beta]
	2)����������� �������� ��������� �����, �� ������� 
		g(x)=x-0.2*(a * x ^ 3 + b * x ^ 2 + c * x + d)
	3)����� 2) ����������� ���� ������ �������� ���������� � �������
		����� ������ ����������� E
*/
double iterations(double alpha, double beta, double a, double b, double c, double d) {
	double x,x_prev;
	int n = 0;

	srand(time(NULL));
	x_prev= (alpha + beta)/ rand();

	cout << "\n\u001B[32m" << setw(5) << "n|" << setw(16) << "Xn|" << setw(17) << "|Xn-X(n-1)| |\n";
	cout << "---- --------------- ---------------\n";
	cout << setw(4) << n << "|" << setw(15) << x_prev << "|" << setw(17) << "|\n";
	cout << "---- --------------- ---------------\n";
	
	while (true) {
		x = x_prev - 0.2 * (a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d);
		
		n++;
		cout << setw(4) << n << "|" << setw(15) << x << "|" << setw(15) << abs(x - x_prev) << "|\n";
		cout << "---- --------------- ---------------\n";
		
		if (abs(x - x_prev) < E) { break; }
		x_prev = x;
	}
	return x;
}

int main() {
	setlocale(LC_ALL, "RUS");
	double a = 0, b = 0, c = 0, d = 0;
	double alpha = -2, beta = 0;
	double x = 0;
	char metod;

	//������ �������� ������
	cout << "\u001B[33m������ ��������� ������������� ��� ���������� ������ �������� ������� �������.\n"
			 << "������� ��������� a, b, c, d �������� ���� a*x^3+b*x^2+c*x+d=0\n"
			 <<"\t\u001B[36m������� �  ";
	cin >> a;
	cout << "\t������� b  ";
	cin >> b;
	cout << "\t������� c  ";
	cin >> c;
	cout << "\t������� d  ";
	cin >> d;
	
	//���������� ������� ��� ������ ������
	find_section(&alpha, &beta, a, b, c, d);
	cout << "\n\u001B[33m������� [alpha,beta], �� ������� ������ ������ ������.\nalpha=" << alpha << " beta=" << beta << "\n";

	//����� ������ ���������� ������
	cout << "\n�������� ����� ������� ���������:\n"
			 << "\u001B[36m\t{1} - ����� ��������\n"
			 << "\t{2} - ����� ����\n"
			 << "\t{3} - ����� �������\n"
			 << "\t{4} - ����� ������� ��������\n\n";
	cin >> metod;

	//���������� ����� ��������� �������
	time_t start=clock();
	switch (metod){
	case '1':
		x=bisection(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\n�����, ����������� �� ���������� ����� = " << (double)(clock() - start) / CLOCKS_PER_SEC <<" ������\n";
		break;
	case '2':
		x = chords(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\n�����, ����������� �� ���������� ����� = " << (double)(clock() - start) / CLOCKS_PER_SEC << " ������\n";
		break;
	case '3':
		x = Newtone(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\n�����, ����������� �� ���������� ����� = " << (double)(clock() - start) / CLOCKS_PER_SEC << " ������\n";
		break;
	case '4':
		x = iterations(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\n�����, ����������� �� ���������� ����� = " << (double)(clock() - start) / CLOCKS_PER_SEC << " ������\n";
		break;
	}

	//����� ����������
	cout << "\n\u001B[33m������ �������� " << x<<"\n";
	return 0;
}