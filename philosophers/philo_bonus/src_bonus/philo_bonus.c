/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:51 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 14:42:51 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_arg	rules;

	if (argc != 5 && argc != 6)
		return (error_message("Wrong amount of arguments!!!"));
	if (init_data(&rules, argv))
		return (error_message("\nSomething happend at initilazion phase..."));
	if (handle_resources(&rules))
		return (error_message("\nSomething happened at process phase...."));
	return (0);
}
