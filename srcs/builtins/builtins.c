#include "minishell.h"
#include <sys/param.h>

int	ft_echo(t_vec *argv)
{
	char	**strs;
	size_t	i;
	int		print_nl;
	int		r;

	strs = (char **)argv->memory;
	if (!ft_strncmp(strs[0], "-n", 3))
		print_nl = 0;
	else
		print_nl = 1;
	i = 0;
	while (i < argv->len)
	{
		r = ft_putstr_fd(strs[i], 1);
		if (r == -1)
			return (1);
		if (i < argv->len - 1)
			r = write(1, " ", 1);
		if (r == -1)
			return (1);
		i++;
	}
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}

int	ft_cd(t_vec *argv)
{
	char	**strs;
	int		r;

	strs = (char **)argv->memory;
	r = chdir(strs[0]);
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd:", 3);
		ft_putstr_fd(strs[0], 3);
		perror(0);
	}
	return (r);
}

int	ft_pwd(t_vec *argv)
{
	char	str[MAXPATHLEN];
	char	*check;

	(void)argv;
	check = getcwd(str, MAXPATHLEN);
	if (!check)
	{
		ft_putstr_fd("minishell: pwd:", 3);
		ft_putstr_fd(str, 3);
		perror(0);
		return (-1);
	}
	else
		return (0);
}
