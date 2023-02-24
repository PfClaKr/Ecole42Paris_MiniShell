/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:36:25 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 22:2 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

# define ERROR -1
# define SUCCESS 0

# define T_END 10
# define T_NULL 0
# define T_WORD 1
# define T_SPACE 4242
# define ARG 1
# define T_WORD_NULL 11
# define T_PIPE 2
# define INFILE_CHAR 30 // <
# define OUTFILE_CHAR 31 // >
# define HEREDOC_CHAR 32 // <<
# define OUTFILEOVER_CHAR 33 // >>
# define INFILE 40 // le mot apres <
# define OUTFILE 41 // le mot apres >
# define LIMITOR 42 // le mot apres <<
# define OUTFILEOVER 43 // le mot apres >>
# define T_SINGLE_QUOTES 5
# define T_DOUBLE_QUOTES 6

# define ERR_SYNTAX -200
# define ERR_SYNTAX_PIPE -201
# define ERR_SYNTAX_NEWLINE -202
# define ERR_AMBIGUOUS -203
# define HEREDOC_ERROR 999

typedef struct s_cmd_line	t_cmd_line;
typedef struct s_token		t_token;
typedef struct s_global
{
	int		ret;
	int		child;
	pid_t	pid;
}					t_global;

struct s_token
{
	char	*word;
	int		type;
	char	*origin;
	int		flag_quotes;
	int		flag_env;
	int		flag_null;
	int		tail;
	t_token	*next;
};

typedef struct s_token_list
{
	struct s_token	*head;
	struct s_token	*tail;
	int				count;
}	t_token_list;

struct s_cmd_line
{	
	pid_t			tmp;
	t_cmd_line		*begin;
	struct s_token	*token;
	t_cmd_line		*next;
	int				token_count;
	int				infile;
	int				outfile;
	char			**cmd_args;
	int				fd;
};

typedef struct s_exec
{
	char	**cmd_paths;
	char	*cmd;
	int		pipe_nb;
	pid_t	pid;
	int		*pipe;
	int		id;
	int		flag;
	int		flag_quotes;
	char	**envp;
}	t_exec;

typedef struct s_env
{
	char	*origin;
	char	*key;
	char	*value;
}	t_env;

typedef struct s_env_list
{
	struct s_env		*content;
	struct s_env_list	*next;
}	t_env_list;

extern struct s_global		g_global;
/*****************Env********************/
void			init_env_signal(char **env, t_env_list **env_list);
int				init_env(char *origin, char **key, char **value);
void			signal_handler(int signo);
char			*find_value_by_key(t_env_list *env_list,
					char *key, t_token *token);
t_env			*find_env_by_key(t_env_list *env_list, char *key);
void			get_new_env(t_env_list *env, char *key, char *value);
void			set_new_env(t_env_list *env_list, char *key, char *value);
void			ft_lstadd_back(t_env_list **new_env_list,
					t_env_list *tmp_env_list);
t_env_list		*ft_lstnew(t_env *new_env);
t_env			*ft_new_env(void);
int				ft_lstsize(t_env_list *list);
void			ft_error(char *str, int type);
int				ft_strcmp(const char *s1, const char *s2);
void			get_new_env_value(t_env *env, char *key, char *value);
void			get_new_dollar(t_token *token,
					int head_dollar, t_env_list *env);
int				check_count_dollar(char *word);
t_token			*re_get_token_list(t_token *token, char *word);
void			ft_free_all_env(t_env_list **env_list);
void			update_env_value(t_env_list **env, char *key, char *value);
void			skip_heredoc_token(t_token **tmp);

/*****************Token********************/
int				check_quotes_incmd(char *cmd);
int				find_quote_end(char *cmd, int i);
int				is_which_quote(char cmd);
int				find_quote_return(int type);
int				find_quote(char *cmd, int i, int type);
int				handle_syntax_error(t_token *err, t_token *next,
					t_token *prev, int status);
void			con_error_status(t_token_list *token_list, int status,
					int status_heredoc);
void			con_error_status2(int status);
void			con_error_status3(t_token_list *tokens, int status);
int				get_token_list(char *cmd_origin, t_env_list *env,
					t_token_list *token_list);
void			set_type_red_word(t_token *token);
void			cmd_tokenizer(char *cmd, t_token_list *token_list);
void			cmd_tokenizer_pipe(char *cmd, t_token *token, int *idx);
void			cmd_tokenizer_redirection(char *cmd, t_token *token, int *idx);
void			cmd_tokenizer_double_quotes(char *cmd, t_token *token,
					int *idx);
void			cmd_tokenizer_single_quotes(char *cmd, t_token *token,
					int *idx);
void			cmd_tokenizer_space(char *cmd, t_token *token, int *idx);
void			cmd_tokenizer_word(char *cmd, t_token *token, int *idx);
void			check_env_token(t_token_list *token_list,
					t_env_list *env, int count_dollar);
char			*get_new_word(t_token *token, t_env_list *env, int head,
					int tail);
char			*ft_strjoin_word(char *word, char *value, char *head,
					char *tail);
int				find_tail_dollar(char *word, int i);
int				check_token_have_env(char *word);
int				syntax_check(t_token *head);
void			syntax_error_heredoc(t_token_list *tokens);
int				is_which_quote(char cmd);
int				find_quote_return(int type);
void			ft_free_token_list2(t_token_list *tokens);
t_token			*ft_new_token(void);
void			ft_token_add_back(t_token **head, t_token *token2);
void			ft_token_free(t_token *token);
void			ft_token_remove_next(t_token *token);
void			ft_token_add_middle(t_token *start_token);
int				ft_is_space(char *cmd);
void			ft_merge_word_origin(t_token *curr, int status);
int				ft_isnot_sep(t_token **curr);
void			ft_token_merge(t_token **curr);
void			remove_space_token(t_token *head);
/*****************Cmd_line********************/
t_cmd_line		*init_cmd_line(t_cmd_line *cmd_line_origin,
					t_token_list *tokens);
int				count_token_before_pipe(t_token *token);
t_cmd_line		*new_cmd_line(void);
void			ft_free_cmd_line(t_cmd_line *cmd_line);
void			ft_cmd_add_back(t_cmd_line **head, t_cmd_line *cmd);
void			copy_cmd_line(t_cmd_line *t_cmd, t_token **head);

/*****************Exec********************/
int				exec(t_cmd_line *cmd_line, t_env_list **env);
void			parent_free(t_exec *exec, t_cmd_line *line);
void			parent_free2(t_cmd_line *tmp);
void			msg_error(char *str);
void			close_pipes(t_exec *exec, t_cmd_line *cmd_line);
void			child(t_exec exec, t_cmd_line *cmd_line, t_env_list **env);
int				create_pipes(t_exec *exec, t_cmd_line *cmd_line);
int				count_pipes(t_cmd_line *cmd_line);
void			here_doc(char *argv, t_token *token,
					t_cmd_line *cmd_line, t_env_list **env);
void			infile(char *word, t_cmd_line *cmd_line, t_exec *exec,
					t_env_list *env);
void			outfile(char *word, t_cmd_line *cmd_line, t_exec *exec,
					t_env_list *env);
void			outfileover(char *word, t_cmd_line *cmd_line, t_exec *exec,
					t_env_list *env);
void			get_files(t_exec *exec, t_cmd_line *cmd_line, t_env_list *env);
void			check_if_builtin(t_exec *exec, t_cmd_line *line,
					t_env_list **envp);
void			sub_dup(t_exec *exec, t_cmd_line *cmd_line);
void			last_cmd_dup(t_exec *exec, t_cmd_line *cmd_line);
char			**create_envp_char(t_env_list *env);
int				check_is_absolute_path(t_exec *exec, t_cmd_line *line,
					t_env_list **env);
int				get_flag(t_cmd_line *cmd_line);
void			put_right_message(t_exec *exec, t_cmd_line *cmd_line,
					t_env_list **env);
void			exec_exit_free_all(int ret, t_exec *exec, t_cmd_line *line,
					t_env_list **env);
void			set_ret(int status);
char			**get_args_incmd(t_cmd_line *cmd_line);
char			*get_path(t_env_list *env);
int				exec_helper(t_exec *exec, t_cmd_line *cmd_line,
					t_env_list **env_list);
void			isdir(t_exec *exec, t_cmd_line *line, t_env_list **env);
char			*check_when_no_paths(t_exec *exec, t_cmd_line *line,
					t_env_list **env);
void			waiter(t_exec *exec, t_cmd_line *tmp);
int				exec_heredoc(t_cmd_line *cmd_line_origin,
					t_env_list **env_list);
void			exec_heredoc2(t_cmd_line *cmd_line, int *i,
					t_env_list **env, int *j);
void			get_random_heredoc(t_token *token, int j);
void			heredoc_handler(int signo);
void			unlink_heredoc_file(t_cmd_line *cmd);
void			heredoc_exit_free_all(char *argv,
					t_cmd_line *cmd_line, t_env_list **env);
void			heredoc_check_ret(void);

/*****************Builtin********************/

int				cd(char **cmd, t_env_list **env);
int				echo(char **cmd);
int				env(char **cmd, t_env_list *env_list, int flag);
int				export(char **cmd, t_env_list *env_list);
void			seperate_env_argv(char *argv, char **key, char **value);
char			*ft_substr_env(char const *s, unsigned int start, int len);
int				exit_cmd(char **cmd);
int				pwd(char **cmd);
int				unset(char **cmd, t_env_list **env_list);

#endif
