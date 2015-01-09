#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 30000

typedef struct brainfuck{
	char data[MAX_DATA];
	char command[MAX_DATA];
	char *ptr;
	int count;
}bf;

bf one;

void init()
{
	char c;
	memset(&one, 0, sizeof(one));
	one.count = 0;
	one.ptr = one.data;
	
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
			break;
		else
		{
			one.command[++one.count] = c;
		}
	}
	one.command[0] = one.count;
	one.command[one.count] = '\0';
}

void run()
{
	char c;
	int i;

	one.count = 0;
	while (c = one.command[++one.count])
	{
		switch (c)
		{
		case '+':
			(*one.ptr)++;
			break;
		case '-':
			(*one.ptr)--;
			break;
		case '>':
			one.ptr++;
			break;
		case '<':
			one.ptr--;
			break;
		case ',':
			*one.ptr = getchar();
			break;
		case '.':
			putchar(*one.ptr);
			break;
		case '[':
			if (*one.ptr != 0)
				break;
			else
			{
				for (i = one.count + 1; i <= one.command[0]; i++)
				{
					if (one.command[i] == ']')
					{
						one.count = i;
						break;
					}
				}
			}
			break;
		case ']':
			if (*one.ptr == 0)
				break;
			else
			{
				for (i = one.count - 1; i >= 1; i--)
				{
					if (one.command[i] == '[')
					{
						one.count = i;
						break;
					}
				}
			}
			break;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	init();
	run();
	return 0;
}