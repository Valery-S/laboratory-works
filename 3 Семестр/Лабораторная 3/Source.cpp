/*Условие задачи:
    Дано N-дерево. Найти поддерево не включающее ни одну из заданных вершин.
*/
#include<iostream> 
#include"MyTree.h"
#include<vector>
using namespace std;
/*Функция для нахождения поддерева без заданных вершин
    Параметры функции:
        1)Указатель на корень дерева
        2)Вектор номеров заданных узлов
*/
template <typename T>
void find_subtree(Node<T>* PNode, vector<int>numb) {
    for (int i = 0; i < PNode->count_child; i++) {
        find_subtree(PNode->child[i], numb);
    }
    for (int j = 0; j < numb.size(); j++) {
        if (PNode->number == numb[j]) {
            Node<T>* cur = PNode->parent;
            int i = 0;
            while (cur->child[i] != PNode) {
                i++;
            }
            for (i; i < cur->count_child - 1; i++) {
                cur->child[i] = cur->child[i + 1];
            }
            cur->count_child--;
        }
    }
}
int main() {
    setlocale(LC_ALL, "ru");     		//Включение русского языка
    Node<int>* root;              		//Указатель на корень дерева
    int count;                    		//Количество узлов
    int root_key;                 		//Значение корня
    int n=0;                        		//Количество вершин, которых не
                                        //должно быть в поддереве
    vector<int> numbers;          		//Номера вершин, которых не должно 
                                        //быть в поддереве
    cout << "\u001B[36mВведите количество узлов в дереве ";
    cin >> count;
    cout << "Узлы номеруются от 1 до " << count
         << "\n\nВведите значние корня дерева ";
    cin >> root_key;
    root = newNode(root_key);
    filling(root, count - 1);       	//Заполнение дерева
    cout << endl << "\u001B[36mСформированное дерево: " << endl;
    Print(root);
    while (n == 0) {
        cout << "\n\u001B[36mВведите количество вершин, которых не должно быть в поддереве ";
        cin >> n;
        if (n > count) {
            cout << "\u001B[31m В дереве меньше вершин";
            n = 0;
        }
    }
    for (int i = 1; i <= n; i++) {    	//Формирование вектора номеров
        cout << endl << "\u001B[32mВведите номер " << i << " вершины ";
        int a;
        cin >> a;
        if (a > count) {
            cout << "\u001B[31mВершины с таким номером в дереве нет.Повторите ввод." << endl;
                i--;

        }
        numbers.push_back(a);
    }
    cout << "\u001B[36m\n\nСформированное поддерево: \n" ;
    find_subtree(root, numbers);
    Print(root);
    deletion(root);                 //Освобождение памяти 
    return 0;
}


