void find_section(double *alpha, double *beta, double a, double b, double c, double d) {
	double f_a,f_b;

	alpha = -100;
	beta = -99;

	for (alpha; alpha < 100;  alpha++) {
		f_a = a * alpha * alpha * alpha + b * alpha * alpha + c * alpha + d;
		f_b = a * beta * beta * beta + b * beta * beta + c * beta + d;
		if ((f_a*f_b) < 0) { break; }
		beta ++;
	}

}

double bisection(double alpha,double beta,double a,double b,double c,double d) {
	double x = 0;
	double f_a = 0,f_b=0,f_x=LONG_MAX;
	int n = 0;

	

	while (abs(f_x) > E) {
		x = (alpha + beta) / 2;
		f_x = a * x * x * x + b * x * x + c * x + d;
		f_a = a * alpha * alpha * alpha + b * alpha * alpha + c * alpha + d;
		f_b = a * beta * beta * beta + b * beta * beta + c * beta + d;

		

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
		�������� �� ����� �� ������, �� �������� ������� ����� ���������� �� �������� ��������� �����
	5)������ 1) - 4) ����������� ���� ������ �������� �������� � ������� ������ ����������� E
*/
double chords(double alpha, double beta, double a, double b, double c, double d) {
	double x = 0;
	double f_a = 0, f_b = 0, f_x = LONG_MAX;
	

	

	while (abs(f_x) > E) {
		f_a = a * alpha * alpha * alpha + b * alpha * alpha + c * alpha + d;
		f_b = a * beta * beta * beta + b * beta * beta + c * beta + d;
		x = alpha - f_a * (beta - alpha) / (f_b - f_a);
		f_x = a * x * x * x + b * x * x + c * x + d;

		

		if (f_a * f_x < 0) { beta = x; }
		if (f_b * f_x < 0) { alpha = x; }
	}
	return x;
}

/*����� �������
�������� ������� :
	1)alpha, beta - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a * x ^ 3 + b * x ^ 2 + c * x + d
������� ������ :
	1)����������� �������� ������������� �����������
	2)����������� �������� �������� � ��� ����������� � ����� beta
	3)����������� �������� ��������� �����
	4)����������� �������� �������� � ��� ����������� � ������� �����
	5)������ 3) - 4) ����������� ���� ������ �������� ���������� � ������� ����� ������ ����������� E
*/
double Newtone(double alpha, double beta, double a, double b, double c, double d) {
	double x=0,x_prev=0;
	double f_d_a = 0, f_d_b = 0, f_d_c = 0;
	double f_x_prev = 0,f_d_x_prev =0;
	
	f_d_a = a * 3;
	f_d_b = b * 2;
	f_d_c = c * 1;
	x_prev = beta;

	

	f_x_prev = a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d;
	f_d_x_prev = f_d_a * x_prev * x_prev + f_d_b * x_prev + f_d_c;
	x = x_prev - f_x_prev / f_d_x_prev;

	while (abs(x - x_prev) > E) {
		double tmp = x;
		x_prev = tmp;
		f_x_prev = a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d;
		f_d_x_prev = f_d_a * x_prev * x_prev + f_d_b * x_prev + f_d_c;
		x = x_prev - f_x_prev / f_d_x_prev;

		
	}

	return x;
}

/*����� ������� ��������
��������� ������� :
	1)alpha, beta - ������� �������, �� ������� ������ ������
	2)a, b, c, d - ��������� �������� a * x ^ 3 + b * x ^ 2 + c * x + d
������� ������ :
	1)�������� ������������ ������ �����, ������������� ������� [alpha,beta]
	2)����������� �������� ��������� �����, �� ������� g(x)=x-0.2*(a * x ^ 3 + b * x ^ 2 + c * x + d)
	3)����� 2) ����������� ���� ������ �������� ���������� � ������� ����� ������ ����������� E
*/
double iterations(double alpha, double beta, double a, double b, double c, double d) {
	double x,x_prev;
	

	srand(time(NULL));
	x_prev= (alpha + beta)/ rand();

	
	
	while (true) {
		x = x_prev - 0.2 * (a * x_prev * x_prev * x_prev + b * x_prev * x_prev + c * x_prev + d);
		
		

		if (abs(x - x_prev) < E) { break; }
		x_prev = x;
	}
	return x;
}