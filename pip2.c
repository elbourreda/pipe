// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pip2.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/05/30 14:41:17 by rel-bour          #+#    #+#             */
// /*   Updated: 2021/05/30 15:25:04 by rel-bour         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// // #include "pipe_h.h"


// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

// void test(char *what, char *path, char ls2, char envp)
// {
//     execve(path, ls2, envp);
// }

// int main(int argc, char argv[], char **envp)
// {
//     char ls[] = { "ls", NULL };
//     char* ls2[] = { "pwd", NULL};
//     pid_t pid;
//     int fd[2];

//     pipe(fd);
//     pid = fork();

//     if(pid==0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         test("ls", "/bin/ls", ls, envp);
//         // test("ls", "/bin/ls", ls, envp);
//         // exit(1);
//     }
//     else
//     { 
//         pid=fork();

//         if(pid==0)
//         {
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[1]);
//             close(fd[0]);
//             test("cat", "/bin/cat", ls2, envp);
//             // test("pwd", "/bin/ls", ls2, envp);
//             // execve("/bin/cat", ls2, envp);
//             // exit(1);
//         }
//         else
//         {
//             int status;
//             close(fd[0]);
//             close(fd[1]);
//             waitpid(pid, &status, 0);
//         }
//     }
// }
// C program to illustrate use of fork() &
// exec() system call for process creation

