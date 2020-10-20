#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::ios;
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
class flight {
private:
	int Fnumber;
	string Fname;
	string Ftype;
	double cost;
	double length;
public:
	void set (int num,string name,string ty,double co,double len ){
		Fnumber=num;
		Fname=name;
		Ftype=ty;
		cost=co;
		length=len;}
	int get_number(){return Fnumber;}
	string get_name(){return Fname;}
	string get_type(){return Ftype;}
	double get_cost(){return cost;}
	double get_length(){return length;}
};
int main(int argc, char **argv){
	cout<<"\x1B[36m"<<logo<<endl;
	if(((argc==2)&&((!strcmp(argv[1],"-h"))||(!strcmp(argv[1],"--help"))))||(argc==1)){
		cout<<"\x1B[32m"<<"Аргументы:"<<endl;
			cout<<"-h or --help для вызова подсказки"<<"\n";
			cout<<"-c <N> [file_name] для создания таблицы и записи её в файл (N строк)."<<endl;
			cout<<"-r <N> [file_name] для вывода таблицы из файла на экран (не более N строк)."<<endl;}
	if((argc==4) &&(!strcmp(argv[1],"-c"))&&(atoi(argv[2])!=0)){
		ofstream fp(argv[3],ios::binary);
		if(fp.is_open()) {
			int N=atoi(argv[2]);
			if(N<=0){cout<<"Eror, n<=0"<<endl;}
			flight* s=new flight [N];
			int number;
			string name;
			string type;
			double co;
			double len;
			for(int i=0;i<N;i++){
				cout<<"Рейс "<<i+1<<endl;
				cout<<"Введите номер рейса"<<endl;
				cin>>number;
				cout<<"Введите название рейса"<<endl;
				cin>>name;
				cout<<"Введите тип самолёта"<<endl;
				cin>>type;
				cout<<"Введите стоимость билета"<<endl;
				cin>>co;
				cout<<"Введите протяжённость рейса"<<endl;
				cin>>len;
				s[i].set(number,name,type,co,len);
fp<<setw(20)<<s[i].get_number()<<setw(20)<<s[i].get_name()<<setw(20)<<s[i].get_type()<<setw(20)<<s[i].get_cost()<<setw(20)<<s[i].get_length()<<endl;
			}
			fp.close();
			delete []s;
		}
	}
	if((argc==4) &&(!strcmp(argv[1],"-r"))&&(atoi(argv[2])!=0)){
		ifstream fp(argv[3],ios::binary);
		if(fp.is_open()) {
			int N=atoi(argv[2]);
			if(N<=0){cout<<"Eror, n<=0"<<endl;}
			flight * s=new flight [N];
			int number;
			string name;
			string type;
			double co;
			double len;
			cout<<setw(15)<<"number"<<setw(15)<<"name"<<setw(15)<<"type"<<setw(15)<<"cost"<<setw(15)<<"length"<<endl;
			for(int i=0;i<N;i++){
		fp>>number>>name>>type>>co>>len;
		s[i].set(number,name,type,co,len);							
		cout<<setw(15)<<s[i].get_number()<<setw(15)<<s[i].get_name()<<setw(15)<<s[i].get_type()<<setw(15)<<s[i].get_cost()<<setw(15)<<s[i].get_length()<<endl;
			}
			fp.close();
			delete []s;
		}
	}
	
	return 0;}




