#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "signal.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "fcntl.h"
#include "sys/wait.h"
#include "string.h"
#include "errno.h"

int	g_return_code;

typedef struct s_cmd
{
    char    **cmd;
    int in;
    int out;
    char    *hr_name;
    int num;
    int err;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_msh
{
	char	*pwd;
	char	*old_pwd;
    int amount;
} t_msh;

typedef struct s_env
{
    char    *data;
    struct s_env   *next;
} t_env;

typedef	struct s_pipe
{
	char	**com;
	char	**cmd;
	char	**path;
	int	**fds;
	int	*pids;
	int	size;
	int	hd;
}	t_pipe;

t_env	*crt_env(char **env);
void	add_back_env(t_env **env, t_env *new);
t_env	*lst_end(t_env *env);
int	size_env(t_env *env);
t_env	*new_env(char *data);
void	sig_msh(void);
void	parse_command(char *cmd, t_msh *msh, t_env **env);
void	check_if_path_not_expand(t_list *cmd_data, t_env *env);
int	check_path(int i, char *str);
int	check_path_data(t_list *cmd_data, int i, char *data, t_env *env);
char	*check_in_env(char *cmd, t_env *env);
void	clean_commands(t_list *cmd_data, t_env *env);
int	check_syntax_error(t_list *cmd_data);
int	check_repited_redirect(t_list *cmd_data);
int	init_cmd_struct(t_list *cmd_data, t_cmd **s, t_msh *msh);
void	fill_list_cmd_struct(t_list *cmd_data, t_cmd *s);
void	signal_for_heredoc(void);
void	ignore_signals(void);
void	heredoc(t_list *cmd_data, t_cmd *s);
void	clear_list_cmd_struct(t_cmd **s);
int	data_is_pipe(t_list *cmd_data);
t_list	*error_ambitious_data(t_list *cmd_data, t_cmd *s);
void	made_redirect(t_list *cmd_data, t_cmd *s);
int	data_redirect_in(t_list *cmd_data);
int	data_redirect_out(t_list *cmd_data);
t_list	*error_with_redirect(t_list *cmd_data, t_cmd *s);
int	check_if_not_last_redirect_in(t_list *cmd_data);
int	check_if_not_last_redirect_out(t_list *cmd_data);
void	pipex(t_cmd *s, t_msh *msh, t_env *env);
int	ft_strchr_len(const char *s, int c);
t_env	*find_env_data(t_env *env, char *data);
void	made_new_minishell(t_env *env);
void	error(int n, char *str);
void	close_inout(t_cmd *s);
int	check_if_build_in_or_null(t_env **env, t_cmd *s, t_msh *msh, int flag);
char	**build_envp(t_env *env);
void	child_signals(void);
void	if_no_first_command(t_cmd *s);
void	free_double_massive(char **data);
char	*add_dir(t_pipe *descriptor, char **cmd, char **envp);
void	signal_for_main_with_fork(void);
void	error_with_std_function(int n);
void	count_pipes(t_pipe *pipex, t_msh *msh);
void	exit_minishell(void);
void	add_command_and_args(t_list *cmd_data, t_cmd *s);
int	data_redirect_and_heredoc(t_list *cmd_data);
void	add_command_and_args(t_list *cmd_data, t_cmd *s);
void	close_fd(int **fds);
void	choose_build_in_function(t_env **env, t_cmd *s, t_msh *msh, int flag);
void	child_process(t_pipe *pipex, t_cmd *s, t_msh *msh, t_env **env);
void	echo_build_in(t_cmd *s);
void	pwd_build_in(t_cmd *s, t_msh *msh);
void	env_build_in(t_env *env, t_cmd *s);
void	change_data_in_list(t_env *env, char *data);
void	export_build_in(t_env **env, t_cmd *s);
int	check_if_str_num(char *data);
void	exit_build_in(t_cmd *s);
int	check_for_error_data(char *data, char c);
static t_env	*copy_env(t_env *env);
void	unset_build_in(t_cmd *s, t_env **env);
void	cd_build_in(char **cmd, t_env *env, char *pwd);
char	*get_address(void);
void	change_env_pwds(t_msh *msh, t_env *env);

#endif
