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
	int win = 0; //1이 되면 플레이어의 승리
	int input_buf; //사용자로부터 받는 입력 버퍼
	int chance;
	
	printf(" --------  숫자 야구 게임  -------- \n\n");
	printf("아무 키나 입력해주세요..\n");
	scanf(" %d", &input_buf);
	fflush(stdin);
	system("cls");

	printf(" -------- 난이도 선택 -------- \n\n");
	printf("자리 수 * 5회의 기회가 주어집니다. ");
	printf("몇 자리의 숫자로 게임을 진행할까요?? : ");
	scanf(" %d", &game_radix);
	system("cls");

	printf("%d 자릿 수 숫자 게임이 시작됩니다. \n", game_radix);
	printf("만점은 %d 점입니다. 도전해 보세요 ! \n", game_radix*game_radix*5);
	printf("선수들 입장 중...\n");
	Sleep(1500);
	system("cls");

	radix_num = (int)pow(10, game_radix) / 10; //10^최대 자리수
	rand_num_generate();
	is_valid_gen(com_num_converted, 0);

	for (int i = 5; i >= 1; i--)
	{
		printf("%d초 후에 게임이 시작됩니다 !", i);
		Sleep(1000);
		system("cls");
	}

	printf(">>>  게 임 시 작 !\n\n");
	printf("\n%d 이닝 게임 시작합니다. \n", inning);
	printf("이번 회차 숫자를 입력해주세요 : ");
	scanf("%d", &input_buf);
	while (0 > input_buf || input_buf > (radix_num*10))
	{
		printf("%d자리 수 숫자를 입력해주세요 ! \n", game_radix);
		scanf(" %d", &input_buf);
	}
	printf("투수 와인드 업...\n");
	inning++;

	radix_convert(input_buf, player_num, radix_num);

	while (!win)
	{
		printf("당신의 숫자 : %d, %d 스트-라이크, %d 보-올 기록!\n\n", input_buf, cnt_strike(player_num, com_num_converted), cnt_ball(player_num, com_num_converted));
		if (cnt_strike(player_num, com_num_converted) == game_radix)
		{
			printf("게임 종료 ! \n");
			win = 1;
		}
		else
		{
			printf("%d 이닝 게임 시작합니다. \n", inning);
			printf("이번 회차 숫자를 입력해주세요 : ");
			scanf("%d", &input_buf);
			while (0 > input_buf || input_buf > (radix_num*10))
			{
				printf("%d자리 수 숫자를 입력해주세요 ! \n", game_radix);
				scanf(" %d", &input_buf);
			}
			printf("투수 와인드 업...\n");
			radix_convert(input_buf, player_num, radix_num);
		}
		inning++;
	}
	printf("홈런 !! %d 이닝만에 게임이 끝납니다!! \n", inning - 2);
	printf("\n\n당신의 점수는 : %d 입니다! 게임 종료.\n\n", game_radix*(game_radix * 5 - inning));
	system("pause");
	return 0; 
}