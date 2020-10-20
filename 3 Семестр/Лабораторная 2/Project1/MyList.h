#pragma once
#ifndef _MyList_H_
#define _MyList_H_
template <typename T> 					// �������� ���������� ������ list
class List {
private:
	template <typename T>				//�������� ����������� ������ ��� ��������		
	class Node {						//�������� ������
	public:
		T value; 						//�������� ��������
		Node* Next; 					//��������� �� ��������� �������
		Node(T val = T(), Node* n = nullptr) {	//����������� � �����������
			value = val;
			Next = n;
		}
	};
	int size;							//���������� ��������� � ������
public: 								//��������� ������ ������ 
	Node<T>* head; 						//��������� �� ������ �������
	List() { 							// ����������� �� ���������
		head = nullptr; 	
		size = 0;
	}
	~List() {delete[] head;} 			//����������

	void push_back(T data) { 			//����� ���������� �������� � ����� ������
										//���� ������ ������, �� �������� ������ � ��������� �������
		if (head == nullptr) { 
			head = new Node<T>(data);
		}	
		else {							//����� ������� �� ���������� ��������,				
			Node<T>* cur = head; 		//�������� ������ � ��������� �������
			while (cur->Next != nullptr) {
				cur = cur->Next;
			}
			cur->Next = new Node <T>(data);
		}
		size++;
	}
	T& operator[](const int index) {	//���������� ���������, ��� ��������� �			
		int counter = 0; 				//��������� ������ 
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
