#include "../includes/tokenizer.h"

int	m_get_status_80(char c)
{
	if (c == '\'')
		return (81);
	else if (c == '\"')
		return (82);
	else if (m_is_special_char(c))
		return (83);
	else if (ft_isspace(c) || c == '\0')
		return (83);
	else if (!m_is_special_char(c))
		return (80);
	else
		return (-1);
}

int	m_get_status_81(char c)
{
	if (c == '\0')
		return (-1); //se acabar a linha dentro do status 81 - ou seja, sem fechar as aspas simples - retorna erro
	else if (c == '\'')
		return (80); //se achar outra aspa simples, volta para o estado 80 - isso porque se no próximo loop achar um espaço, por exemplo, vai fechar o token no estado 83 (palavra) 
	else if (c != '\'')
		return (81); //se achar quaquer outro caractere, continua dentro do status 81
	else
		return (-1);
}

int	m_get_status_82(char c)
{
	if (c == '\0')
		return (-1);  //se acabar a linha dentro do status 82 - ou seja, sem fechar as aspas duplas - retorna erro
	else if (c == '\"')
		return (80);
	else if (c != '\"')
		return (82);
	else
		return (-1);
}

int	m_status_needs_backtrack(int status)
{
	if (status == 41 \
            || status == 62 \
            || status == 72 \
            || status == 83)
		return (1);
    return (0);
}

//LEGENDA STATUS
//---> 83 = WORD ----------> token type number = 0
//---> 40 = PIPE ----------> token type number = 1
//---> 62 = REDIR_IN ------> token type number = 2
//---> 61 = REDIR_HEREDOC -> token type number = 3
//---> 72 = REDIR_OUT -----> token type number = 4
//---> 71 = REDIR_APPEND --> token type number = 5
int	m_is_final_status(int status)
{
	return (status == 41 
                || status == 61 || status == 62 \
			    || status == 71 || status == 72 \
			    || status == 83);
}