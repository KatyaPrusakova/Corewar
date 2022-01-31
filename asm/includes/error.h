/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:28:32 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 18:36:41 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_MALLOC_ASM	    	"\x1b[31mMalloc Error: can't locate memory for asm struct.\n\033[0m"
# define ERR_NAME	 			"\x1b[31mIncorrect file type.\n\033[0m"
# define ERR_OPEN	 			"\x1b[31mOpen Error on source file.\n\033[0m"
# define ERR_MULT_NAME	 		"\x1b[31mMultiple names!\n\033[0m"
# define ERR_NO_NAME	 		"\x1b[31mNo name or comment!\n\033[0m"
# define ERR_INC_NAME	 		"\x1b[31mIncorrect name/comment.\n\033[0m"
# define ERR_INV_CHAR			"\x1b[31mInvalid char following name/comment!\n\033[0m"
# define ERR_INV_COM			"\x1b[31mInvalid command on line:\n	\033[0m"
# define ERR_NAME_COM			"\x1b[31mName or comment missing!\n\033[0m"
# define ERR_MALLOC_STR	    	"\x1b[31mMalloc Error: can't locate memory for string.\n\033[0m"
# define ERR_MALLOC_OPER    	"\x1b[31mMalloc Error: can't locate memory for operation struct.\n\033[0m"
# define ERR_LEB_CHAR			"\x1b[31mWrong chars in label:\n	\033[0m"
# define ERR_LEB_DUB			"\x1b[31mDuplicate label:\n	\033[0m"
# define ERR_ARG			"\x1b[31mToo many arguments on line:\n	\033[0m"

#endif