/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:14:16 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/07 17:43:50 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H // Proteção contra inclusões múltiplas
# define MINISHELL_H // Identificador do cabeçalho

# include <unistd.h>           // Funções POSIX básicas
# include <errno.h>            // Definições de códigos de erro
# include <stdbool.h>          // Tipo booleano
# include <stdio.h>            // Entrada e saída padrão
# include <stdlib.h>           // Funções utilitárias gerais
# include <readline/readline.h>// Leitura de linha interativa
# include <readline/history.h> // Histórico da readline
# include <signal.h>           // Tratamento de sinais
# include <limits.h>           // Limites do sistema
# include <fcntl.h>            // Controle de arquivos
# include <sys/stat.h>         // Informações sobre arquivos
# include <sys/types.h>        // Definições de tipos do sistema
# include <sys/wait.h>         // Controle de processos

# include "libft.h"            // Biblioteca auxiliar personalizada

/******************************************************************************
*                                                               MACROS
******************************************************************************/
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002" // String do prompt
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"                                   // Prefixo para arquivos de heredoc

# define CMD_NOT_FOUND 127     // Código: comando não encontrado
# define CMD_NOT_EXECUTABLE 126// Código: comando sem permissão de execução

# ifndef PATH_MAX             // Se PATH_MAX não estiver definido
#  define PATH_MAX 4096       // Define o tamanho máximo de caminho
# endif                        // Fim da verificação de PATH_MAX

# define SUCCESS 0             // Código genérico de sucesso
# define FAILURE 1             // Código genérico de falha

/******************************************************************************
*                                                       GLOBAL VARIABLE
******************************************************************************/
extern int      g_last_exit_code; // Armazena o código de saída do último comando

/******************************************************************************
*                                                               STRUCTS
******************************************************************************/
typedef struct s_token              // Estrutura de um token
{
        char                    *str;          // Conteúdo textual
        char                    *str_backup;   // Cópia de segurança
        bool                    var_exists;    // Indica se variável existe
        int                     type;          // Tipo do token
        int                     status;        // Estado de análise
        bool                    join;          // Junta com token anterior
        struct s_token          *prev;         // Token anterior
        struct s_token          *next;         // Próximo token
}       t_token;

typedef struct s_io_fds             // Estrutura de descritores de E/S
{
        char    *infile;           // Arquivo de entrada
        char    *outfile;          // Arquivo de saída
        char    *heredoc_delimiter;// Delimitador do heredoc
        bool    heredoc_quotes;    // Preserva aspas no heredoc
        int     fd_in;             // FD de entrada
        int     fd_out;            // FD de saída
        int     stdin_backup;      // Backup do stdin
        int     stdout_backup;     // Backup do stdout
}       t_io_fds;

typedef struct s_command            // Estrutura de um comando
{
        char            *command;      // Nome do comando
        char            *path;         // Caminho do executável
        char            **args;        // Lista de argumentos
        bool            pipe_output;   // Indica se envia saída para pipe
        int             *pipe_fd;      // FDs do pipe
        t_io_fds        *io_fds;       // Estrutura de E/S
        struct s_command *next;        // Próximo comando
        struct s_command *prev;        // Comando anterior
}       t_command;

typedef struct s_data               // Estrutura principal do shell
{
        bool      interactive;         // Modo interativo
        t_token   *token;              // Lista de tokens
        char      *user_input;         // Entrada do usuário
        char      **env;               // Variáveis de ambiente
        char      *working_dir;        // Diretório atual
        char      *old_working_dir;    // Diretório anterior
        t_command *cmd;                // Lista de comandos
        pid_t     pid;                 // PID do processo
}       t_data;

/******************************************************************************
*                                                               ENUMS
******************************************************************************/

enum e_token_types { // Tipos de tokens possíveis
        SPACES = 1, // Espaços em branco
        WORD,       // Palavra simples
        VAR,        // Variável de ambiente
        PIPE,       // Símbolo de pipe
        INPUT,      // Redirecionamento de entrada
        TRUNC,      // Redirecionamento de saída truncando
        HEREDOC,    // Heredoc
        APPEND,     // Redirecionamento de saída em append
        END         // Fim da linha
};

enum e_quoting_status { // Estados de citação
        DEFAULT, // Sem aspas
        SQUOTE,  // Em aspas simples
        DQUOTE   // Em aspas duplas
};

/******************************************************************************
*                                                               FUNCTIONS
******************************************************************************/

/* ------------------------ INITIALIZATION ----------------------------------*/
//init_data.c
bool            init_data(t_data *data, char **env);       // Inicializa dados do shell
void            init_io(t_command *cmd);                   // Inicializa descritores de E/S

/* ------------------------ ERROR & EXIT HANDLING ---------------------------*/
// exit.c
void            exit_shell(t_data *data, int exno);        // Sai do shell liberando recursos

// error.c
int             errmsg_cmd(char *command, char *detail, char *error_message,
                        int error_nb);                     // Exibe erro específico de comando
void            errmsg(char *errmsg, char *detail, int quotes); // Exibe erro genérico
bool            usage_message(bool return_val);            // Exibe mensagem de uso

// cleanup.c
void            free_data(t_data *data, bool clear_history);    // Libera estrutura principal
void            close_fds(t_command *cmds, bool close_backups); // Fecha descritores
void            free_io(t_io_fds *io);                          // Libera estrutura de E/S
void            free_ptr(void *ptr);                            // Libera ponteiro genérico
void            free_str_tab(char **tab);                       // Libera vetor de strings

/* ------------------------ LEXER -----------------------------------------*/
// parse_user_input.c
bool            parse_user_input(t_data *data);             // Lê e analisa entrada

// tokenization.c
int             tokenization(t_data *data, char *str);      // Separa entrada em tokens

// tokenization_utils.c
int             save_word_or_sep(int *i, char *str, int start, t_data *data); // Salva palavra ou separador
int             set_status(int status, char *str, int i);   // Atualiza estado de aspas
int             is_separator(char *str, int i);             // Verifica separador
int             save_word(t_token **token_lst, char *str, int index, int start);   // Salva palavra
int             save_separator(t_token **token_lst, char *str, int index, int type); // Salva separador

// lexer_grammar.c
int             check_consecutives(t_token **token_lst);    // Verifica tokens consecutivos inválidos

// check_if_var.c
int             check_if_var(t_token **token_lst);          // Marca tokens como variáveis

// token_lst_utils.c
t_token         *lst_new_token(char *str, char *str_backup, int type, int status); // Cria token
void            lst_add_back_token(t_token **alst, t_token *new_node); // Adiciona token ao fim
void            lstdelone_token(t_token *lst, void (*del)(void *));   // Remove token
void            lstclear_token(t_token **lst, void (*del)(void *));   // Limpa lista de tokens
t_token         *insert_lst_between(t_token **head, t_token *to_del,
                                t_token *insert);          // Insere token entre nós

/* ------------------------ EXPANSION ---------------------------------------*/
//var_expander.c
int             var_expander(t_data *data, t_token **token_lst); // Expande variáveis

//recover_value.c
char            *recover_val(t_token *token, char *str, t_data *data); // Recupera valor de variável

//identify_var.c
char            *identify_var(char *str);                 // Identifica nome de variável
int             var_length(char *str);                    // Calcula tamanho da variável
bool            is_var_compliant(char c);                 // Verifica caractere válido

//replace_var.c
int             replace_var(t_token **token_node, char *var_value, int index); // Substitui variável
void            copy_var_value(char *new_str, char *var_value, int *j);         // Copia valor
char            *var_expander_heredoc(t_data *data, char *str);                 // Expande em heredoc
char            *replace_str_heredoc(char *str, char *var_value, int index);    // Substitui em heredoc

// var_expander_utils.c
void            copy_var_value(char *new_str, char *var_value, int *j);         // Copia valor (utilitário)
char            *get_new_token_string(char *oldstr, char *var_value,
                                int newstr_size, int index);                    // Gera nova string de token

//quotes_handler.c
int             handle_quotes(t_data *data);              // Trata aspas na tokenização
bool            quotes_in_string(char *str);              // Verifica presença de aspas
int             count_len(char *str, int count, int i);   // Calcula comprimento sem aspas

//quotes_remover.c
int             remove_quotes(t_token **token_node);      // Remove aspas dos tokens

/* ------------------------ PARSER ---------------------------------------*/

// create_command.c
void            create_commands(t_data *data, t_token *token); // Cria lista de comandos

// parse_command.c
void            parse_word(t_command **cmd, t_token **token_lst); // Analisa palavra e adiciona comando

// fill_args_default.c
int             fill_args(t_token **token_node, t_command *last_cmd);           // Preenche argumentos
int             add_args_default_mode(t_token **token_node, t_command *last_cmd); // Adiciona argumento (modo padrão)
int             create_args_default_mode(t_token **token_node, t_command *last_cmd); // Cria array de argumentos

// fill_args_echo_mode.c
int             add_args_echo_mode(t_token **token_node, t_command *last_cmd); // Argumentos específicos para echo
int             create_args_echo_mode(t_token **token_node, t_command *last_cmd); // Cria array para echo

// fill_args_echo_utils.c
char            *join_vars(t_token **token_node);         // Junta variáveis contíguas
int             count_args(t_token *temp);                // Conta argumentos
char            **copy_in_new_tab(int len, char **new_tab,
                                t_command *last_cmd, t_token *tmp);            // Copia argumentos
void            remove_empty_var_args(t_token **tokens);  // Remove argumentos vazios

// cmd_lst_utils.c
t_command       *lst_new_cmd(bool value);                 // Cria novo comando
void            lst_add_back_cmd(t_command **alst, t_command *new_node); // Adiciona comando
t_command       *lst_last_cmd(t_command *cmd);            // Último comando
t_command       *lst_first_cmd(t_command *cmd);           // Primeiro comando

// cmd_lst_utils_cleanup.c
void            lst_delone_cmd(t_command *lst, void (*del)(void *)); // Remove comando
void            lst_clear_cmd(t_command **lst, void (*del)(void *)); // Limpa lista de comandos

// parse_trunc.c
void            parse_trunc(t_command **last_cmd, t_token **token_lst); // Redirecionamento de saída truncado
char            *get_relative_path(char *file_to_open);                // Obtém caminho relativo

// parse_input.c
bool            remove_old_file_ref(t_io_fds *io, bool infile);        // Remove referência antiga
void            parse_input(t_command **last_cmd, t_token **token_lst); // Redirecionamento de entrada

// parse_append.c
void            parse_append(t_command **last_cmd, t_token **token_lst); // Redirecionamento de saída append

// parse_heredoc.c
void            parse_heredoc(t_data *data, t_command **last_cmd,
                                t_token **token_lst);                  // Configura heredoc

// parse_heredoc_utils.c
bool            fill_heredoc(t_data *data, t_io_fds *io, int fd);      // Preenche conteúdo do heredoc

// parse_pipec
void            parse_pipe(t_command **cmd, t_token **token_lst);      // Divide comandos por pipe

/* ------------------------ EXECUTION ---------------------------------------*/
// env.c
int             env_var_count(char **env);             // Conta variáveis de ambiente
int             get_env_var_index(char **env, char *var);    // Obtém índice de variável
char            *get_env_var_value(char **env, char *var);  // Recupera valor de variável
bool            is_valid_env_var_key(char *var);       // Verifica chave válida

// env_set.c
bool            set_env_var(t_data *data, char *key, char *value); // Define variável
bool            remove_env_var(t_data *data, int idx);            // Remove variável

// builtins
int             env_builtin(t_data *data, char **args);   // Implementação de env
int             pwd_builtin(t_data *data, char **args);   // Implementação de pwd
int             echo_builtin(t_data *data, char **args);  // Implementação de echo
int             export_builtin(t_data *data, char **args);// Implementação de export
int             unset_builtin(t_data *data, char **args); // Implementação de unset
int             cd_builtin(t_data *data, char **args);    // Implementação de cd
int             exit_builtin(t_data *data, char **args);  // Implementação de exit

// signal.c
void            ignore_sigquit(void);                   // Ignora SIGQUIT
void            set_signals_interactive(void);          // Sinais para modo interativo
void            set_signals_noninteractive(void);       // Sinais para modo não interativo

// execute.c
int             execute(t_data *data);                  // Executa comandos

// execute_cmd.c
int             execute_command(t_data *data, t_command *cmd); // Executa comando externo
int             execute_builtin(t_data *data, t_command *cmd); // Executa builtin

// execute_utils.c
bool            cmd_is_dir(char *cmd);                  // Verifica se é diretório
int             check_command_not_found(t_data *data, t_command *cmd); // Erro de comando não encontrado

// parse_path.c
char            *get_cmd_path(t_data *data, char *cmd); // Obtém caminho do executável

// pipe.c
bool            create_pipes(t_data *data);             // Cria pipes necessários
bool            set_pipe_fds(t_command *cmds, t_command *curr_cmd); // Configura FDs de pipe
void            close_pipe_fds(t_command *cmds, t_command *skip_cmd); // Fecha FDs de pipe

// file_io.c
bool            check_infile_outfile(t_io_fds *io);     // Verifica arquivos de E/S
bool            redirect_io(t_io_fds *io);              // Realiza redirecionamento
bool            restore_io(t_io_fds *io);               // Restaura descritores originais

// heredoc.c
bool            get_heredoc(t_data *data, t_io_fds *io); // Obtém conteúdo de heredoc

/* ------------------------ DEBUG -------------------------------------------*/
// debug.c
void            print_cmd_list(t_data *data);          // Imprime comandos para depuração
void            print_token_list(t_token **tokens);    // Imprime tokens para depuração

#endif // Fim da proteção do cabeçalho
