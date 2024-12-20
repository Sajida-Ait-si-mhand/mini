#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include "get_next_line/get_next_line.h"

//--->Sajida: new header Declarations
# include "libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
}					t_env;

/// Sajida

typedef enum e_token_type
{
	WORD,
	PIPE,
	HER_DOC,
	OUT_REDIR,
	APPEND,
	INP_REDIR
}					token_type;

typedef struct s_token
{
	char			*data;
	token_type		data_type;
	struct s_token	*next_token;
	struct s_token	*prev_token;
	char			**envirement;    //Sojod
}					t_token;

typedef struct s_redir
{
	token_type		red_type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_node
{
	char			**cmd;
	t_redir			*redir;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}					t_node;

typedef struct s_minishell
{
	int				in_file;
	int				out_file;
	char			**envirement;
	char			*command;
	t_env			*envir;
	t_env			*export_env;
	t_token			*tokens;
	t_node			*nodes;
}					t_minishell;

extern t_minishell	g_minishell;

char				*get_word(char *str, int i);
char				*get_env_var(char *str, int i);
char				*fill_first_part(char *env_var, int *i);
char				*fill_middle_part(char *env_var, int *i);
char				*allocate_4_nword(char *str, char *env_var);
char				*ft_join_words(char *word, char *str, int l);
char				*remplace_doll_str(char *data, char *env_var);
char				*after_dol_word(char *str, int l, int str_len);
char				*rmp_dollar(char *tokens_word, t_token **tokens_list);
char				*rmp_dollar2(char *t_word, int *i, int to_split,
						t_token **tokens_list);
char				*token_edi_env(char *str, char *env_var,
						t_token **tokens_list);
int					is_space(char *line);
int					is_not_alpanum(char c);
int					cmd_count(t_token *tokens);
int					count_pipe(t_token *tokens);
int					check_4_space(char *env_var);
int					valid_word(char *str, int i);
int					count_dollar_lenth(char *str);
int					check_is_num(char *str, int i);
int					count_lenth2(char *str, int *i);
int					is_not_valid_expend(char *str, int i);
int					put_env_in_word(char *str, char *word, char *env_var,
						int *i, int *j);
int					ft_put_word_token(char **line, enum e_token_type token_t,
						t_token **tokens_list, int heredoc);
void				free_node(t_node *node);
void				free_redir_list(t_redir *redir);
void				free_node_list(t_node *node_list);
void				skip_double_signs(char *str, int *i);
void				skip_quo(char *tokens_word, int *i, int quot);
void				skip_if_isalnum(char *tokens_word, int *i);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
void				skip_double_quo(char *tokens_word, int *to_split, int *i);
void				fill_word_sgl_quot(char *word, char *str, int *i, int *j);
void				ft_redi_add_back(t_redir **redirections,
						t_redir *new_redir);
void				fill_redi(enum e_token_type token_t, char *red_file,
						t_redir **redirections);
void				token_new_edi_word(char *word, enum e_token_type token_t,
						t_token **tokens_list);
void				ft_put_token(char **line, enum e_token_type token_t,
						t_token **tokens_list);
void				token_new_word(char *word, enum e_token_type token_t,
						t_token **tokens_list, int heredoc);
t_token				*ft_tokenize(t_minishell g_minishell);
t_token				*rm_qotes(t_token *tokens);
t_token				*parsing(t_minishell g_minishell);
t_node				*mk_nodes(t_token *tokens);
t_node				*allocate_for_node(t_token *temp_tokens);
void				free_env_list(t_env *head);
//  🥳 EXECUTION PART:

t_env	*mk_env(char **envirement);

// functionts utils:
int					ft_strcmp(char *s1, char *s2);
void				ft_sigint(int x);
char 				**mk_tenv_char(t_env *envir);

// commands:
t_env				*ft_env_unset(t_minishell data);
int					check_key(char *str, t_env *envir);
int 				ft_check_building(t_token *token);
int					ft_cd(t_token *data);
char				*put_quot2_value(char *str);
char				*rm_quot2_value(char *str);
void				ft_pwd(t_token *data);
void				ft_echo(t_token *data);
void				check_command(t_token *data,
						t_env *expo_envir, t_env *env_envir);
void				ft_env(t_minishell data);
void				ft_exit(t_token *data);
void				ft_unset(t_env *env_list, t_minishell data);
void				ft_export(t_token *tokens, t_env *expo_envir, t_env *env_envir);
void				ft_env_export_once(t_token *data, t_env *envir, int active);
void				key_without_equal(t_token *tokens, t_env *envir, int active);
void				remove_node(t_env** head, char *keyToRemove);
void				search_check_add_env(t_env *expo_envir, t_env *env_envir);
void				*mk_env_4expo(char **envir);
char				*ft_strncpy(char *dst, const char *src, size_t len);
// void				ft_env_export_once(t_token *token, int active);
// void			ft_add_to_export_arg(t_token *token);


// executr commands:
int ft_execute(t_token *data, char **env);

// redirectios:
int					ft_output(t_token *tokens);
int					ft_input(t_token *tokens);
int					ft_append(t_token *tokens);
int					ft_check_redirections(t_minishell *data, t_token *tokens);
int					main_heredoc(t_token *tokens);
int					ft_heredoc(t_token *tokens);
int					start_heredoc(int fd, char *limiter);
int					ft_start_heredoc(int fd, char *limiter);
// error:
void	ft_error(char *msg);
// PIPE:
int execute_piped_commands(t_node *nodes, char **env);


#endif
