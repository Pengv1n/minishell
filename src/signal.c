#include "minishell.h"

void	handler_sig(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_return_code = 1;
}

void	sig_msh(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *)handler_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_for_heredoc(void)
{
	signal(SIGINT, (void *)handler_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}