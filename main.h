#ifndef _MAIN_H_
#define _MAIN_H_

#include <bits/types/FILE.h>
#include <cstddef>
#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


/* Points to the array of pointers to strings called the "environment" */


extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @_environ: environment variable
 * @pid: process ID of the shell.
 *
 */






typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;

} data_shell ;



/**
 * struct line_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */




typedef struct line_list_s
{
	char separator;
	struct sep_list_s *next;

} sep_list;


/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */




typedef struct line_list_s 
{
	char *line;
	struct line_list_s *next;
} line_list;


/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @next: next node
 * Description: single linked list to store variables
 */





typedef struct r_var_list *next 
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;

} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env.
 * @f: data type pointer function.
 */




typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *dataash);
} builtin_t;


/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);


/* aux_lists2.c */
rvar *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
char *_strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int *_strspn(char *s, char *accept);


/* aux_mem.c  */
void _memcpy(void *nextptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars( char str[] *delim);
char *_strtok(char str[],const char *delim);
int _isdigit(const char *s);


/* aux_str3 */
void rev_string(char *s);

/* check_syntax_error.c  */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *dataash, char *input, int i, int bool);
int check_syntax_error(data_shell *dataash, char *input);


/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *dataash);

/* read_line.c */
char *read_line(int *i_eof);


/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *dataash);
int split_commands(data_shell *dataash, char *input);
char **split_line(char *input);





/* rep_var.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *dataash);


/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);




/* exec_line */
int exec_line(data_shell *dataash);



/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *which(char *cmd, char **environ);
int is_executable(data_shell *dataash);
int check_error_cmd(char *dir, data_shell *dataash);
int cmd_exec(data_shell *dataash);




/* env1.c */
char *_getenv();
int _env();


/* env2.c */
char *copy_info();
void set_env();
int _setenv();
int _unsetenv();


/* cd.c */
void cd_dot(data_shell *dataash);
void cd_to(data_shell *dataash);
void cd_previous(data_shell *dataash);
void cd_to_home(data_shell *dataash);


/* cd_shell.c */
int cd_shell(data_shell *dataash);



/* get_builtin */
int (*get_builtin(char *cmd)) (data_shell *dataash);

/* _exit.c */
int exit_shell(data_shell *dataash);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);


/* aux_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *dataash);
char *error_not_found(data_shell *dataash);
char *error_exit_shell(data_shell *dataash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *dataash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *dataash);




/* get_error.c */
int get_error(data_shell *dataash, int eval);


/* get_sigint.c */
void get_sigint(int sig);




/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);


/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);





/* get_help.c */
int get_help(data_shell *dataash);



#endif
