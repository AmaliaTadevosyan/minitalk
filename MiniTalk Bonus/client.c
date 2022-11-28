/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtadevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:56:59 by amtadevo         #+#    #+#             */
/*   Updated: 2022/09/07 20:22:06 by amtadevo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r')
		|| str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	send_bytes(pid_t pid, char str)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((str & (1 << i)))
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		--i;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	char	*message;
	pid_t	pid;
	int		i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		message = argv[2];
		while (1)
		{
			send_bytes(pid, message[i]);
			if (message[i] == '\0')
				break ;
			i++;
		}
	}
	else
	{
		ft_putstr("You must have only two arguments!\n");
		ft_putstr("client [pid] [message]\n");
	}
	return (0);
}
