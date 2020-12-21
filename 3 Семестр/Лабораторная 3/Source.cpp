/*������� ������:
    ���� N-������. ����� ��������� �� ���������� �� ���� �� �������� ������.
*/
#include<iostream> 
#include"MyTree.h"
#include<vector>
using namespace std;
/*������� ��� ���������� ��������� ��� �������� ������
    ��������� �������:
        1)��������� �� ������ ������
        2)������ ������� �������� �����
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
    setlocale(LC_ALL, "ru");     		//��������� �������� �����
    Node<int>* root;              		//��������� �� ������ ������
    int count;                    		//���������� �����
    int root_key;                 		//�������� �����
    int n=0;                        		//���������� ������, ������� ��
                                        //������ ���� � ���������
    vector<int> numbers;          		//������ ������, ������� �� ������ 
                                        //���� � ���������
    cout << "\u001B[36m������� ���������� ����� � ������ ";
    cin >> count;
    cout << "���� ���������� �� 1 �� " << count
         << "\n\n������� ������� ����� ������ ";
    cin >> root_key;
    root = newNode(root_key);
    filling(root, count - 1);       	//���������� ������
    cout << endl << "\u001B[36m�������������� ������: " << endl;
    Print(root);
    while (n == 0) {
        cout << "\n\u001B[36m������� ���������� ������, ������� �� ������ ���� � ��������� ";
        cin >> n;
        if (n > count) {
            cout << "\u001B[31m � ������ ������ ������";
            n = 0;
        }
    }
    for (int i = 1; i <= n; i++) {    	//������������ ������� �������
        cout << endl << "\u001B[32m������� ����� " << i << " ������� ";
        int a;
        cin >> a;
        if (a > count) {
            cout << "\u001B[31m������� � ����� ������� � ������ ���.��������� ����." << endl;
                i--;

        }
        numbers.push_back(a);
    }
    cout << "\u001B[36m\n\n�������������� ���������: \n" ;
    find_subtree(root, numbers);
    Print(root);
    deletion(root);                 //������������ ������ 
    return 0;
}


