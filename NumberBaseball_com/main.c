#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

int game_radix = 4;
int com_generated_num = 0;
int com_num_converted[4];
int player_num[4];
int radix_num = 10;

int cnt_strike(int* my_num, int* other_num)
{
	int cnt = 0;
	for (int i = 0; i < game_radix; i++)
	{
		if (my_num[i] == other_num[i])
		{
			cnt++;
		}
	}
	return cnt;
}

int cnt_ball(int* my_num, int* other_num)
{
	int cnt = 0;
	for (int i = 0; i < game_radix; i++)
	{
		if (my_num[i] != other_num[i])
		{
			for (int j = 1; j < game_radix; j++)
			{
				if (my_num[(i + j) % game_radix] == other_num[i])
				{
					cnt++;
				}
			}
		}
	}
	return cnt;
}

void radix_convert(int num, int* arr, int radix_stnum)
{
	for (int i = 0; i < game_radix; i++)
	{
		arr[i] = num / radix_stnum;
		num = num - radix_stnum * arr[i];
		radix_stnum = radix_stnum / 10;
	}
}

void rand_num_generate()
{
	int temp_generated;
	srand((unsigned)time(NULL));
	temp_generated = rand();
	com_generated_num = temp_generated % (int)(pow(10, game_radix));
	radix_convert(com_generated_num, com_num_converted, radix_num);
}

void is_valid_gen(int* arr, int valid_val)
{
	int i, j;
	while (!valid_val)
	{
		for (i = 0; i < game_radix; i++)
		{
			for (j = i + 1; j < game_radix; j++)
			{
				if (arr[i] == arr[j])
				{
					goto regen;
				}
			}
		}
		valid_val = 1;
		regen :
			rand_num_generate();
			is_valid_gen(arr, valid_val);
	}

}

int main()
{
	int rand_num = rand();
	int inning = 1;
	int win = 0; //1�� �Ǹ� �÷��̾��� �¸�
	int input_buf; //����ڷκ��� �޴� �Է� ����
	int chance;
	
	printf(" --------  ���� �߱� ����  -------- \n\n");
	printf("�ƹ� Ű�� �Է����ּ���..\n");
	scanf(" %d", &input_buf);
	fflush(stdin);
	system("cls");

	printf(" -------- ���̵� ���� -------- \n\n");
	printf("�ڸ� �� * 5ȸ�� ��ȸ�� �־����ϴ�. ");
	printf("�� �ڸ��� ���ڷ� ������ �����ұ��?? : ");
	scanf(" %d", &game_radix);
	system("cls");

	printf("%d �ڸ� �� ���� ������ ���۵˴ϴ�. \n", game_radix);
	printf("������ %d ���Դϴ�. ������ ������ ! \n", game_radix*game_radix*5);
	printf("������ ���� ��...\n");
	Sleep(1500);
	system("cls");

	radix_num = (int)pow(10, game_radix) / 10; //10^�ִ� �ڸ���
	rand_num_generate();
	is_valid_gen(com_num_converted, 0);

	for (int i = 5; i >= 1; i--)
	{
		printf("%d�� �Ŀ� ������ ���۵˴ϴ� !", i);
		Sleep(1000);
		system("cls");
	}

	printf(">>>  �� �� �� �� !\n\n");
	printf("\n%d �̴� ���� �����մϴ�. \n", inning);
	printf("�̹� ȸ�� ���ڸ� �Է����ּ��� : ");
	scanf("%d", &input_buf);
	while (0 > input_buf || input_buf > (radix_num*10))
	{
		printf("%d�ڸ� �� ���ڸ� �Է����ּ��� ! \n", game_radix);
		scanf(" %d", &input_buf);
	}
	printf("���� ���ε� ��...\n");
	inning++;

	radix_convert(input_buf, player_num, radix_num);

	while (!win)
	{
		printf("����� ���� : %d, %d ��Ʈ-����ũ, %d ��-�� ���!\n\n", input_buf, cnt_strike(player_num, com_num_converted), cnt_ball(player_num, com_num_converted));
		if (cnt_strike(player_num, com_num_converted) == game_radix)
		{
			printf("���� ���� ! \n");
			win = 1;
		}
		else
		{
			printf("%d �̴� ���� �����մϴ�. \n", inning);
			printf("�̹� ȸ�� ���ڸ� �Է����ּ��� : ");
			scanf("%d", &input_buf);
			while (0 > input_buf || input_buf > (radix_num*10))
			{
				printf("%d�ڸ� �� ���ڸ� �Է����ּ��� ! \n", game_radix);
				scanf(" %d", &input_buf);
			}
			printf("���� ���ε� ��...\n");
			radix_convert(input_buf, player_num, radix_num);
		}
		inning++;
	}
	printf("Ȩ�� !! %d �̴׸��� ������ �����ϴ�!! \n", inning - 2);
	printf("\n\n����� ������ : %d �Դϴ�! ���� ����.\n\n", game_radix*(game_radix * 5 - inning));
	system("pause");
	return 0; 
}