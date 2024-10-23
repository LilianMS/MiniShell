#include "../includes/minishell.h"

int m_check_quotes(const char *line)
{
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	while (*line)
	{
		if (*line == '\'' && !double_q)
			single_q = !single_q;
		else if (*line == '\"' && !single_q)
			double_q = !double_q;
		line++;
	}
	return (!single_q && !double_q);
}