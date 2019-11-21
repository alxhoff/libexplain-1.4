/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2009 Peter Miller
 * Written by Peter Miller <pmiller@opensource.org.au>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CODEGEN_WRAPPER_H
#define CODEGEN_WRAPPER_H

#include <libexplain/ac/stdio.h>

/**
  * The wrapper function may be used to wrap and printf a string.
  *
  * @param fp
  *    The file to print into.
  * @param prefix
  *    The (optional) prefix text to be added to every output line.
  * @param text
  *    The text to be wrapped.
  */
void wrapper(FILE *fp, const char *prefix, const char *text);

/**
  * The wrapper_hang function may be used to wrap and printf a string,
  * the second and subsequent lines are indented 4 spaces relative to
  * the first line.
  *
  * @param fp
  *    The file to print into.
  * @param prefix
  *    The (optional) prefix text to be added to every output line.
  * @param text
  *    The text to be wrapped.
  */
void wrapper_hang(FILE *fp, const char *prefix, const char *text);

#endif /* CODEGEN_WRAPPER_H */
