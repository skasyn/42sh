/*
** EPITECH PROJECT, 2018
** history
** File description:
** history
*/

typedef struct history {
    int check;
    char *command;
    FILE *fp;
} history_t;

typedef struct hist_key {
    int x;
    char *path;
} hist_key_t;

void fill_struc(hist_key_t *st);
char *read_line(hist_key_t *st);
char **str_to_word_array(const char *str);
void free_arr(char **str);
char **history_flag(char **str, hist_key_t *st);
int arrow_down(hist_key_t *st, char *line, int *line_length, int *cursor);
int arrow_up(hist_key_t *st, char *line, int *line_length, int *cursor);
void backspace(char *line, int *line_length, int *cursor);
char *get_command(char *command, size_t len, FILE *fp, hist_key_t *st);
void free_all(char **arr, char **str, char *line);
void create_bash_history(hist_key_t *st);
void move_in_file(FILE *fd, hist_key_t *st);
void write_in_history(hist_key_t *st, char **str);