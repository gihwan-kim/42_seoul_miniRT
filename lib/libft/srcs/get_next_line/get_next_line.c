/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 10:45:35 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/22 15:29:30 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_makestr(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(size);
	if (str == 0)
		return (0);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

static char	*check_buf_temp(char *buf_temp, char **line, int *ret)
{
	char *check_buf_temp_ptr;

	check_buf_temp_ptr = 0;
	*ret = 1;
	if (buf_temp != 0)
	{
		if ((check_buf_temp_ptr = ft_strchr(buf_temp, '\n')))
		{
			*check_buf_temp_ptr = '\0';
			++check_buf_temp_ptr;
			*line = ft_strdup(buf_temp);
			ft_strlcpy(buf_temp, check_buf_temp_ptr,
				ft_strlen(check_buf_temp_ptr) + 1);
		}
		else
		{
			*line = ft_strdup(buf_temp);
			while (*buf_temp)
				*(buf_temp++) = 0;
		}
	}
	else
		*line = ft_makestr(1);
	return (check_buf_temp_ptr);
}

static void	my_free(char **str)
{
	if (*str && (**str >= 0))
	{
		free(*str);
		*str = 0;
	}
}

static int	check_ret(int *ret, char **buf_temp, char **line)
{
	if (*ret > 0)
		return (1);
	else
	{
		if (*buf_temp && (**buf_temp >= 0))
		{
			free(*buf_temp);
			*buf_temp = 0;
		}
		if (*ret == 0)
			return (0);
		else
		{
			if (*line && line)
			{
				free(*line);
				*line = 0;
			}
			return (-1);
		}
	}
}

int			get_next_line(int fd, char **line)
{
	static char	*buf_temp;
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	char		*check_buf_temp_ptr;
	char		*temp;

	if (!line || fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0 || fd == 2)
		return (-1);
	check_buf_temp_ptr = check_buf_temp(buf_temp, line, &ret);
	while (!check_buf_temp_ptr && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		*(buf + ret) = '\0';
		my_free(&buf_temp);
		if ((check_buf_temp_ptr = ft_strchr(buf, '\n')))
		{
			*check_buf_temp_ptr = '\0';
			buf_temp = ft_strdup(++check_buf_temp_ptr);
		}
		temp = *line;
		*line = ft_strjoin(*line, buf);
		free(temp);
	}
	return (check_ret(&ret, &buf_temp, line));
}
