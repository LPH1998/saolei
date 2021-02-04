#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//��ӡ�к�
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * '0';
}

void JudgeAround(char mine[ROWS][COLS],char show[ROWS][COLS],int x,int y)
{
	int i = 0;
	int j = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (show[i][j] != ' '&&i != 0 && i != ROWS - 1 && y != 0 && y != COLS - 1)
			{
				int count=get_mine_count(mine, i, j);
				show[i][j] = count + '0';
				if (show[i][j] == '0')
				{
					show[i][j] = ' ';
					JudgeAround(mine,show, i, j);
				}
			}
		}
	}
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win<row*col-EASY_COUNT)
	{
		printf("�����벻���׵����꣺>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row&&y >= 1 && y <= col)
		{
			//����Ϸ�
			//1.����
			if (mine[x][y] == '1')
			{
				printf("���ź�������ը���ˣ�\n");
				DisplayBoard(mine, row, col);
				break;
			}
			else//������
			{
				//����x,y������Χ�м�����
				int count=get_mine_count(mine,x,y);
				show[x][y] = count + '0';
				if (show[x][y] == '0')
				{
					show[x][y] = ' ';
					JudgeAround(mine, show, x, y);
				}
				DisplayBoard(show, row, col);
				win++;
			}
		}
		else
		{
			printf("��������Ƿ������������룡");
		}
	}
	if (win == row*col - EASY_COUNT)
	{
		printf("��ϲ�㣬���׳ɹ���\n");
		DisplayBoard(mine, row, col);
	}
}

//�ݹ����ʹ�����׵ĵط�ȫ��չ��