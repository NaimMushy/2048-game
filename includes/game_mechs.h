/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mechs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:12:16 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 20:15:29 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_MECHS_H
# define GAME_MECHS_H

# include "wkw.h"

enum e_error	game_init(t_board *board, int size);
enum e_error	add_tile(t_board* ptr_board);
enum e_error	game_loop(t_board* ptr_board, int input);
bool			process_line(t_board* ptr_board, int* line);
void			get_line(t_board* ptr_board, int* line, int input, int index);
void			set_line(t_board* ptr_board, int* line, int input, int index);

#endif