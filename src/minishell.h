#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"

typedef struct s_env
{
    char    *data;
    struct s_env   *next;
} t_env;

t_env	*crt_env(char **env);
void	add_back_env(t_env **env, t_env *new);
t_env	*lst_end(t_env *env);
t_env	*new_env(char *data);

#endif
