# Shell Simplificado

Implementacao simples de um shell em C para a atividade de Sistemas Operacionais.
O programa segue o fluxo classico: mostra prompt, le uma linha, separa comando e
argumentos, cria um processo filho com `fork`, executa com `execvp` e aguarda com
`waitpid`.

## Compilacao

```bash
gcc -Wall -Wextra -o myshell main.c
```

## Execucao

```bash
./myshell
```

Exemplos de comandos suportados:

```bash
pwd
ls
ls -l
date
echo teste
exit
```

Linhas vazias ou compostas apenas por espacos sao ignoradas. Comandos externos
inexistentes exibem erro e o shell continua executando.

## Testes manuais

Depois de compilar e executar, teste alguns comandos basicos:

```bash
pwd
ls -l
echo teste
comando_inexistente
exit
```

Tambem pressione Enter em uma linha vazia ou digite apenas espacos para confirmar
que o shell continua funcionando.

## Limitacoes

Este shell implementa apenas o fluxo basico de execucao de comandos externos com
`fork`, `execvp` e `waitpid`.

Nao ha suporte a:

- pipes (`|`);
- redirecionamento (`>`, `<`, `>>`);
- execucao em background (`&`);
- historico de comandos;
- autocomplete;
- aspas e escaping no estilo Bash.
