/*
+ : Increments the value at the current cell by one.
- : Decrements the value at the current cell by one.
> : Moves the data pointer to the next cell (cell on the right).
< : Moves the data pointer to the previous cell (cell on the left).
. : Prints the ASCII value at the current cell (i.e. 65 = 'A').
, : Reads a single input character into the current cell.
[ : If the value at the current cell is zero, skips to the corresponding ] .
Otherwise, move to the next instruction.
] : If the value at the current cell is zero, move to the next instruction.
Otherwise, move backwards in the instructions to the corresponding [ .
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 30000

typedef struct brainfuck{
	char data[MAX_DATA];
	char command[MAX_DATA];
	char *ptr;
	int count;
	int pos;
}bf;

bf one;

void init()
{
	char c;
	memset(&one, 0, sizeof(one));
	one.pos = 0;
	one.count = 0;
	one.ptr = one.data;

	while (c = getchar())
	{
		if (c == '\n')
			break;
		else
		{
			one.command[++one.count] = c;
		}
	}
	one.command[one.count] = '\0';
}

void run()
{
	char c;
	int i;

	while (c = one.command[++one.pos])
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
				for (i = one.pos + 1; i <= one.count; i++)
				{
					if (one.command[i] == ']')
					{
						one.pos = i;
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
				for (i = one.pos - 1; i >= 1; i--)
				{
					if (one.command[i] == '[')
					{
						one.pos = i;
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