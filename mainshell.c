#include "header.h"

void _putchar(const char* character)
{
	write(1, &character, strlen(character));
}

void showprom(void)
{
	_putchar("ShaBen Shell# ");
}

void executer(const char *com)
{
	char* command = strdup(com); 
	pid_t c_process = fork();

	if (c_process == -1) 
	{
		perror("error during fork");
		exit(EXIT_FAILURE);
	}
	if (c_process == 0)
	{
		int n = 0;
		char* delim = " ";
		char* tokens[100];
		tokens[n] = strtok(command, delim);
		
		while(tokens[n])
		{
			n++;
			tokens[n] = strtok(NULL, delim);
		}
		tokens[n] = NULL;
		execve("ls", tokens, NULL);
		perror("at execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

void readcom(char *com, size_t size)
{
	if (fgets(com, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			_putchar("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			_putchar("Error\n");
			exit(EXIT_FAILURE);
		}
	}
	com[strcspn(com, "\n")] = '\0'; 
}

int main(void)
{
	
	char com[200];
	
	while (1)
	{
		showprom();
		readcom(com, sizeof(com));
		executer(com);
	}


	return 0;
}
