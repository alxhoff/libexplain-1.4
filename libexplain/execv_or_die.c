/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2012, 2013 Peter Miller
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <libexplain/ac/errno.h>
#include <libexplain/ac/unistd.h>

#include <libexplain/execv.h>
#include <libexplain/output.h>


void
explain_execv_or_die(const char *pathname, char *const*argv)
{
    if (explain_execv_on_error(pathname, argv) < 0)
    {
        explain_output_exit_failure();
    }
}


int
explain_execv_on_error(const char *pathname, char *const *argv)
{
    int             result;

    result = execv(pathname, argv);
    if (result < 0)
    {
        int             hold_errno;

        hold_errno = errno;
        explain_output_error
        (
            "%s",
            explain_errno_execv(hold_errno, pathname, argv)
        );
        errno = hold_errno;
    }
    return result;
}


/* vim: set ts=8 sw=4 et : */
