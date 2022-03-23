#include "minishell.h"

int	data_dollar_question(t_list *cmd_data, int i, char *data)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;
	int	len;

	tmp1 = ft_substr(data, 0 , i - 1);
	ret = ft_itoa(g_return_code);
	len = ft_strlen(ret);
	tmp2 = ft_strjoin(tmp1, ret);
	free(tmp1);
	free(ret);
	tmp1 = ft_strdup(data + i + 1);
	free(cmd_data->content);
	cmd_data->content = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	return (i + len - 1);
}

int	data_dollar_num(t_list *cmd_data, int i, char *data)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(data, 0, i - 1);
	tmp2 = ft_strdup(data + i + 1);
	free(cmd_data->content);
	cmd_data->content = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (i);
}

char	*check_in_env(char *var, t_env *env)
{
	int	len;
	char	*new;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(var, env->data, len) && env->data[len] == '=')
		{
			new = ft_memchr(env->data, '=', ft_strlen(env->data));
			new++;
			return (ft_strdup(new));
		}
		env = env->next;
	}
	return (NULL);
}

int	data_change_path(t_list *cmd_data, int i, char *data, t_env *env)
{
	int	j;
	char	*tmp1;
	char	*tmp2;
	char	*new;
	int	len;

	j = i;
	i = check_path(i, data);
	if (j == i)
		return (i);
	tmp1 = ft_substr(data, j, i - j);
	new = check_in_env(tmp1, env);
	free(tmp1);
	tmp1 = ft_substr(data, 0, j - 1);
	len = ft_strlen(new);
	tmp2 = ft_strjoin(tmp1, new);
	if (new)
		free(new);
	free(tmp1);
    tmp1 = ft_strdup(data + i);
	free(cmd_data->content);
	cmd_data->content = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	return (j + len - 1);

}

int	check_path_data(t_list *cmd_data, int i, char *data, t_env *env)
{
	if (cmd_data->flag_not_change_dollars == 1)
		return (check_path(i ,data));
	if (data[i] == '?')
	{
		i = data_dollar_question(cmd_data, i--, data);
		return (i);
	}
	if (data[i] && ft_isdigit(data[i]))
	{
		i = data_dollar_num(cmd_data, i--, data);
		return (i);
	}
	if (data[i] && (ft_isalnum(data[i]) || data[i] == '_'))
		i = data_change_path(cmd_data, i, data, env);
	return (i);
}