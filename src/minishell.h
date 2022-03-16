#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "signal.h"
#include "readline/readline.h"
#include "readline/history.h"

int	g_return_code;

typedef struct s_msh
{
	char	*pwd;
	char	*old_pwd;
} t_msh;

typedef struct s_env
{
    char    *data;
    struct s_env   *next;
} t_env;

t_env	*crt_env(char **env);
void	add_back_env(t_env **env, t_env *new);
t_env	*lst_end(t_env *env);
t_env	*new_env(char *data);
void	sig_msh(void);
void	parse_command(char *cmd, t_msh *msh, t_env *env);
void	check_if_path_not_expand(t_list *cmd_data, t_env *env);

#endif
