#include<iostream>
#include<fstream>
#include<iomanip>
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::endl;
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
int myLen(const char* str) {
	int res = 0;
	for (res; str[res] != '\0'; res++);
	return res;
}

int myCmp(const char* str1, const char* str2) {
	int res=0;
	int len=myLen(str1);
	if(myLen(str2)<len){len=myLen(str2);}
	for(int i=0;i<len;i++){
		if(str1[i]>str2[i]){res=1;break;}
		if(str1[i]<str2[i]){res=-1;break;}
	}
	if((res==0) && (myLen(str1)>myLen(str2))){res=1;}
	if((res==0) && (myLen(str1)<myLen(str2))){res=-1;}	
	return res;
}
class human{
	protected:
		char name[20];
		int id;
	public:
		void print_to_file(int count,ofstream& f){
			char Name[20];
			int ID;
			for(int i=0;i<count;i++){
				cout<<"\x1B[36m\nВведите имя человека "<<i+1<<" ";
				cin>>Name;
				cout<<"\nВведите ID человека "<<i+1<<" ";
				cin>>ID;
				for(int j=0;j<myLen(Name);j++){name[j]=Name[j];}
				name[myLen(Name)]='\0';
				id=ID;
				f<<name<<" "<<id<<endl;
			}
		}
		void print_to_console(int count,ifstream& f){
			char Name[20];
			int ID;
			for(int i=0;i<count;i++){
				f>>Name;
				f>>ID;
				for(int j=0;j<myLen(Name);j++){name[j]=Name[j];}
				name[myLen(Name)]='\0';
				id=ID;
				cout<<"\x1B[36m"<<setw(15)<<name<<setw(10)<<id<<"\n";
			}
		}
		
		
};
class student: public human{};
class programmer: public human{};
class tester: public human{};
class supervisor: public human{};

int main(int argc,char **argv){
	if (argc==1){
		cout<<logo<<"\n";
		cout<<"\x1B[32m"<<"Аргументы: \n";
		cout<<"-h or --help для вызова подсказки\n";
		cout<<"-w <file_name> для создания таблицы работников \n";
		cout<<"-r <file_name> для вывода на экран таблицы работников \n";
	}
	if((myCmp(argv[1], "-h") == 0 || myCmp(argv[1], "--help") == 0) && argc==2){
		cout<<"\x1B[32m"<<"Программа предназначена для создания и вывода базы данных о работниках компании.\n";	
		cout<<"В первой строке файла записано число стажеров, программистов, тестировщиков и руководителей.\n";
	}
	if(myCmp(argv[1],"-w")==0 && argc==3){
		ofstream fp(argv[2],ios::binary);
		if(fp.is_open()) {
			int count_st=0,count_tes=0,count_sup=0,count_pr=0;
			cout<<"\n\x1B[36mВведите колличество стажёров-студентов ";
			cin>>count_st;
			cout<<"\nВведите колличество программистов ";
			cin>>count_pr;
			cout<<"\nВведите колличество тестировщиков ";
			cin>>count_tes;
			cout<<"\nВведите колличество руководителей ";
			cin>>count_sup;
			fp<<count_st<<" "<<count_pr<<" "<<count_tes<<" "<<count_sup<<"\n";
			if(count_st>0){
				cout<<"\x1B[32m\nЗапись стажеров\n";
				fp<<"Стажёры:\n";
				student st;
				st.print_to_file(count_st,fp);
			}
			if(count_pr>0){
				cout<<"\x1B[32m\nЗапись программистов\n";
				fp<<"Программисты:\n";
				programmer pr;
				pr.print_to_file(count_pr,fp);
			}
			if(count_tes>0){
				cout<<"\x1B[32m\nЗапись тестировщиков\n";
				fp<<"Тестировщики:\n";
				tester tes;
				tes.print_to_file(count_tes,fp);
			}
			if(count_sup>0){
				cout<<"\x1B[32m\nЗапись руководителей\n";
				fp<<"Руководители:\n";
				supervisor sp;
				sp.print_to_file(count_sup,fp);
			}
		fp.close();
		}
	}
	if(myCmp(argv[1],"-r")==0 && argc==3){
		ifstream fp(argv[2]);
		if(fp.is_open()) {
			int count[4];
			fp>>count[0]>>count[1]>>count[2]>>count[3];
			if(count[0]>0){
				char position[20];
				fp>>position;
				student st;
				cout<<"\x1B[32mСтажеры:\n";
				st.print_to_console(count[0],fp);
			}
			if(count[1]>0){
				char position[20];
				fp>>position;
				programmer pr;
				cout<<"\x1B[32mПрограмисты:\n";
				pr.print_to_console(count[1],fp);
			}
			if(count[2]>0){
				char position[20];
				fp>>position;
				tester ts;
				cout<<"\x1B[32mТестировщики:\n";
				ts.print_to_console(count[2],fp);
			}
			if(count[3]>0){
				char position[20];
				fp>>position;
				supervisor sp;
				cout<<"\x1B[32mРуководители:\n";
				sp.print_to_console(count[3],fp);
			}
		}
		fp.close();
	}
	return 0;
}
