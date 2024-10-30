#include "../includes/tokenizer.h"

int	m_get_next_status(int status, char c)
{
	int	new_status;

	if (status == 1)
		new_status = m_get_status_1(c);
	else if (status == 40)
		new_status = m_get_status_40(c);
	else if (status == 60)
		new_status = m_get_status_60(c);
	else if (status == 70)
		new_status = m_get_status_70(c);
	else if (status == 80)
		new_status = m_get_status_80(c);
	else if (status == 81)
		new_status = m_get_status_81(c);
	else if (status == 82)
		new_status = m_get_status_82(c);
	else
		new_status = -1;
	return (new_status);
}

int	m_get_status_1(char c)
{
	if (c == '|')
		return (40);
	else if (c == '<')
		return (60);
	else if (c == '>')
		return (70);
	else if (ft_isalnum(c))
		return (80); //ft_isalnum olha se é dígito ou alfabético//ft_isalnum olha se é dígito ou alfabético
	else if (c == '\'')
		return (81);
	else if (c == '\"')
		return (82);
	else if (c == '\0' || ft_isspace(c))
		return (1); //se achar um white space ou fim da linha, continua no status 1 e vai sair do loop lá na função m_tokenize
	else
		return (-1);
}

// definir comportamento se o minishell achar outro '|' -> retornar erro, considerar como um pipe só ou outra coisa?

int	m_get_status_40(char c)
{
	if (c == '|')
		return (-1); //no momento caso achar outro '|', retorna o -1, status de erro
	else if (c != '|')
		return (41);
	else
		return (-1);
}

int	m_get_status_60(char c)
{
	if (c == '<')
		return (61); //se achar outro '<' retorna o final_state de REDIR_HEREDOC
	else if (c != '<')
		return (62); //se achar qualquer outro caractere, retorna o final_state de REDIR_IN
	else
		return (-1);
}

int	m_get_status_70(char c)
{
	if (c == '>')
		return (71); //se achar outro '>' retorna o final_state de REDIR_APPEND
	else if (c != '>')
		return (72); //se achar qualquer outro caractere, retorna o final_state de REDIR_OUT
	else
		return (-1);
}
