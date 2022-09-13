/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_raw_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:59:52 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 14:30:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 * Saving the current terminal attributes into our struct 'raw'
 * We then use bitwise operations with macros from termios.h to change the
 * attributes of our terminal.
 *
 * Local flags:
 * First we turn OFF echo (ECHO), so chars typed by the use wont be displayed.
 * We also turn off canonical mode (ICANON), so text typed by the user is
 * read byte by byte
 * To disable signals ctrl-C and ctrl-Z, we also invoke ISIG, however, we want
 * to implement special handling for these so we leave it on.
 * To disable ctrl-V (allows next char to be read literally), we use IEXTEN
 * (and also ctrl-O on macOS)
 *
 * Input flags:
 * We need to turn off ctrl-S and ctrl-Q,(IXON) as we don't need to pause and
 * resume data being transmitted to the terminal. Also ICRNL is invoked to stop
 * ctrl-M being interpretted as a carriage return. However, this stopped
 * enter being processed correctly so we leave it on.
 * When BRKINT is on, a break condition will cause an interrupt signal
 * INPCK enables parity checking (probably wont effect term emulators)
 * ISTRIP sets the 8th input byte to 0 (probably already off)
 *
 * Output flags:
 * Normal when a \n char is read, a \r (carriage return) char is added by
 * default, to move the cursor back to the start of the line. We turn off
 * OPOST to stop this happening, but keep in mind, in printf we now need to
 * add it manually
 *
 * CS8 is not a flag but a bit mask, it sets all chars to 8 bits per byte
 * (on most systems this is already the case)
 *
 * VMIN and VTIME are set to 0 and 1 respectively, so if there is no data
 * to read after 1/10 of 1 second, read returns 0 and control flow continues
 * throught the program. Also the minimum number of bytes that can be read
 * is set to 0
 *
 * Once we are happy with the adjustments to our a settings, we use tcsetattr
 * to apply them to the stdin file descriptor. TCSAFLUSH means that this waits
 * for any pending output to be written to terminal, and discards input not yet
 * read.
 */

void	enable_raw_mode(void)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		return ;//die("tcgetattr");
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_iflag &= ~(IXON | BRKINT | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		return ;//die("tcsetattr");
}
