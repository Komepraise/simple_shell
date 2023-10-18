#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/


#include "macros.h" /* for msg help and prompt */


/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for gt_line
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: numb of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} program_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct def
{
	char *def;
	int (*function)(program_data *data);
} def;



void inicialize_data(program_data *data, int arc, char *argv[], char **env);

void sisifo(char *prompt, program_data *data);

void handle_ctrl_c(int opr UNUSED);



int gt_line(program_data *data);

int logic_check(char *arr_com[], int x, char opp_arr[]);


void exp_variables(program_data *data);

void exp_alias(program_data *data);

int add_buf(char *buffer, char *str_to_add);


void tokenize(program_data *data);

char *_strtok(char *line, char *delim);


int execute(program_data *data);

int def_list(program_data *data);

char **tokenize_path(program_data *data);

int find_prog(program_data *data);

void free_array_of_pointers(char **directories);

void rel_rec_dat(program_data *data);

void free_all_data(program_data *data);

int def_exit(program_data *data);

int def_cd(program_data *data);

int set__act_dir(program_data *data, char *new_dir);

int def_help(program_data *data);

int def_alias(program_data *data);

int def_env(program_data *data);

int def_set_env(program_data *data);

int def_unset_env(program_data *data);


char *get_env_key(char *name, program_data *data);

int ste_env_key(char *key, char *value, program_data *data);

int rmv_env_key(char *key, program_data *data);

void _print_env(program_data *data);

int _print(char *string);

int _prints(char *string);

int _print_err(int errorcode, program_data *data);

int str_len(char *string);

char *str_dup(char *string);

int str_comp(char *string1, char *string2, int numb);

char *str_coc(char *string1, char *string2);

void str_rev(char *string);

void long_to_string(long numb, char *string, int base);

int _atoi(char *s);

int cnt_char(char *string, char *character);

int pnt_alias(program_data *data, char *alias);

char *get_alias(program_data *data, char *alias);

int set_alias(char *alias_string, program_data *data);


#endif /* SHELL_H */
