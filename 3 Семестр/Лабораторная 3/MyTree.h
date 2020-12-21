#pragma once
#ifndef _MyTree_H_
#define _MyTree_H_
#include<iostream>
#include<iomanip>
#define N 5             //����������� ������������� ���������� �������
using namespace std;
// ����� ���� ������
template <typename T>
struct Node {
    T key;              //�������� ����
    int number;         //����� ����
    Node* child[N];     //��������� �� ������ �������
    Node* parent;       //��������� �� ��������
    int height;         //������ ����
    int count_child;    //������� ���������� �����
    Node() {
        parent = nullptr;
        count_child = 0;
        key = T();
        height = 0;
        number = 0;
    }
    ~Node() {}
};
int num = 0;            //������� �����
/*������� ��� �������� ����
    ��������� �������:
        1)�������� ����
    ��������� - ��������� �� ����
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
/* ������� ��� ���������� ���� � ������ �� ������� ��������
    ��������� �������:
        1)��������� �� ������ ������
        2)������ ������������� ����
        3)�������� ����
*/
template <typename T>
void push(Node<T>* PNode, int index, T key) {
    if (PNode->number == index) {
        if (PNode->count_child == N) {
            cout << "\u001B[31m� ����� ���� ������������ ���������� �������" << endl;
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
/*������� ���������� ������
    ��������� �������:
        1)��������� �� ������ ������
        2)���������� �����
*/
template <typename T>
void filling(Node<T>* PNode, int count) {
    int p_i;
    T k;
    for (int i = 1; i < count + 1; i++) {
        cout << "\u001B[32m\n\n���������� ���� " << i + 1 
            << "\u001B[36m\n\t������� ����� ���� �������� ";
        cin >> p_i;
        if (p_i > num) {
            cout << "\u001B[31m���� � ����� ������� ��� �� �������\n";
            i--;

        }
        else {
            cout << "\t������� �������� ���� ";
            cin >> k;
            push(PNode, p_i, k);
        }
    }
}
/*������� �������� ������
    ��������� �������:
        1)��������� �� ������ ������
*/
template <typename T>
void deletion(Node<T>* PNode) {
    for (int i = 0; i < PNode->count_child; i++) {
        deletion(PNode->child[i]);
    }
    delete PNode;
}
/*���������� ��������� << ��� ������ ����������� ����
    ��������� �������:
      1)������ �� ����� ������
      2)��������� �� ����
    ���������- ������ �� ����� ������
*/
template <typename T>
ostream& operator<<(ostream& os, Node<T>* PNode) {
    if (PNode->parent != nullptr) {
        os << "\u001B[32m\n\n����� �������: " << PNode->number
            <<"\u001B[33m\n\t�������� �������: " << PNode->key
            << "\n\t������ �������: " << PNode->height
            << "\n\t����� ��������: " << PNode->parent->number;
        if (PNode->count_child != 0) {
            os << "\n\t������ ������ �������: ";
            for (int i = 0; i < PNode->count_child; i++) {
                os << PNode->child[i]->number << " ";
            }
        }
        else {
            os << "\n\t� ����� ���� ��� �������";
        }

    }
    else {
        os << "\u001B[32m\n\n����� �������: " << PNode->number
            << "\u001B[33m\n\t�������� �������: " << PNode->key
            << "\n\t������ �������: " << PNode->height;
        if (PNode->count_child != 0) {
            os << "\n\t������ ������ �������: ";
            for (int i = 0; i < PNode->count_child; i++) {
                os << PNode->child[i]->number << " ";
            }
        }
        else {
            os << "\n\t� ����� ���� ��� �������";
        }
    }
    return os;
}
/*������� ��� ������ ������
    ��������� �������:
        1)��������� �� ������ ������
*/
template <typename T>
void Print(Node<T>* PNode) {
    cout << PNode;
    for (int i = 0; i < PNode->count_child; i++) {
        Print(PNode->child[i]);
    }
}
#endif
