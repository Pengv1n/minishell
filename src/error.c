#include "minishell.h"

void	error(int n, char *str)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_return_code = errno;
	}
	else if (n == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_return_code = 127;
		exit(127);
	}
	exit(EXIT_FAILURE);
}

void	error_with_std_function(int n)
{
	if (n >= 1 && n <= 15)
		ft_putstr_fd("error with malloc\n", 2);
	if (n == 20)
		ft_putstr_fd("Error: can't create a pipe\n", 2);
	if (n == 21)
		ft_putstr_fd("Can't make a fork\n", 2);
	exit (n);
}