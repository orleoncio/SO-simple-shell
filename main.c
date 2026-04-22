#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64


//Ajuste no parsing
void parse_command(char *line, char **args) {
    int i = 0;

    args[i] = strtok(line, " \t\n");

    while (args[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        args[i] = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("minimalistshell> ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break; // Ctrl + D
        }

        parse_command(line, args);

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "Uso: cd <diretorio>\n");
            } else if (chdir(args[1]) == -1) {
                perror("Erro no cd");
            }
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork, nao foi possivel alocar memoria");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);

            perror("Erro ao executar comando");
            exit(EXIT_FAILURE);
        } else {
            if (waitpid(pid, NULL, 0) == -1) {
                perror("Erro no waitpid");
            }
        }
    }

    return 0;
}
