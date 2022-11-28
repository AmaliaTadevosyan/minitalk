/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtadevo <amtadevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:05:42 by amtadevo          #+#    #+#             */
/*   Updated: 2022/11/19 14:39:47 by amtadevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

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

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_putnbr(int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nbr);
	}
	else if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
	{
		ft_putchar(nbr + '0');
	}
}

static void	handler(int signum)
{
	static char	byte = 0;
	static int	shift = 7;

	if (signum == SIGUSR1)
	{
		byte |= (1 << shift);
		--shift;
	}
	if (signum == SIGUSR2)
	{
		--shift;
	}
	if (shift < 0)
	{
		write(1, &byte, 1);
		if (byte == '\0')
			write(1, "\n", 1);
		shift = 7;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_putstr("PID - ");
	ft_putnbr(pid);
	write(1, "\n", 1);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
		;
	return (0);
}
