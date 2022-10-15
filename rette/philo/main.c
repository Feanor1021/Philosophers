/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otokluog <otokluog@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:49:28 by otokluog          #+#    #+#             */
/*   Updated: 2022/10/03 10:49:29 by otokluog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	write_error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong amount of arguments"));
	if (init_data(&rules, argv))
		return (EXIT_FAILURE);
	if (launcher(&rules))
		return (write_error("There was an error creating the threads"));
	return (0);
}