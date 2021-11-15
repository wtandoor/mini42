// #include "minishell.h"


// int pwd(void)
// {
// 	char cwd[PATH];

// 	if (getcwd(cwd, PATH))
// 	{
// 		ft_putendl_fd(cwd, 1);
// 		return (1);
// 	}
// 	else 
// 		return (0);
// } 

// t_sig g_sig;


// void    sigint(int code)
// {
// 	if (g_sig.pid == 0)
// 	{
// 		ft_putchar_fd("w", 2);
// 		g_sig.exit_status = 1;
// 	}
// 	else
// 	{
// 		ft_putchar_fd("\n", 2);
// 		g_sig.exit_status = 130;
// 	}

// }

// void    signal(t_mini **mini)
// {
// 	signals(SIGINT, &sigint);
// }
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main()
{
	// int pid = fork();
	// if (pid == -1) 
	// 	return 1;
	// if (pid == 0)
	// {
	// 	while (1)
	// 	{
	// 		printf("Some text\n");
	// 		usleep(50000);
	// 	}
	// }
	// else{
	// 	sleep(1);
	// 	kill(pid, );
	// 	// wait((int*)14);
	// 	printf("hi\n" );
	// }
		
	int id = fork();
	if (id != 0)
		fork();

	// pwd();
	printf("%s :%d\n", "done", id);
	return 0;
}