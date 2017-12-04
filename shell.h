void printarr(char* args[]);
char ** parse_args(char* line);
void special_exec(char ** line);
void piping(char * s);
void execute_args(char ** line);
void redirect(int std, int fd, char **line);
void redirecting(int std, char ** line);
void exec(char * command);
