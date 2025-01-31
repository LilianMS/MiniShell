#include "../../includes/minishell.h"

pid_t	extract_pid(const char *buffer)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9')
	{
		pid = pid * 10 + (buffer[i] - '0');
		i++;
	}
	return (pid);
}

pid_t	m_get_process_id()
{
	char	buffer[256];
	int		fd;
	ssize_t	bytes_read;
	pid_t	pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		perror("read");
		close(fd);
		return -1;
	}
	buffer[bytes_read] = '\0';
	close(fd);
	pid = extract_pid(buffer);

	return pid;
}
