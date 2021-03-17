#pragma once
#ifndef _MyTree_H_
#define _MyTree_H_
#include<iostream>
#include<iomanip>
#define N 5             		//Определение максимального количества сыновей
using namespace std;
// Класс узла дерева
template <typename T>
struct Node {
    T key;              		//Значение узла
    int number;         		//Номер узла
    Node* child[N];     		//Указатель на массив сыновей
    Node* parent;       		//Указатель на родителя
    int height;         		//Высота узла
    int count_child;    		//Текущее количество детей
    Node() {
        parent = nullptr;
        count_child = 0;
        key = T();
        height = 0;
        number = 0;
    }
    ~Node() {}
};
int num = 0;            		//Счётчик узлов
/*Функция для создания узла
    Параметры функции:
        1)Значение узла
    Результат - указатель на узел
*/
template <typename T>
Node<T>* newNode(T key) {
    num++;
    Node<T>* temp = new Node<T>;
    temp->key = key;
    temp->number = num;
    for (int i = 0; i < N; i++) {
        temp->child[i] = NULL;
    }
    return temp;
}
/* Функция для добавления узла в дерево по индексу родителя
    Параметры функции:
        1)Указатель на корень дерева
        2)Индекс родительского узла
        3)Значение узла
*/
template <typename T>
void push(Node<T>* PNode, int index, T key) {
    if (PNode->number == index) {
        if (PNode->count_child == N) {
            cout << "\u001B[31mУ этого узла максимальное количество сыновей" << endl;
        }
        else {
            if (PNode->parent == nullptr) {
                PNode->height = 1;
            }
            PNode->child[PNode->count_child] = newNode(key);
            PNode->child[PNode->count_child]->parent = PNode;
            PNode->child[PNode->count_child]->height = PNode->height + 1;
            PNode->count_child++;
        }
    }
    for (int i = 0; i < PNode->count_child; i++) {
        push(PNode->child[i], index, key);
    }
}
/*Функция заполнения дерева
    Параметры функции:
        1)Указатель на корень дерева
        2)Количество узлов
*/
template <typename T>
void filling(Node<T>* PNode, int count) {
    int p_i;
    T k;
    for (int i = 1; i < count + 1; i++) {
        cout << "\u001B[32m\n\nДобавление узла " << i + 1 
            << "\u001B[36m\n\tВведите номер узла родителя ";
        cin >> p_i;
        if (p_i > num) {
            cout << "\u001B[31mУзел с таким номером ещё не записан\n";
            i--;

        }
        else {
            cout << "\tВведите значение узла ";
            cin >> k;
            push(PNode, p_i, k);
        }
    }
}
/*Функция удаления дерева
    Параметры функции:
        1)Указатель на корень дерева
*/
template <typename T>
void deletion(Node<T>* PNode) {
    for (int i = 0; i < PNode->count_child; i++) {
        deletion(PNode->child[i]);
    }
    delete PNode;
}
/*Перегрузка оператора << для вывода содержимого узла
    Параметры функции:
      1)Ссылка на поток вывода
      2)Указатель на узел
    Результат- ссылка на поток вывода
*/
template <typename T>
ostream& operator<<(ostream& os, Node<T>* PNode) {
    if (PNode->parent != nullptr) {
        os << "\u001B[32m\n\nНомер вершины: " << PNode->number
            <<"\u001B[33m\n\tЗначение вершины: " << PNode->key
            << "\n\tВысота вершины: " << PNode->height
            << "\n\tНомер родителя: " << PNode->parent->number;
        if (PNode->count_child != 0) {
            os << "\n\tНомера вершин сыновей: ";
            for (int i = 0; i < PNode->count_child; i++) {
                os << PNode->child[i]->number << " ";
            }
        }
        else {
            os << "\n\tУ этого узла нет сыновей";
        }

    }
    else {
        os << "\u001B[32m\n\nНомер вершины: " << PNode->number
            << "\u001B[33m\n\tЗначение вершины: " << PNode->key
            << "\n\tВысота вершины: " << PNode->height;
        if (PNode->count_child != 0) {
            os << "\n\tНомера вершин сыновей: ";
            for (int i = 0; i < PNode->count_child; i++) {
                os << PNode->child[i]->number << " ";
            }
        }
        else {
            os << "\n\tУ этого узла нет сыновей";
        }
    }
    return os;
}
/*Функция для вывода дерева
    Параметры функции:
        1)Указатель на корень дерева
*/
template <typename T>
void Print(Node<T>* PNode) {
    cout << PNode;
    for (int i = 0; i < PNode->count_child; i++) {
        Print(PNode->child[i]);
    }
}
#endif
