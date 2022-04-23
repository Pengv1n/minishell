#include "minishell.h"

static void	do_chdir(char *str)
{
	int	fd;

	fd = 0;
	if (chdir((const char *)str) < 0)
	{
		fd = open(str, O_DIRECTORY);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);

		if (access(str, 0) < 0)
			ft_putendl_fd(": No such file or directory", 2);
		else if (fd < 0)
			ft_putendl_fd(": Permission denied", 2);
		if (fd > 0)
			close(fd);
		g_return_code = 1;
	}
}

char	*get_address(void)
{
	char	*buf;
	char	*copy;

	buf = malloc(sizeof(char) * 1000);
	copy = buf;
	if (!buf)
		error_with_std_function(9);
	buf = getcwd(buf, 1000);
	if (!buf)
	{
		free(copy);
		g_return_code = 2;
		return (NULL);
	}
	return (buf);
}

static void cd_back(char *pwd)
{
	char	*buf;
	char	*last;
	char	*prev;
	int	flag;

	flag = 0;
	buf = get_address();
	if (!buf && ++flag)
		buf = pwd;
	last = ft_strrchr(buf, '/');
	prev = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(last) + 1);
	if (!prev)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	do_chdir(prev);
	if (flag == 0)
		free(buf);
	free(prev);
}

void	cd_build_in(char **cmd, t_env *env, char *pwd)
{
	int	a;
	const char	str[] = "HOME=";
	char	*home;

	a = 0;
	while (cmd[a])
		a++;
	while (env && (ft_strncmp(str, env->data, ft_strlen(str)) != 0))
	{
		if (env->next)
			env = env->next;
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_return_code = 1;
			return ;
		}
	}
	home = env->data + ft_strlen(str);
	if (a == 1)
		do_chdir(home);
	else if (!ft_strncmp(cmd[1], "..", 3) && ft_strlen(cmd[1]) == 2)
		cd_back(pwd + 4);
	else
		do_chdir(cmd[1]);
}

void	change_env_pwds(t_msh *msh, t_env *env)
{
	char	*buf;
	t_env	*pwd;
	t_env	*oldpwd;

	buf = get_address();
	free(msh->old_pwd);
	msh->old_pwd = ft_strjoin("OLDPWD=", msh->pwd + 4);
	free(msh->pwd);
	msh->pwd = ft_strjoin("PWD=", buf);
	pwd = find_env_data(env, "PWD=");
	oldpwd = find_env_data(env, "OLDPWD=");
	free(oldpwd->data);
	if (!pwd)
		oldpwd->data = ft_strdup(msh->old_pwd);
	else
		oldpwd->data = ft_strjoin("OLDPWD=", pwd->data + 4);
	if (pwd)
	{
		free(pwd->data);
		pwd->data = ft_strdup(msh->pwd);
	}
	free(buf);
}