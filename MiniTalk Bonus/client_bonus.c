/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtadevo <amtadevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:56:58 by amtadevo          #+#    #+#             */
/*   Updated: 2022/11/19 15:02:03 by amtadevo         ###   ########.fr       */
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

int	send_bytes(pid_t pid, char str)
{
	int	i;
	int	j;

	i = 7;
	j = 1;
	while (i >= 0)
	{
		if ((str & (1 << i)))
		{
			if (kill(pid, SIGUSR1) < 0)
				j = 0;
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				j = 0;
		}
		--i;
		usleep(100);
	}
	return (j);
}

int	main(int argc, char **argv)
{
	int	get_id;
	int	i;

	get_id = 0;
	i = 0;
	if (argc == 3)
	{
		get_id = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			send_bytes(get_id, argv[2][i]);
			i++;
		}
		if (send_bytes(get_id, '\n') == 1)
			write(1, "Message Received!\n", 18);
		return (0);
	}
}
