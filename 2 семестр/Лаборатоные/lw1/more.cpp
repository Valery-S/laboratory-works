#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
int main(int argc,char* argv[])
{
 if( argc > 1 )
 {
        
        ifstream fin;
        fin.open(argv[1]);
        if(fin.is_open())
        {
         int count = 0;
         string dataf;
         getline(fin,dataf,'\0');
         count = dataf.length();
         int k = 1;
         char ch = 1;
         cout<<endl;

         for(int i = 1;i<count;i++){

          cout<<dataf[i];

          if (i%100 == 0 ) {
           cout<<endl;
           k++;
          }

          if( k == 50){
           while(ch!='\n'){
            ch = cin.get();
           }
           ch = 1;
           k = 1;
           cout<<"\x1B[53F"<<endl;
           cout<<"\x1B[0J"<<endl;
           cout<<"\x1B[1A"<<endl;
          }
         }
        }
        else
        {
         cout<<"\x1B[1;5;31m!..    ОШИБКА    ..!\x1B[0m"<<endl;
         cout<<"\x1B[1;5;31m!..Файл Не Открыт..!\x1B[0m"<<endl;
         return -1;
        }
        fin.close();

 }
return 0;
}
