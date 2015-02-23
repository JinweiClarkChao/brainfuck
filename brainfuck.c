#include <stdio.h>
#include <string.h>

#define MAX_DATA 30000

typedef struct brainfuck{
	char data[MAX_DATA];
	char command[MAX_DATA];
	char *ptr;
	int count;
	int num;
}bf;

bf one;

void init()
{
	char c;
	memset(&one, 0, sizeof(one));
	one.count = 0;
	one.num = 0;
	one.ptr = one.data;

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
			break;
		one.command[++one.count] = c;
	}
	one.num = one.count;
	one.command[one.count] = '\0';
}

void run()
{
	char c;
	int i;
	int left;
	int right;

	one.count = 0;
	while (c = one.command[++one.count])
	{
		switch (c)
		{
		case '+':
			if (*one.ptr == 255)
				*one.ptr = 0;
			else
				++*one.ptr;
			break;
		case '-':
			if (*one.ptr == 0)
				*one.ptr = 255;
			else
				--*one.ptr;
			break;
		case '>':
			++one.ptr;
			break;
		case '<':
			--one.ptr;
			break;
		case ',':
			*one.ptr = getchar();
			break;
		case '.':
			putchar(*one.ptr);
			break;
		case '[':
			left = 0;
			if (*one.ptr != 0)
				break;
			else
			{
				for (i = one.count + 1; i <= one.num; i++)
				{
					if (one.command[i] == '[')
						++left;
					else if (one.command[i] == ']')
					{
						if (left == 0)
						{
							one.count = i;
							break;
						}
						else
							--left;
					}
					
				}
			}
			break;
		case ']':
			right = 0;
			if (*one.ptr == 0)
				break;
			else
			{
				for (i = one.count - 1; i >= 1; i--)
				{
					if (one.command[i] == ']')
						++right;
					else if (one.command[i] == '[')
					{
						if (right == 0)
						{
							one.count = i;
							break;
						}
						else
							--right;
					}
				}
			}
			break;
		}
	}
}

int main(int argc, char **argv)
{
	printf("Input the brainfuck expression below\n");
	init();
	run();
	return 0;
}
