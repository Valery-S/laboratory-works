#include<iostream>							//подключение библиотеки ввода-вывода
using namespace std; 						// использование пространства имён std
template <typename T>						//создание внутреннего класса для хранения		
class Node {								//элемента списка
public:
	T value; 								//значение элемента
	Node* Next; 							//указатель на следующий элемент
	Node(T val = T(), Node* n = nullptr) {	//конструктор с параметрами
		value = val;
		Next = n;
	}
};
template <typename T> 						// создание шаблонного класса list
class List {
	public: 								//публичная секция класса 
		List() { 							// конструктор по умолчанию
			head = nullptr; 				//указатель на первый элемент списка
		}
		~List() { 							//деструктор
			delete [] head;
		}
		void push_back(T data ) { 			//метод добавления элемента в конец списка
			if (head == nullptr) { 			//если список пустой, то выделяем память и 
				head = new Node<T>(data); 	//добавляем элемент
			}
			else {								//иначе доходим до последнего элемента,				
				Node<T> *cur= head; 			//выделяем память и добавляем элемент
				while (cur->Next != nullptr) {
					cur = cur->Next;
				}
				cur->Next = new Node <T>(data);
			}
		}
		T& operator[](const int index) {	//перегрузка оператора, для обращения к			
			int counter = 0; 				//элементам списка 
			Node <T>* cur = head;
			while (cur != nullptr) {
				if (counter==index){
					return cur->value;
				}
				cur = cur->Next;
				counter++;
			}
		}
		Node<T> *head; 		//член класса list, хранит указатель на первый элемент 
};
template <typename T>
void swaping(List<T>* lst) {						//метод, меняющий местами крайние элементы 
	T buf = lst->head->value;
	Node <T>* cur = lst->head;
	while (cur->Next != nullptr) {
		cur = cur->Next;
	}
	lst->head->value = cur->value;
	cur->value = buf;
}
int main() {						
	setlocale(LC_ALL,"ru");				//включение русского языка
	List <float> lst; 			
	int n;
	float a;
	cout << "Введите количество элементов в списке"<<endl;
	cin >> n;
	for (int i = 0; i < n; i++){		//запись элементов в список
		cout<<"Введите элемент списка под номером "<<i+1<<endl;
		cin >> a;
		lst.push_back(a);
	}
	cout << "Текущий список" << endl;	//вывод списка на консоль
	for (int i = 0; i < n; i++) {
		cout << lst[i]<<endl;
	}
	swaping(&lst);						//использование функции перестановки крайних элементов
										//вывод списка на консоль
	cout << "Список после перестановки крайних элементов " << endl;
	for (int i = 0; i < n; i++) {
		cout << lst[i] << endl;
	}
	return 0;
}
