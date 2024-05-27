#include "../cub3d.h"

int usage()
{
	ft_putstr_fd("Usage:\n./cub3d file.cub\n", 1);
	return (1);
}

int is_cub(char *str)
{
	int i;
	if (ft_strlen(str) < 4)
		return (0);
	i = 0;
	while (str[i])
		i++;
	i = i - 4;
	if (ft_strncmp(str + i, ".cub", 4))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	int fd_cub;

	if (ac != 2)
	{
		ft_putstr_fd("Error: arguments\n\n", 2);
		return (usage());
	}
	if (!is_cub(av[1]))
	{
		ft_putstr_fd("Error: not a .cub file\n\n", 2);
		return (usage());
	}
	fd_cub = open(av[1], O_RDONLY);
	if (fd_cub == -1)
	{
		ft_putstr_fd("Error: open\n\n", 2);
		return (usage());
	}
	if (check_file(fd_cub))
	{
		ft_putstr_fd("Error: param\n\n", 2);
		return (usage());
	}
}
