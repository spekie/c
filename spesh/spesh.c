/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 spekie
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define DELIMS " \t\r\n"

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        char *args[MAX_CMD_LEN];
        char *token = strtok(command, DELIMS);
        int i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, DELIMS);
        }

        args[i] = NULL;

        if (execvp(args[0], args) == -1) {
            perror("Command not found");
        }

        exit(1);
    } else {
        wait(NULL);
    }
}

int main() {
	printf("spesh, the Simple Program Execution SHell\n\n");
    char command[MAX_CMD_LEN];

    while (1) {
        printf("spesh >$ ");
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            if (feof(stdin)) {
                break;
            } else {

                perror("Input error");
                continue;
            }
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);
    }

    return 0;
}
