/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_banner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:05:26 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/19 13:40:57 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ps_frame(void)
{
	write(1, "\x1b[34m", 5);
	write(1, "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\", 35);
	write(1, "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n", 25);
	write(1, "\x1b[0m", 4);
}

static void	ps_banner(void)
{
	write(1, "\x1b[32m", 5);
	write(1, "\
	      ___       _____         ___   \n\
	     /  /\\     /  /::\\       /  /\\  \n\
	    /  /:/_   /  /:/\\:\\     /  /:/_ \n\
	   /  /:/ /\\ /  /:/  \\:\\   /  /:/ /\n\
	  /  /:/ /://__/:/ \\__\\:| /  /:/ /:/\n\
	 /__/:/ /:/ \\  \\:\\ /  /://__/:/ /:/ \n\
	 \\  \\:\\/:/   \\  \\:\\  /:/ \\  \\:\\/:/  \n\
	  \\  \\::/     \\  \\:\\/:/   \\  \\::/   \n\
	   \\  \\:\\      \\  \\::/     \\  \\:\\   \n\
	    \\  \\:\\      \\__\\/       \\  \\:\\  \n\
	     \\__\\/                   \\__\\/  \n", 418);
	write(1, "\x1b[0m", 4);
}

static void	ps_usage(void)
{
	write(1, "Usage:	   ./fdf *.fdf\n", 23);
}

int	main(void)
{
	ps_frame();
	ps_banner();
	ps_frame();
	ps_usage();
	return (0);
}