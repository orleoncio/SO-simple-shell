#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

// Função para dividir o comando em argumentos
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
        // Exibe prompt
        printf("myshell> ");
        fflush(stdout);

        // Lê entrada do usuário
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break; // Ctrl+D
        }

        // Remove linha vazia
        if (strcmp(line, "\n") == 0) {
            continue;
        }

        // Parse do comando
        parse_command(line, args);

        // Comando "exit" para sair
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Cria processo filho
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
            exit(1);
        }

        if (pid == 0) {
            // Processo filho executa comando
            execvp(args[0], args);

            // Se exec falhar
            perror("Erro ao executar comando");
            exit(1);
        } else {
            // Processo pai espera o filho
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}