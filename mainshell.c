#include "header.h"

void _putchar(const char* character)
{
	write(1, character, strlen(character));
}

void showprom(void)
{
	_putchar("ShaBen Shell# ");
}

void executer(const char *com)
{
	char* command = strdup(com);
	char* prefix = "/bin/";
	int n = 0;
	char* delim = " ";
	char* tokens[100];
	int newlen;
	char* newcom = NULL;

	pid_t c_process = fork();

	if (c_process == -1) 
	{
		perror("error during fork");
		exit(EXIT_FAILURE);
	}
	if (c_process == 0)
	{
		tokens[n] = strtok(command, delim);
		newlen = strlen(prefix) + strlen(tokens[0]) + 1;
		while(tokens[n])
		{
			n++;
			tokens[n] = strtok(NULL, delim);
		}
		newcom = (char*)malloc(newlen * sizeof(char));
		if (newcom == NULL)
		{
			perror("Memory alloc fail");
			exit(EXIT_FAILURE);
		}
		strcpy(newcom, prefix);
		strcat(newcom, tokens[0]);
		tokens[0] = newcom;
		tokens[n] = NULL;
		execve(tokens[0], tokens, NULL);
		perror("at execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		if (newcom != NULL)
			free(newcom);
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
