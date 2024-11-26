//Designed by Comardom 2024.11.23
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define DIM_SIZE 1//每个维度的长
#define LONG_LONG_ERROR LLONG_MIN
#define LONG_LONG_NULL (LLONG_MIN+1)
#define STOP (LLONG_MIN+2)
void store_integer_on_3D_coordinates(void);
long long int ll_input_restrictions(bool if_negative_is_allowed);
void array_handle_main(int *part, bool part_is_been_typed, bool part_is_demical);
void data_out(int *integer, int *decimal);
void multi_dimensional_array_handling(int *out, const int *in,int n, int dimension);
void array_out(const int *out,const int n,const int dimension);
void assign_initial_value(int *part, int n, int dimension);

int main(void)
{

	store_integer_on_3D_coordinates();
	return 0;
}

void store_integer_on_3D_coordinates(void)
{

	int integer_part[DIM_SIZE][DIM_SIZE][DIM_SIZE];
	int decimal_part[DIM_SIZE][DIM_SIZE][DIM_SIZE];
	assign_initial_value(integer_part,DIM_SIZE,3);
	assign_initial_value(decimal_part,DIM_SIZE,3);
	long long int temp_choice_for_overflow_checking;
	bool integer_part_is_been_typed = false;
	bool decimal_part_is_been_typed = false;
	while (1)
	{
		printf("Plz choose the part that you wanna input.\n");
		printf("If you wanna input a negative number,"
			" enter a \"-\" before or after or between the number you entered, "
			"and try to enter it first, of course.\n"
			"But do not input \"-\" when you are typing the decimal part.\n"
			"WARNING: DO NOT TYPE MORE TEXT THAN EXPECTED!!!!!!\n");
		printf("And you should input a \".\" to SAVE and press Enter to CONTINUE.\n"
		 "If you wanna stop your typing, please input a \"~\".\n");
		printf("1. Enter integer\n");
		printf("2. Enter decimal\n");
		printf("3. Read your data\n");
		printf("4. Exit\n");
		temp_choice_for_overflow_checking=ll_input_restrictions(true);
		// printf("%lld\n", temp_choice_for_overflow_checking);
		if(temp_choice_for_overflow_checking >= SHRT_MAX)
		{
			//将数据限定在short，保险
			printf("Overflow! (here is short int data, not long long)\n");
			continue;
		}
		else//甭管有没有用，写else就是规整一些
		{
			switch (temp_choice_for_overflow_checking)
			{
				case 1:
				{
					printf("Now input the integer part.\n");
					array_handle_main(integer_part, integer_part_is_been_typed,false);
					integer_part_is_been_typed = true;
					break;
				}
				case 2:
				{
					printf("Now input the decimal part.\n");
					array_handle_main(decimal_part, decimal_part_is_been_typed,true);
					decimal_part_is_been_typed = true;
					break;
				}
				case 3:
				{
					printf("\n");
					data_out(integer_part,decimal_part);
					break;
				}
				case 4:
				{
					exit(0);
				}
				default:
				{
					printf("Invalid Choice.\n");
					printf("Plz Try Again.\n");
					break;
				}
			}//选择结束
			getchar();
			getchar();
		}//else结束
	}//循环结束
}

void array_handle_main(int *part, bool part_is_been_typed , bool part_is_demical)
{
	int arr[DIM_SIZE][DIM_SIZE][DIM_SIZE];
	assign_initial_value(arr,DIM_SIZE,3);
	long long int temp_for_overflow_checking = -1;
	// bool input_provided = false; // 标记是否有有效输入

	printf("Plz enter your int data, and enter \".\" to SAVE and press Enter to CONTINUE.\n");
	printf("If you enter something that's not an integer, ");
	printf("the program will automatically filter it out, don't worry.\n");
	/*输入整数，输入~完成此次输入，如果你输入了别的东西，程序会自动过滤，别担心 */
	for(int i=0;i<DIM_SIZE;i++)
	{
		for(int j=0;j<DIM_SIZE;j++)
		{
			for(int k=0;k<DIM_SIZE;k++)//三层循环是为了解决数组输入
			{
				//这个地方要循环很多次，不要把变量声明放进这里，损失性能的
				temp_for_overflow_checking = part_is_demical ? ll_input_restrictions(false) : ll_input_restrictions(true);
				//这里使用对数据进行预处理的函数，就不用管油炸糕了
				if(temp_for_overflow_checking >= INT_MAX || temp_for_overflow_checking == LONG_LONG_ERROR)
				{
					//将数据限定在int，保险
					printf("Overflow! (here is int data, not long long)\n");
					continue;
				}
				else if(temp_for_overflow_checking == STOP)
				{
					printf("You have stopped it.\n");
					goto break_the_input;//三层循环刚结束就是这个goto语句
				}
				else if(part_is_been_typed && temp_for_overflow_checking==LONG_LONG_NULL)
				{
					arr[i][j][k] = *(part + i * DIM_SIZE * DIM_SIZE + j * DIM_SIZE + k);
					//这里是在保留原来的数据
				}
				else
				{
					if(*(part + i * DIM_SIZE * DIM_SIZE + j * DIM_SIZE + k)==0)
					{
						arr[i][j][k] = 0;
					}
					else
					{
						arr[i][j][k]=temp_for_overflow_checking;
					//不用管数据类型转换，已经保证没问题了
					}
				}
			}
		}
	}//三层嵌套循环输入结束
	break_the_input:;//goto语句，在三层循环内调用，因为不想一直break
	multi_dimensional_array_handling(part,arr,DIM_SIZE,3);//传递了每维度长度和维度
	array_out(part,DIM_SIZE,3);//输出
}

void multi_dimensional_array_handling(int *out, const int *in,int n, int dimension)
{
	int num_pow=(int)pow(n,dimension);//计算数据量
	for(int i=0;i<num_pow;i++)
	{
		*(out+i)=*(in+i);
	}
}

long long int ll_input_restrictions(bool if_negative_is_allowed)
{
	char integer;
	long long int sum;
	bool there_was_a_value_just_now = false;
	bool is_negative = false;
	integer = 0;
	sum = 0;
	while(1)
	{
		//这里的顺序千万不要随便改！！！
		scanf("%c",&integer);
		if(integer == '~')
		{
			return STOP;
			break;
		}
		if(integer == EOF)
		{
			return LONG_LONG_ERROR;
		}
		if(integer == '-' && if_negative_is_allowed)
		{
			is_negative = true;
			continue;
		}
		if (integer == '.' && there_was_a_value_just_now)
		{
			break;  // 遇到 '.' 退出循环
		}
		else if(integer == '.' && !there_was_a_value_just_now)
		{
			return LONG_LONG_NULL;
		}
		there_was_a_value_just_now = false;
		if(integer>='0' && integer<='9')
		{
			if (sum > (LLONG_MAX / 10) || (sum == LLONG_MAX / 10 && (integer - '0') > (LLONG_MAX % 10)))
			{//此处检测溢出解释见函数末尾
				printf("Overflow!!\n");
				return LONG_LONG_ERROR;//直接结束函数并返回错误代码
			}
			else
			{
				there_was_a_value_just_now = true;
				sum = sum * 10 + (integer - '0');
				//每次输入数字将之前的数向前抬一位，把新数塞到个位
				if(is_negative)
				{
					sum = -sum;
				}
			}
		}
	}//此处循环结束
	return sum;
	/*
	 sum > (LLONG_MAX / 10)
	 ||
	 (sum == LLONG_MAX / 10 && (integer - '0') > (LLONG_MAX % 10))
	 1.检查整体倍数：
		sum > (LLONG_MAX / 10)
		这部分检查 sum 当前的值是否已经大到再乘以 10 就会超出 LLONG_MAX。
		如果 sum 已大于 LLONG_MAX / 10，那么再乘以 10 必定会导致溢出。
	2.检查最后一位数字：
		(sum == LLONG_MAX / 10 && (integer - '0') > (LLONG_MAX % 10))
		如果 sum 刚好等于 LLONG_MAX / 10，则需要进一步检查本次读取的数字是否会导致溢出。
	其中，
		integer - '0' 是当前输入的数字。
		LLONG_MAX % 10 是 LLONG_MAX 的最后一位数字。
		如果当前输入的数字比 LLONG_MAX 的最后一位数字大，那么把这个数字加到 sum * 10 后，
		结果将超过 LLONG_MAX，因此也会导致溢出。*/
}

void array_out(const int *out, const int n, const int dimension)
{
	printf("Now check your data.\n");
	printf("If you're not satisfied, you can re-enter it, "
		"which will overwrite the original data.\n");
	int num_pow=(int)pow(n,dimension);//计算数据量
	for(int i=0;i<num_pow;i++)
	{
		if((i)%DIM_SIZE==0)
		{
			printf("\n");
		}
		else
		{
			;//什么也不做
		}
		printf("%d  ",*(out+i));
	}
	printf("\n");
}

void data_out(int *integer, int *decimal)
{
	printf("Now here's your data.\n");
	int num_pow=(int)pow(DIM_SIZE,3);//计算数据量
	for(int i=0;i<num_pow;i++)
	{
		if((i)%DIM_SIZE==0)
		{
			printf("\n");
		}
		else
		{
			;//什么也不做
		}
		printf("%d",*(integer+i));
		printf(".");
		printf("%d     ",*(decimal+i));
	}
	// printf("\r    ");
	printf("\n");
}

void assign_initial_value(int *part, int n, int dimension)
{
	int num_pow=(int)pow(n,dimension);//计算数据量
	for(int i=0;i<num_pow;i++)
	{
		*(part+i) = 0;//赋初值
	}
}