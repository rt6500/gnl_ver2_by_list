#include <stdio.h> //puts/printf
#include <fcntl.h>//open
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	if (ac == 1)
		fd = STDIN_FILENO;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return(printf("Error\nInvalid input\n"), 1);
	while((line = get_next_line(fd)))
	{
		printf("%d->%s\n", lines++, line);
		free (line);
	}
	if (ac == 2 && close(fd) < 0)
		return (perror("error closing file"), 1);
	return (0);
}

// int	main()
// {
// 	int	fd;
// 	fd = open("text.txt", O_RDONLY | O_CREAT);
// 	printf("fd of file: %d\n", fd);
// 	sleep(100);
// 	return (0);
// }

// int	main()
// {
// 	int		fd;
// 	char	*line;
// 	int		lines;

// 	lines = 1;
// 	fd = open("text.txt", O_RDONLY);

// 	while((line = get_next_line(fd)))
// 		printf("%d->%s\n", lines++, line);
// 	close(fd);
// 	return (0);
// }