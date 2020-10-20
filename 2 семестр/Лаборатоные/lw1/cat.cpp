#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
int main(int argc, char **argv)
{
	if((argc < 2)||(argc >3))
	{
		std::cout<<"Ошибка, повторите ввод"<<std::endl;
		exit(1);
	}
	if (argc ==2)
	{
		std::ifstream fin(argv[1]);
		std::string line;
		while(getline(fin,line))
		{
		std::cout<<line<<std::endl;
		}
		exit(0);
	}
	std::ifstream fin(argv[2]);
	int k=0;
	char ch;
	while(fin.get(ch))
	{
		k++;
	}
	fin.close();
	fin.open(argv[2]);
	std::string line;
	switch (*(argv[1]+1))
	{
		case *("-n"+1):
		{
			std::cout<<"1. ";
			int i=2;
			int g=0;
			while(fin.get(ch))
			{
				g++;
				std::cout<<ch;
				if ((ch=='\n')&&(k!=g))
				{
					std::cout<<i<<". ";
					i++;
				}
				
			}
		}
		break;
		case *("-b"+1):
		{
			int i=1;
			int g=0;
			while(getline(fin,line))
			{
				if(!all_of(line.begin(),line.end(), isspace))
				{
					std::cout<<i<<". "<<line<<std::endl;
					i++;
				}
				else
				{
					std::cout<<line<<std::endl;
				}
			}
		}
		break;
		case *("-e"+1):
		{
			while(fin.get(ch))
			{
				
				if (ch=='\n')
				{
					std::cout<<"$";
				}
				std::cout<<ch;
				
			}
		}
		break;
		case *("-h"+1):
		{
			char logo[]=
			"Синтаксис утилиты: ./CAT опции файл                      \n"
			"Список опций:                                            \n"
			"-h -Справка                                              \n" 
			"-e -Вывод каждой строки, с прибавлением символа $ в конце\n"
			"-b -Вывод с нумерацией непустых строк                    \n"
			"-n -Вывод с нумерацией всех строк                        \n"
			"-s -Вывод с удалением дублированных пустых строк         \n"
			"-v -Версия утилиты                                       \n";
			std::cout<<logo<<std::endl;
		}
		break;
		case *("-v"+1):
		{
			char logo[]=
			"Версия утилиты: 1.0.0                                    \n";
			std::cout<<logo<<std::endl;
		}
		break;
		case *("-s"+1):
		{
			int i=0;
			while(getline(fin,line))
			{
				
				if(!all_of(line.begin(),line.end(), isspace))
				{
					std::cout<<line<<std::endl;
					i=0;
				}
				else
				{
					if(i==0)
					{
						i++;
						std::cout<<line<<std::endl;
					}
				}
			}
		}
		break;
		default:
		{
			std::cout<<"Ошибка, для получения справки введите -h"<<std::endl;
		}
		break;
	}
	return 0;
}
