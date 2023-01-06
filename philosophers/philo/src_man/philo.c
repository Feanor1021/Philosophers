/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:39:25 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/16 14:14:45 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_arg	rules;

	if (argc != 5 && argc != 6)
		return (error_message("Wrong amount of arguments!!!"));
	if (set_rules(&rules, argv, argc))
		return (error_message("\nSomething happend at initilazion phase..."));
	if (handle_resources(&rules))
		return (error_message("\nSomething happened at process phase...."));
	return (0);
}
