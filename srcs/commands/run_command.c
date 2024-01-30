/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/30 10:10:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

pid_t	execute_command(t_vec argv)
{
	int		ret;
	char	**strs;
	char	*nulterm;

	nulterm = ft_calloc(1, sizeof(char *));
	if (nulterm == 0)
		return (-1);
	if (vec_push(&argv, nulterm) == -1)
		return (-1);
	strs = (char **) argv.memory;
	ret = execve(strs[0], strs, NULL);
	perror(strs[0]);
	return (ret);
}

void	apply_redirect(void	*param)
{
	t_redirect	redirect;

	redirect = *(t_redirect *) param;
	if (dup2(redirect.new_fd, redirect.origial_fd) == -1)
		perror("dup failed");
}

int	prepare_command(t_command *command, char *command_str)
{
	vec_new(&command->argv, 0, sizeof(char *));
	if (split_command(&command->argv, command_str) == -1)
		return (-1);
	vec_new(&command->redirects, 0, sizeof(t_redirect));
	if (extract_files(command) == -1)
		return (-1);
	if (add_path((char **) vec_get(&command->argv, 0)) == -1)
		return (-1);
	return (1);
}

int	run_single_command(char *command_str)
{
	t_command	command;
	int			ret;

	if (prepare_command(&command, command_str) == -1)
		return (-1);
	command.process_id = fork();
	if (command.process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (command.process_id == 0)
	{
		vec_iter(&command.redirects, apply_redirect);
		return (execute_command(command.argv));
	}
	waitpid(command.process_id, &ret, 0);
	return (WEXITSTATUS(ret));
}

int	run_command(char *command_str)
{
	int	ret;

	if (ft_strchr(command_str, '|') != 0)
		ret = pipex(command_str);
	else
		ret = run_single_command(command_str);
	return (ret);
}