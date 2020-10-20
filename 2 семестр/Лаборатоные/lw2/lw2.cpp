#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::setw;
char logo[]=
"***************************************************************\n"
"                                  ______    ______            \n"
" \\        /       /\\     |        |        |     |   \\     / \n"
"  \\      /       /  \\    |        |        |_____|    \\   /  \n"
"   \\    /       /    \\   |        |_____   |  \\        \\ /   \n"
"    \\  /       /------\\  |        |        |   \\        /    \n"
"     \\/       /        \\ |_____   |_____   |    \\      /     \n"
"                                                              \n"
"**************************************************************\n";
struct flight {
	int Fnumber;
	string Fname;
	string Ftype;
	double cost;
	double length;
};
int main(int argc, char **argv){
	cout<<"\x1B[36m"<<logo<<endl;
	if(((argc==2)&&((!strcmp(argv[1],"-h"))||(!strcmp(argv[1],"--help"))))||(argc==1)){
		cout<<"Это программа для работы с файлом , который хранит данные о разных авиарейсах. C ней можно работать в двух режимах : запись и чтение."<<endl<<"Введите -с [N] [file_name] для запуска программы в режиме создания электронной таблицы записей, N – количество записей, file_name – имя текстового файла, в котором будет сохранен массив (таблица) записей."<<endl<<"Введите -r [N] [file_name] - для запуска программы в режиме чтения содержимого текстового файла file_name, на экран будут выведены не более N записей."<<endl;}
	if((argc==4) &&(!strcmp(argv[1],"-c"))&&(atoi(argv[2])!=0)){
		ofstream fp(argv[3]);
		if(fp.is_open()) {
			int N=atoi(argv[2]);
			flight s;
			for(int i=0;i<N;i++){
				cout<<"Рейс "<<i+1<<endl;
				cout<<"Введите номер рейса"<<endl;
				cin>>s.Fnumber;
				cout<<"Введите название рейса"<<endl;
				cin>>s.Fname;
				cout<<"Введите тип самолёта"<<endl;
				cin>>s.Ftype;
				cout<<"Введите стоимость билета"<<endl;
				cin>>s.cost;
				cout<<"Введите протяжённость рейса"<<endl;
				cin>>s.length;
			fp<<setw(20)<<s.Fnumber<<setw(20)<<s.Fname<<setw(20)<<s.Ftype<<setw(20)<<s.cost<<setw(20)<<s.length<<endl;
			}
			fp.close();
		}
	}
	if((argc==4) &&(!strcmp(argv[1],"-r"))&&(atoi(argv[2])!=0)){
		ifstream fp(argv[3]);
		if(fp.is_open()) {
			int N=atoi(argv[2]);
			flight s;
			cout<<setw(15)<<"number"<<setw(15)<<"name"<<setw(15)<<"type"<<setw(15)<<"cost"<<setw(15)<<"length"<<endl;
			for(int i=0;i<N;i++){
		fp>>s.Fnumber>>s.Fname>>s.Ftype>>s.cost>>s.length;
		cout<<setw(15)<<s.Fnumber<<setw(15)<<s.Fname<<setw(15)<<s.Ftype<<setw(15)<<s.cost<<setw(15)<<s.length<<endl;
			}
			fp.close();
		}
	}
	
	return 0;}




