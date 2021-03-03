#include<iostream>
#include<iomanip>
#include <ctime> 
using namespace std;
double const E = 0.001;

/*Функция поиска отрезка для нахождения корня
Параметры функции:
	1)*alpha,*beta  - указатели на переменные, содержащие границы отрезка, на котором ищется корень
	2)a, b, c, d - параметры полинома a*x^3+b*x^2+c*x+d
Принцип работы:
	1)Присваемаем границам значения -100 и -99 (минимально возможные в рамках данной задачи)
	2)Находим значения функции в точках alpha и beta
	3)Если при умножении значений функции знак произведения отрицательный,
		то найдены нужные значения и функция завершается,
		иначе увеличиваем значение переменных alpha и beta на 1
	4)Пункты 2)-3) выполняются пока не найдены нужные значения или граница
		не дошла до предельно допустимой в рамках данной задачи (99 и 100)
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

/*Метод биекции
Параметры функции:
	1)alpha,beta  - границы отрезка, на котором ищется корень
	2)a, b, c, d - параметры полинома a*x^3+b*x^2+c*x+d
Принцип работы:
	1)Находится середина отрезка [alpha,beta]
	2)Вычисляется значение полинома в середине отрезка и на его концах
	3)Если знак значения полинома в середине отрезка совпадает со знаком
		значения на одном из концов, то значение этого конца заменяется на
		значение середины отрезка
	4)Пункты 1)-3) выполняются пока модуль значения полинома в середине
		отрезка больше погрешности E
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

/*Метод хорд
Параметры функции :
	1)alpha, beta - границы отрезка, на котором ищется корень
	2)a, b, c, d - параметры полинома a * x ^ 3 + b * x ^ 2 + c * x + d
Принцип работы :
	1)Вычисляется значение полинома на концах отрезка
	2)Вычисляется точка пересечения хорды с осью абсцисс
	3)Вычилсяется значение полинома в найденной точке
	4)Если знак значения полинома в найденной точке совпадает со знаком
		значения на одном из концов, то значение другого конца заменяется
		на значение найденной точки
	5)Пункты 1) - 4) выполняются пока модуль значения полинома в текущей
		больше погрешности E
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

/*Метод Ньютона
Параметры функции :
	1)alpha, beta - границы отрезка, на котором ищется корень
	2)a, b, c, d - параметры полинома a * x ^ 3 + b * x ^ 2 + c * x + d
Принцип работы :
	1)Вычисляются значения коэффициентов производной
	2)Вычисляются значения полинома и его производной в точке beta
	3)Вычисляется значение следующей точки
	4)Вычисляются значения полинома и его производной в текущей точке
	5)Пункты 3) - 4) выполняются пока модуль разности предыдущей и
		текущей точек больше погрешности E
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

/*Метод простой итерации
Параметры функции :
	1)alpha, beta - границы отрезка, на котором ищется корень
	2)a, b, c, d - параметры полинома a * x ^ 3 + b * x ^ 2 + c * x + d
Принцип работы :
	1)Случайно генерируется первая точка, принадлежащую отрезку [alpha,beta]
	2)Вычисляется значение следующей точки, по формуле 
		g(x)=x-0.2*(a * x ^ 3 + b * x ^ 2 + c * x + d)
	3)Пункт 2) выполняется пока модуль разности предыдущей и текущей
		точек больше погрешности E
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

	//Запрос исходных данных
	cout << "\u001B[33mДанная программа предназначена для нахождения корней полинома третьей степени.\n"
			 << "Введите параметры a, b, c, d полинома вида a*x^3+b*x^2+c*x+d=0\n"
			 <<"\t\u001B[36mВведите а  ";
	cin >> a;
	cout << "\tВведите b  ";
	cin >> b;
	cout << "\tВведите c  ";
	cin >> c;
	cout << "\tВведите d  ";
	cin >> d;
	
	//Нахождение отрезка для поиска корней
	find_section(&alpha, &beta, a, b, c, d);
	cout << "\n\u001B[33mОтрезок [alpha,beta], на котором ищется корень найден.\nalpha=" << alpha << " beta=" << beta << "\n";

	//Выбор метода нахождения корней
	cout << "\nВыберите метод решения уравнения:\n"
			 << "\u001B[36m\t{1} - Метод бисекции\n"
			 << "\t{2} - Метод хорд\n"
			 << "\t{3} - Метод Ньютона\n"
			 << "\t{4} - Метод простой итерации\n\n";
	cin >> metod;

	//Нахождение корня указанным методом
	time_t start=clock();
	switch (metod){
	case '1':
		x=bisection(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\nВремя, затраченное на нахождение корня = " << (double)(clock() - start) / CLOCKS_PER_SEC <<" секунд\n";
		break;
	case '2':
		x = chords(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\nВремя, затраченное на нахождение корня = " << (double)(clock() - start) / CLOCKS_PER_SEC << " секунд\n";
		break;
	case '3':
		x = Newtone(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\nВремя, затраченное на нахождение корня = " << (double)(clock() - start) / CLOCKS_PER_SEC << " секунд\n";
		break;
	case '4':
		x = iterations(alpha, beta, a, b, c, d);
		cout << "\u001B[33m\nВремя, затраченное на нахождение корня = " << (double)(clock() - start) / CLOCKS_PER_SEC << " секунд\n";
		break;
	}

	//Вывод результата
	cout << "\n\u001B[33mКорень полинома " << x<<"\n";
	return 0;
}