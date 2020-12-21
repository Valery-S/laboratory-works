#include<iostream>
#include <cstdlib>				// ��� ������� rand() � srand()
#include <ctime>					// ��� ������� time()
#include"Tree.h"
using namespace std;

/*������� �������� ������������� ����
��������� ������:
	1)��������� �� ���� ������
��������� - ������� ����������� ����: ������ ��� ����
������� ������:
	1)������� ��������- ���� �� ���������.
	2)���� � ���� ����������� "0"-��������� ������, �� �������� �������������.
*/
bool game_is_over(Tree_node* PNode) {
	bool res = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (PNode->field[i][j] == 0) {
				res = false;
			}
		}
	}
	return res;
}
/*������� �������� ������
���������:
	1)��������� �� ���� ������
	2)�������� ������ ������� ������
	3)�������� ������� ������� ������
	4)�������� ������ ����: 1 ��� 2- �������� �������� ��� ����������
	5)�������� ���� char: s ��� � - ����������� ��������: �� ������ ��� �������
	6)�������� ������ ����: 1 ��� -1  - �������� ��������
������� ������:
	1)�������� �������� �������� ����
	2)������� ������� ��������� direction, ���� �� ����� s, �� ��������� �� �������� ��������� step �� ������, ���� directon �����
	  c, �� �������� �� �������
	3)���� �������� ��������������� ������ ����� ����������� � �������� ������ �� � ��� ������ �����, �� ��������� ���� �������� ����
*/
bool check_cell(Tree_node* PNode, int string, int column, const int value, char direction, const int step) {
	bool flag=false;
	int field[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			field[i][j] = PNode->field[i][j];
		}
	}
	if (direction == 'c') {
		if (field[string + step][column] == 0) {
			field[string + step][column] = value;
		}
		if (field[string + step][column] == value) {
			bool res = false;
			for (int i = 0; i < 4; i++) {
				if (PNode->connections[string][column][i] == (string + step) * 10 + column) {
					res = true;
				}
			}
			if (res == false) {
				flag = true;
				push(PNode, PNode->number, field);
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
							PNode->child[PNode->count_child - 1]->count_connections[i][j] = PNode->count_connections[i][j];
							PNode->child[PNode->count_child - 1]->connections[i][j][0] = PNode->connections[i][j][0];
							PNode->child[PNode->count_child - 1]->connections[i][j][1] = PNode->connections[i][j][1];
							PNode->child[PNode->count_child - 1]->connections[i][j][2] = PNode->connections[i][j][2];
							PNode->child[PNode->count_child - 1]->connections[i][j][3] = PNode->connections[i][j][3];
					}
				}
				PNode->child[PNode->count_child - 1]->connections[string + step][column][PNode->child[PNode->count_child - 1]->count_connections[string + step][column]] = string * 10 + column;
				PNode->child[PNode->count_child - 1]->connections[string][column][PNode->child[PNode->count_child - 1]->count_connections[string][column]] = (string + step) * 10 + column;
				PNode->child[PNode->count_child - 1]->count_connections[string][column]++;
				PNode->child[PNode->count_child - 1]->count_connections[string + step][column]++;
			}
		}
	}
	if (direction == 's') {
		if (field[string][column + step] == 0) {
			field[string][column + step] = value;
		}
		if (field[string][column + step] == value) {
			bool res = false;
			for (int i = 0; i < 4; i++) {
				if (PNode->connections[string][column][i] == string * 10 + column + step) {
					res = true;
				}
			}
			if (res == false) {
				flag = true;
				push(PNode, PNode->number, field);
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						PNode->child[PNode->count_child - 1]->count_connections[i][j] = PNode->count_connections[i][j];
						PNode->child[PNode->count_child - 1]->connections[i][j][0] = PNode->connections[i][j][0];
						PNode->child[PNode->count_child - 1]->connections[i][j][1] = PNode->connections[i][j][1];
						PNode->child[PNode->count_child - 1]->connections[i][j][2] = PNode->connections[i][j][2];
						PNode->child[PNode->count_child - 1]->connections[i][j][3] = PNode->connections[i][j][3];
					}
				}
				PNode->child[PNode->count_child - 1]->connections[string][column + step][PNode->child[PNode->count_child - 1]->count_connections[string][column + step]] = string * 10 + column;
				PNode->child[PNode->count_child - 1]->connections[string][column][PNode->child[PNode->count_child - 1]->count_connections[string][column]] = string * 10 + column + step;
				PNode->child[PNode->count_child - 1]->count_connections[string][column]++;
				PNode->child[PNode->count_child - 1]->count_connections[string][column + step]++;
			}
		}
	}
	return flag;
}
/*������� �������� ����, ��� �� ������� ���� ��� ����������� ������� �� ������� ������ � ������, ����������� ��� ����
��������� �������:
	1)��������� �� ���� ������
	2)����� ������ ������ ������
	3)����� ������� ������ ������
	4)����� ������ ������ ������
	5)����� ������� ������ ������
������� ������:
	1)���� � ������ ������ ���� ����� � �������, �� ���������� flag_first=true
	2)���� � ������ ������ ���� ����� � �������, �� ���������� flag_second=true
	3)���� ������ ��������� � ��������, �� ��������� ����� ������� ������ ����� �����
*/
bool is_square_up(Tree_node* PNode, int string_first, int column_first, int string_second, int column_second) {
	bool flag_first = false;
	bool flag_second = false;
	bool flag_up = false;
	for (int i = 0; i < 4; i++) {
		if (PNode->connections[string_first][column_first][i] == (string_first - 1) * 10 + column_first) {
			flag_first = true;
		}
		if (PNode->connections[string_second][column_second][i] == (string_second - 1) * 10 + column_second) {
			flag_second = true;
		}
	}
	if (flag_second == true && flag_first == true) {
		for (int i = 0; i < 4; i++) {
			if (PNode->connections[string_first - 1][column_first][i] == (string_second - 1) * 10 + column_second) {
				flag_up = true;
			}
		}
	}
	return flag_up;
}
/*������� �������� ����, ��� �� ������� ���� ��� ����������� ������� �� ������� ������ � ������, ����������� ��� ����
��������� �������:
	1)��������� �� ���� ������
	2)����� ������ ������ ������
	3)����� ������� ������ ������
	4)����� ������ ������ ������
	5)����� ������� ������ ������
������� ������:
	1)���� � ������ ������ ���� ����� � ������, �� ���������� flag_first=true
	2)���� � ������ ������ ���� ����� � ������, �� ���������� flag_second=true
	3)���� ������ ��������� � �������, �� ��������� ����� ������ ������ ����� �����
*/
bool is_square_down(Tree_node* PNode, int string_first, int column_first, int string_second, int column_second) {
	bool flag_first = false;
	bool flag_second = false;
	bool flag_down = false;
	for (int i = 0; i < 4; i++) {
		if (PNode->connections[string_first][column_first][i] == (string_first + 1) * 10 + column_first) {
			flag_first = true;
		}
		if (PNode->connections[string_second][column_second][i] == (string_second + 1) * 10 + column_second) {
			flag_second = true;
		}
	}
	if (flag_second == true && flag_first == true) {
		for (int i = 0; i < 4; i++) {
			if (PNode->connections[string_first + 1][column_first][i] == (string_second + 1) * 10 + column_second) {
				flag_down = true;
			}
		}
	}
	return flag_down;
}
/*������� �������� ����, ��� �� ������� ���� ��� ����������� ������� �� ������� ������ � ������, ����������� ������
��������� �������:
	1)��������� �� ���� ������
	2)����� ������ ������ ������
	3)����� ������� ������ ������
	4)����� ������ ������ ������
	5)����� ������� ������ ������
������� ������:
	1)���� � ������ ������ ���� ����� � ������, �� ���������� flag_first=true
	2)���� � ������ ������ ���� ����� � ������, �� ���������� flag_second=true
	3)���� ������ ��������� � �������, �� ��������� ����� ������ ������ ����� �����
*/
bool is_square_right(Tree_node* PNode, int string_first, int column_first, int string_second, int column_second) {
	bool flag_first = false;
	bool flag_second = false;
	bool flag_right = false;
	for (int i = 0; i < 4; i++) {
		if (PNode->connections[string_first][column_first][i] == string_first * 10 + column_first + 1) {
			flag_first = true;
		}
		if (PNode->connections[string_second][column_second][i] == string_second * 10 + column_second + 1) {
			flag_second = true;
		}
	}
	if (flag_second == true && flag_first == true) {
		for (int i = 0; i < 4; i++) {
			if (PNode->connections[string_first][column_first + 1][i] == string_second * 10 + column_second + 1) {
				flag_right = true;
			}
		}
	}
	return flag_right;
}
/*������� �������� ����, ��� �� ������� ���� ��� ����������� ������� �� ������� ������ � ������, ����������� �����
��������� �������:
	1)��������� �� ���� ������
	2)����� ������ ������ ������
	3)����� ������� ������ ������
	4)����� ������ ������ ������
	5)����� ������� ������ ������
������� ������:
	1)���� � ������ ������ ���� ����� � �����, �� ���������� flag_first=true
	2)���� � ������ ������ ���� ����� � �����, �� ���������� flag_second=true
	3)���� ������ ��������� � �������, �� ��������� ����� ����� ������ ����� �����
*/
bool is_square_left(Tree_node* PNode, int string_first, int column_first, int string_second, int column_second) {
	bool flag_first = false;
	bool flag_second = false;
	bool flag_left = false;
	for (int i = 0; i < 4; i++) {
		if (PNode->connections[string_first][column_first][i] == string_first * 10 + column_first - 1) {
			flag_first = true;
		}
		if (PNode->connections[string_second][column_second][i] == string_second * 10 + column_second - 1) {
			flag_second = true;
		}
	}
	if (flag_second == true && flag_first == true) {
		for (int i = 0; i < 4; i++) {
			if (PNode->connections[string_first][column_first - 1][i] == string_second * 10 + column_second - 1) {
				flag_left = true;
			}
		}
	}
	return flag_left;
}
/*������� �������� ����, ��� �� ������� ���� ��� ����������� �������
��������� �������:
	1)��������� �� ���� ������
	2)����� ������ ������ ������
	3)����� ������� ������ ������
	4)����� ������ ������ ������
	5)����� ������� ������ ������
������� ������:
	1)������� ����� ������.���� ������ ����������� �� ����� ������:
	1.1)���� ��� ���������,�� �������� ������� is_square_up()
	1.2)���� ��� ������,�� �������� ������� is_square_down()
	1.3)���� ������ �� �������,�� ������� ������� is_square_up() � is_square_down()
	2)������� ����� �������. ���� ������ � ����� �������:
	2.1)���� �� ���������,�� �������� ������� is_square_left()
	2.2)���� �� ������,�� �������� ������� is_square_right()
	2.3)���� ������� �� �������, �� ������� ������� is_square_left() � is_square_right()
*/
void is_square(Tree_node* PNode, int string_first, int column_first, int string_second, int column_second) {
	bool flag = false;
	if (string_first == string_second) {
		if (string_first == 9) {
			flag = is_square_up(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) {PNode->is_square = true;}
		}
		if (string_first == 0) {
			flag = is_square_down(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
		}
		if (string_first > 0 && string_first < 9) {
			flag = is_square_up(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
			flag = is_square_down(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
		}
	}
	if (column_first == column_second) {
		if (column_first == 9) {
			flag = is_square_left(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
		}
		if (column_first == 0) {
			flag = is_square_right(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
		}
		if (column_first > 0 && column_first < 9) {
			flag = is_square_left(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
			flag = is_square_right(PNode, string_first, column_first, string_second, column_second);
			if (flag == true) { PNode->is_square = true; }
		}
	}
}
/*������� ��������� ����
��������� ������:
	1)��������� �� ���� ������
	2)�������� ������ ����: 1, ���� ����� ������������� ��� ��� ����������,
	  2 - ��� ��������.
������� ������:
	1)������������� ��� �������� ������ �������� �������� ����
	2)���� �������� ����� �����������, �� ������������� ��� �������.
	3)� ����������� �� ������� �������������� �������� ������
	4)��� ���� ��� �������, ��������� ��� �� ������� ������� �� ������ ����
*/
void generation_move(Tree_node* PNode, const int value) {
	bool flag;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (PNode->field[i][j] == value) {
				if (i == 0 && j == 0) {
					flag=check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) {is_square(PNode->child[PNode->count_child-1], i, j, i, j + 1);}
					flag=check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i+1, j );}
				}
				if (i == 0 && j == 9) {
					flag=check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1);}
					flag=check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i + 1, j);}
				}
				if (i == 9 && j == 0) {
					flag=check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i - 1, j);}
					flag=check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j + 1);}
				}
				if (i == 9 && j == 9) {
					flag=check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i - 1, j);}
					check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1); }
				}
				if (i == 0 && j > 0 && j < 9) {
					flag=check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1); }
					flag=check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j + 1); }
					flag=check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i + 1, j); }
				}
				if (i == 9 && j > 0 && j < 9) {
					flag=check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1); }
					flag=check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j + 1); }
					flag=check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i - 1, j); }
				}
				if (j == 0 && i != 0 && i != 9) {
					flag=check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i - 1, j); }
					flag=check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i + 1, j); }
					flag=check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j+1); }
				}
				if (j == 9 && i != 0 && i != 9) {
					flag = check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i - 1, j); }
					flag = check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i + 1, j); }
					flag = check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1); }
				}
				if (i != 0 && i != 9 && j != 0 && j != 9) {
					flag = check_cell(PNode, i, j, value, 's', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j - 1); }
					flag = check_cell(PNode, i, j, value, 's', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i, j + 1); }
					flag = check_cell(PNode, i, j, value, 'c', -1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i-1, j); }
					flag = check_cell(PNode, i, j, value, 'c', 1);
					if (flag == true) { is_square(PNode->child[PNode->count_child - 1], i, j, i+1, j); }
				}
			}
		}
	}
}
/*������� ��������� ������ ��������� �����
���������:
	1)��������� �� ������ ������
������� ������:
	1)������� �����������, ���� ������ ������ �� ����� 5
	2)���� ������ �������� ������ ��������, �� ��������� ��� ����������
	2.1)���� �� ���������� ���� ��� ������ �������, �� ��������� ���� � ������� ���������� ���� �.�. ������� ���������� ���
	2.2)���� �� ���������� ���� �� ��� ������ �������, �� �������� ������� generation_move � ���������� 2.
	3)���� ������ �������� ������ ������, �� ��������� ��� ��������
	3.1)���� �� ���������� ���� ��� ������ �������, �� ��������� ���� � ������� ���������� ���� �.�. ��������� ���������� ���
	3.2)���� �� ���������� ���� �� ��� ������ �������, �� �������� ������� generation_move � ���������� 1.
*/
void make_tree(Tree_node* PNode) {
	if (PNode->height % 2 == 1) {
		if (PNode->is_square == false) {
			generation_move(PNode, 1);
		}
		else {
			push(PNode, PNode->number, PNode->field);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					PNode->child[0]->count_connections[i][j] = PNode->count_connections[i][j];
					PNode->child[0]->connections[i][j][0] = PNode->connections[i][j][0];
					PNode->child[0]->connections[i][j][1] = PNode->connections[i][j][1];
					PNode->child[0]->connections[i][j][2] = PNode->connections[i][j][2];
					PNode->child[0]->connections[i][j][3] = PNode->connections[i][j][3];
				}
			}
		}
	}
	if (PNode->height % 2 == 0) {
		if (PNode->is_square == false) {
			generation_move(PNode, 2);
		}
		else {
			push(PNode, PNode->number, PNode->field);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					PNode->child[0]->count_connections[i][j] = PNode->count_connections[i][j];
					PNode->child[0]->connections[i][j][0] = PNode->connections[i][j][0];
					PNode->child[0]->connections[i][j][1] = PNode->connections[i][j][1];
					PNode->child[0]->connections[i][j][2] = PNode->connections[i][j][2];
					PNode->child[0]->connections[i][j][3] = PNode->connections[i][j][3];
				}
			}
		}
	}
	if (PNode->height <= 3) {
		for (int i = 0; i < PNode->count_child; i++) {
			make_tree(PNode->child[i]);
		}
	}
}
/*��������� �������
���������:
	1)��������� �� ���� ������
������� ������:
	1)��������������� �������� ������ �������� ����
	2)���� �������� ������ ����� 1, �� ��� ����������� ����������. � ���������� ������������ ���������� ������ ���� ������ 
	3)���� �������� ������ ����� 2, �� ��� ����������� ��������. �� ���������� ���������� ���������� ������ ���� ������ 
*/
void get_assessment(Tree_node* PNode) {
	int res = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (PNode->field[i][j] == 1) {
					res = res + PNode->count_connections[i][j];
				}
				if (PNode->field[i][j] == 2) {
					res = res - PNode->count_connections[i][j];
				}
			}
		}
	PNode->assessment = res;
}
/*������� ����� ����� ���������
���������:
	1)��������� �� ���� ������
������� ������:
	1)���� ���� �������� ������, �� ����������� ��� ������
	2)���� ��������� �� ��� ������� ����, �� ��������� ������� � ������������� ��������
	3)���� ���� �� �������� ������, �� �������� �������� alpha � betta �������� ����
	4)��������� �������� ����������� �������
	5)���� ��������� ��� �������, �� ���� ��������
	6)���� ���� �� ������:
	6.1)���� �������� ��������� �� ������ ������ (��������), �� ������������ �������� betta �������� ����
	6.2)���� �������� ��������� �� �������� ������ (���������), �� ������������ �������� alpha �������� ����
	6.3)���� � �������� ���� alpha<betta:
	6.3.1)�������� ������ �������� ����� ������ �������� ����
	6.3.2)���� � ���� ���� ��������� ����, �� ��������� � ����
	6.3.3)��������� � �������� �������� ����
	6.4)���� � �������� ���� alpha>betta:
	6.4.1)��������� � �������� �������� ����
	6.4.2)���������� ����������� ������� = ���������� �������
	6.4.3)���� ��������
*/
void alpha_betta(Tree_node* PNode) {
	if (PNode->height == 5) {
		get_assessment(PNode);
	}
	if (PNode->count_check_child != PNode->count_child) {
		for (int i = PNode->count_check_child; i <PNode->count_child; i++){
			alpha_betta(PNode->child[i]);
		}
	}
	if (PNode->height != 1) {
		PNode->alpha = PNode->parent->alpha;
		PNode->betta = PNode->parent->betta;
	}
	for (int i = 0; i < PNode->count_child; i++) {
		if (PNode->child[i]->is_check == true) {
			PNode->count_check_child++;
		}
	}
	if (PNode->count_check_child == PNode->count_check_child) {
		PNode->is_check = true;
	}
	if (PNode->height != 1) {
		if (PNode->parent->height % 2 == 1) {
			if (PNode->parent->betta > PNode->assessment)
				PNode->parent->betta = PNode->assessment;
		}
		if (PNode->parent->height % 2 == 0) {
			if (PNode->parent->alpha < PNode->assessment) {
				PNode->parent->alpha = PNode->assessment;
			}
		}
		if (PNode->parent->alpha < PNode->parent->betta) {
			PNode->parent->assessment = PNode->assessment;
			if (PNode->next_brother != nullptr) {
				PNode = PNode->next_brother;
			}
			else {
				PNode = PNode->parent;
			}
		}
		else {
			PNode = PNode->parent;
			PNode->count_check_child = PNode->count_child;
			PNode->is_check = true;
		}
	}
}
/*������� ������ ������� ����
���������:
	1)��������� �� ������ ������
������� ������:
	1)��������� ������ ������� �����
	2)���� �������� ������ ���� ����� ������ �����, �� ������ �������� ���� ����� �� �������� ���� �������� ����
	3)���� ����������� ��� ���� ��� � �������, ������ ������ �����, �� � ������������ 50%
		(��������� ������� �������� ���������������� ����� �� ������� �� 2) �������� �������� ���� �����
*/
void choose_best_move(Tree_node* PNode) {
	int tmp = 0;
	srand(unsigned int(time(0)));
	for (int k = 0; k < PNode->count_child; k++) {
		if (PNode->child[k]->assessment == PNode->assessment) {
			tmp++;
			if (tmp == 1) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						PNode->field[i][j] = PNode->child[k]->field[i][j];
						PNode->count_connections[i][j] = PNode->child[k]->count_connections[i][j];
						for (int l = 0; l < 4; l++){
							PNode->connections[i][j][l] = PNode->child[k]->connections[i][j][l];
						}
					}
				}
				if (PNode->child[k]->is_square == true) {PNode->is_square = true;}
			}
			else {
				int r = rand() % 2;
				if (r == 0) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							PNode->field[i][j] = PNode->child[k]->field[i][j];
							PNode->count_connections[i][j] = PNode->child[k]->count_connections[i][j];
							for (int l = 0; l < 4; l++) {
								PNode->connections[i][j][l] = PNode->child[k]->connections[i][j][l];
							}
						}
					}
					if (PNode->child[k]->is_square == true) { PNode->is_square = true; }
				}
			}
		}
	}
}
/*������� ������ ������� ����
���������:
	1)��������� �� ���� ������
������� ������:
	1)���� �������� ������ ����� 1, �� ������� ������� �����,2 - �����, 0-�����
	2)���� � ������ ���� ����� � ������, �� ������� "-" ���������������� �����, ����� " "
	3)���� � ������ ���� ����� � ������, �� ������� "|"���������������� ����� " "
*/
void Print_field(Tree_node* PNode) {
	cout << " \u001B[33m 0   1   2   3   4   5   6   7   8   9\n";
	for (int i = 0; i < 10; i++) {
		
		if (i > 0) {
			for (int j = 0; j < 10; j++) {
				bool f = false;
				for (int k = 0; k < 4; k++) {
					if (PNode->connections[i][j][k] == (i - 1) * 10 + j) {f = true;}
				}
				if (f == true) {
					if (PNode->field[i][j] == 1) {cout << "\u001B[31m  | ";}
					else {cout << "\u001B[34m  | ";}
				}
				else {cout << "    ";}
			}
			cout << "\n";
		}
		cout << "\u001B[33m" << i << " ";
		for (int j = 0; j < 10; j++) {
			if (PNode->field[i][j] == 1) {cout << "\u001B[31m.";}
			if (PNode->field[i][j] == 2) {cout << "\u001B[34m.";}
			if (PNode->field[i][j] == 0) {cout << "\u001B[32m.";}
			bool f = false;
			for (int k = 0; k < 4; k++) {
				if (PNode->connections[i][j][k] == i * 10 + j + 1) {f = true;}
			}
			if (f == true) {
				if (PNode->field[i][j] == 1) {cout << "\u001B[31m - ";}
				else {cout << "\u001B[34m - ";}
			}
			else {cout << "   ";}
		}
		cout << "\n";
	}
	cout << "\n";
}
/*������� �������� ����� ������
��������� �������:
	1)������� ��������� �������� ������� ����
������� ������:
	1)�������� ����� ���� � ���������� ���������
	2)������ ���� ����� 1
*/
Tree_node* creat_root(int start_field[10][10]) {
	Tree_node* root = newNode(start_field);
	root->height = 1;
	return root;
}
/*������� ������������ ����� 
���������:
	1)��������� �� ������ 
������� ������:
	1)����������� ��������� ����, ������ ������ � �� ���������� �� ��������� ����������
	2)�������� ������ �� ��������� �� ������
	3)�������� ������ �����, �� ����������� ���������
	4)���������� ������� ����������� �����
*/
Tree_node * re_create_root(Tree_node* root) {
	int field[10][10];
	int count_connections[10][10];
	int connections[10][10][4];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			field[i][j] = root->field[i][j];
			count_connections[i][j] = root->count_connections[i][j];
			for (int k = 0; k < 4; k++) {
				connections[i][j][k] = root->connections[i][j][k];
			}
		}
	}
	deletion(root);
	root = creat_root(field);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			root->count_connections[i][j] = count_connections[i][j];
			for (int k = 0; k < 4; k++) {
				root->connections[i][j][k] = connections[i][j][k];
			}
		}
	}
	return root;
}
/*������� ���������� ���� ��������
��������� ������:
	1)��������� �� ���� ������
������� ������:
	1)����������� ������ ������ � ������� ��������� ������.
	2)���� ��� ������� �� �������� [0;9], �� ���������� �� ������, ������� ���������������.
	3)����������� ������ ������ � ������� ������� ������.
	4)���� ��� ������� �� �������� [0;9], �� ���������� �� ������, ������� ���������������.
	5)���� ������� � �������� ������ �� ��������, �� ���������� �� ������, ������� ���������������.
	6)�������� ���� � ������� ������ ����������� ��������� "2".
	7)� ����������� ������ ��������� � ������� ������ ���������� �������.
	8)�������� ����� � �������� ��������� � ������� ������ ������������ � ��������������� ������� ���������� ������.
*/
void read_human_move(Tree_node* PNode) {
	int start_string = 0, start_column = 0, finish_string = 0, finish_column = 0;
	cout << "\u001B[37m������� ������ ��������� ������ : ";
	cin >> start_string;
	cout << "������� ������� ��������� ������ : ";
	cin >> start_column;
	if (start_column < 10 && start_column >= 0 && start_string < 10 && start_string >= 0) {
		if (PNode->field[start_string][start_column] == 2) {
			cout << "������� ������ ������� ������ : ";
			cin >> finish_string;
			cout << "������� ������� ������� ������ : ";
			cin >> finish_column;
			if (finish_column < 10 && finish_column >= 0 && finish_string < 10 && finish_string >= 0) {
				if (PNode->field[finish_string][finish_column] != 1) {
					if (abs(start_string - finish_string) == 1 && start_column == finish_column
						|| abs(start_column - finish_column) == 1 && start_string == finish_string) {
						PNode->field[finish_string][finish_column] = 2;
						PNode->count_connections[start_string][start_column]++;
						PNode->count_connections[finish_string][finish_column]++;
						int i = 0;
						while (PNode->connections[start_string][start_column][i] != -1) { i++; }
						PNode->connections[start_string][start_column][i] = finish_string * 10 + finish_column;
						i = 0;
						while (PNode->connections[finish_string][finish_column][i] != -1) { i++; }
						PNode->connections[finish_string][finish_column][i] = start_string * 10 + start_column;
						is_square(PNode, start_string, start_column, finish_string, finish_column);
					}
					else {
						cout << "\u001B[31m\t��� ������ ������ ���������\n"
							<< "\t�� ��������� ������ �� ��� �� �������\n\n";
						read_human_move(PNode);
					}
				}
				else {
					cout << "\u001B[31m\t��� ������ ������ ���������\n"
						<< "\t��� ����������� ���������\n\n";
					read_human_move(PNode);
				}
			}
			else {
				cout << "\u001B[31m\t������� ������ ��� ����������� ���������\n"
					<< "\t������� ������ � ������� ������ ������ � ��������� �� 0 �� 9\n\n";
				read_human_move(PNode);
			}
		}
		else {
			cout << "\u001B[31m\t��� ������ �� ����������� ���\n\n";
			read_human_move(PNode);
		}
	}
	else {
		cout << "\u001B[31m\t��������� ������ ��� ����������� ���������\n"
			<< "\t������� ������ � ������� ������ ������ � ��������� �� 0 �� 9\n\n";
		read_human_move(PNode);
	}
}
/*������� ����
���������:
	1)��������� �� ���� ������
������� ������:
	1)������� ����������� ���� ���� �� ��������
	2)i- ���������� ����, ��� ��������� ������ �������
	3)���� ����������� ��� ������ �������,�� �������  ��������������� �������
	4)������� ���� ����
	4)��������� ��� ��������
	5)���� �� ������ ������� - ��������� ������ 4)-5)
	6)������ ������ ��������� �����
	7)���������� �������� �����-����� ���������
	8)�������� ������ ���
	9)���� ��� ������ �������- ��������� ������ 6)-9)
*/
Tree_node* game(Tree_node* root) {
	int i = 0;
	while (game_is_over(root) == false) {
		system("cls");
		if (i > 0) {
			cout << "\u001B[35m��������� ������ ������� \n";
			i = 0;
		}
		Print_field(root);
		read_human_move(root);
		while (root->is_square == true) {
			system("cls");
			Print_field(root);
			cout << "\u001B[35m�� ������� �������\n";
			root->is_square = false;
			read_human_move(root);
		}
		make_tree(root);
		alpha_betta(root);
		choose_best_move(root);
		while (root->is_square == true) {
			root = re_create_root(root);
			root->is_square = false;
			make_tree(root);
			alpha_betta(root);
			choose_best_move(root);
			i++;
		}
		root = re_create_root(root);
	}
	return root;
}
/*������� ������ ���������� ���� 
���������:
	1)��������� �� ������ ������
������� ������:
	1)������� ������ ������ � ����������
	2)����� ����������
*/
void get_result(Tree_node* root) {
	int score_c = 0, score_h = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (root->field[i][j] == 1) { score_c++; }
			if (root->field[i][j] == 2) { score_h++; }
		}
	}
	if (score_h > score_c) { cout << "\u001B[36m\t�� �������! ��� ���� " << score_h << " ���� ���������� " << score_c << "\n"; }
	if (score_h < score_c) { cout << "\u001B[36m\t�� ���������( ��� ���� " << score_h << " ���� ���������� " << score_c << "\n"; }
	if (score_h == score_c) { cout << "\u001B[36\tm�����! ��� ���� " << score_h << " ���� ���������� " << score_c << "\n"; }
}
int main() {
	setlocale(LC_ALL, "ru");     		//��������� �������� �����
	cout << "\u001B[36\tm�����!";
	int field[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			field[i][j] = 0;
		}
	}
	field[9][0] = 1;
	field[0][9] = 2;
	Tree_node* root;
	root = creat_root(field);
	root = game(root);
	Print_field(root);
	system("cls");
	get_result(root);
	return 0;
}