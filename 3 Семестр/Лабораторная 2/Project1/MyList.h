#pragma once
#ifndef _MyList_H_
#define _MyList_H_
template <typename T> 					// создание шаблонного класса list
class List {
private:
	template <typename T>				//создание внутреннего класса для хранения		
	class Node {						//элемента списка
	public:
		T value; 						//значение элемента
		Node* Next; 					//указатель на следующий элемент
		Node(T val = T(), Node* n = nullptr) {	//конструктор с параметрами
			value = val;
			Next = n;
		}
	};
	int size;							//Количество элементов в списке
public: 								//публичная секция класса 
	Node<T>* head; 						//указатель на первый элемент
	List() { 							// конструктор по умолчанию
		head = nullptr; 	
		size = 0;
	}
	~List() {delete[] head;} 			//деструктор

	void push_back(T data) { 			//метод добавления элемента в конец списка
										//если список пустой, то выделяем память и добавляем элемент
		if (head == nullptr) { 
			head = new Node<T>(data);
		}	
		else {							//иначе доходим до последнего элемента,				
			Node<T>* cur = head; 		//выделяем память и добавляем элемент
			while (cur->Next != nullptr) {
				cur = cur->Next;
			}
			cur->Next = new Node <T>(data);
		}
		size++;
	}
	T& operator[](const int index) {	//перегрузка оператора, для обращения к			
		int counter = 0; 				//элементам списка 
		Node <T>* cur = head;
		while (cur != nullptr) {
			if (counter == index) {return cur->value;}
			cur = cur->Next;
			counter++;
		}
	}
	int get_size() { return size; }
};
#endif
