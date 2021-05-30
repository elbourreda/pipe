/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 11:45:03 by rel-bour          #+#    #+#             */
/*   Updated: 2021/05/30 18:03:46 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char 	*ft_path( char **cmd)
// {
// 	char	*bin = NULL;
// 	char 	*temp;
// 	char	**path_split = NULL;
// 	int 	i;
// 	int 	fd;
// 	char	*path;
// 	i = 0;
// 	path = getenv("PATH");
// 	if (!path)
// 	{
// 		printf("getenv() : there is no path variable\n");
// 		exit(1);
// 	}
// 	path_split = ft_split(path, ':');
// 	path = NULL;
// 	while (path_split[i])
// 	{
// 		bin = strdup(path_split[i]);
// 		bin = ft_strjoin(bin, "/");
// 		bin = ft_strjoin(bin, buffer.type);
// 		fd = open(bin, O_RDONLY);
// 		if ( fd != -1)
// 			break ;
// 		else
// 			bin = NULL;
// 		i++;
// 	}
// 	if(fd == -1)
// 		printf("minishell: %s: command not found\n", buffer.type);
// 	free_array(path_split);
// 	free(buffer.type);
// 	free(cmd[0]);
// 	cmd[0] = bin;
//     return(cmd[0]);
// }
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void	free_array(char **array)
{
	int i;
	
	i = 0;
	while (array[i]) 
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	char	*c1;
	char	*c2;
	size_t	i;

	if (!s1 || !s2 || !(r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	c1 = (char *)s1;
	c2 = (char *)s2;
	i = 0;
	while (*c1)
		r[i++] = *(c1++);
	while (*c2)
		r[i++] = *(c2++);
	r[i] = '\0';
	return (r);
}
int		numstring(char const *s1, char c)
{
	int	comp;
	int	cles;

	comp = 0;
	cles = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		if (*s1 == c)
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			comp++;
		}
		s1++;
	}
	return (comp);
}

int		numchar(char const *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

char		**freee(char const **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

char		**affect(char const *s, char **dst, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * numchar(s, c, i) + 1);
		if (dst[j] == NULL)
			return (freee((char const **)dst, j));
		while (s[i] != '\0' && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	char	**dst;
	int		l;

	if (s == NULL)
		return (NULL);
	l = numstring(s, c);
	dst = (char **)malloc(sizeof(char *) * (l + 1));
	if (dst == NULL)
		return (NULL);
	return (affect(s, dst, c, l));
}

char 	*ft_path(char *cmd)
{
	char	*bin = NULL;
	char 	*temp;
	char	**path_split = NULL;
	int 	i;
	int 	fd;
	char	*path;
	i = 0;
	path = getenv("PATH");
	if (!path)
	{
		printf("getenv() : there is no path variable\n");
		exit(1);
	}
	path_split = ft_split(path, ':');
	path = NULL;
	while (path_split[i])
	{
		bin = strdup(path_split[i]);
		bin = ft_strjoin(bin, "/");
		bin = ft_strjoin(bin, cmd);
		fd = open(bin, O_RDONLY);
		if ( fd != -1)
			break ;
		else
			bin = NULL;
		i++;
	}
	if(fd == -1)
		printf("minishell: %s: command not found\n", cmd);
	free_array(path_split);
	// free(buffer.type);
	// free(cmd[0]);
	// cmd[0] = bin;
    return(bin);
}



void	exec_cmd(char **cmd, char *envs[])
{
	pid_t	pid = 0;
	int	status = 0;
	pid = fork();
	if (pid == -1)
		printf("fork() : fails\n");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	if(pid == 0)
	{
		execve(cmd[0], cmd, envs);
		exit(1);
	}
}

int main(int argc, char **argv, char **envs)
{
	int fd[2];
	int f_p[2];
	pid_t pid;
	char **cmd;
	
	fd[0] = open(argv[1], O_CREAT | O_WRONLY , 0777);
	if(fd[0] == -1)
	{
		perror("error fd[0]");
	}
	fd[1] = open(argv[4], O_CREAT | O_WRONLY , 0777);
	if(fd[1] == -1)
		return(0);
	if (pipe(f_p) == -1)
        return(0);// p[0] ,p[1];
	pid = fork();
	if (pid == -1)
		return(0);
	else if(pid == 0)
	{
		dup2(fd[0], 1);
		dup2(f_p[0], fd[0]);
		close(fd[0]);
		//close(fd[1]);
		cmd = ft_split(argv[2], ' ');
		cmd[0] = ft_path(cmd[0]);
		exec_cmd(cmd, envs);
	}
	else
	{
		dup2(fd[1], 1);
		dup2(f_p[1], f_p[0]);
		close(fd[1]);
		// //close(fd[0]);
		cmd = ft_split(argv[3], ' ');
		cmd[0] = ft_path(argv[3]);
		exec_cmd(cmd, envs);
	}
    return 0;
}