/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2013 Peter Miller
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

#ifndef LIBEXPLAIN_MOUNT_H
#define LIBEXPLAIN_MOUNT_H

/**
  * @file
  * @brief explain mount(2) errors
  *
  * These functions may be used to obtain explanations for errors returned
  * by the <i>mount</i>(2) system call.
  */

#include <libexplain/gcc_attributes.h>
#include <libexplain/large_file_support.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * The explain_mount_or_die function is used to call the <i>mount</i>(2)
  * system call. On failure an explanation will be printed to stderr,
  * obtained from the <i>#explain_mount</i>(3) function, and then the
  * process terminates by calling <tt>exit(EXIT_FAILURE)</tt>.
  *
  * @param source
  *     The source, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param target
  *     The target, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param file_system_type
  *     The file_system_type, exactly as to be passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The flags, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The data, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @returns
  *     This function only returns on success, see <i>mount</i>(2) for more
  *     information. On failure, prints an explanation and exits, it does
  *     not return.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * explain_mount_or_die(source, target, file_system_type, flags, data);
  * @endcode
  */
void explain_mount_or_die(const char *source, const char *target, const char
    *file_system_type, unsigned long flags, const void *data);

/**
  * The explain_mount_on_error function is used to call the <i>mount</i>(2)
  * system call. On failure an explanation will be printed to stderr,
  * obtained from the <i>#explain_mount</i>(3) function.
  *
  * @param source
  *     The source, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param target
  *     The target, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param file_system_type
  *     The file_system_type, exactly as to be passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The flags, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The data, exactly as to be passed to the <i>mount</i>(2) system
  *     call.
  * @returns
  *     The value returned by the wrapped <i>mount</i>(2) system call.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * if (explain_mount_on_error(source, target, file_system_type, flags, data) <
  *     0)
  * {
  *     ...cope with error
  *     ...no need to print error message
  * }
  * @endcode
  */
int explain_mount_on_error(const char *source, const char *target, const char
    *file_system_type, unsigned long flags, const void *data);

/**
  * The explain_mount function is used to obtain an explanation of an error
  * returned by the <i>mount</i>(2) system call. The least the message will
  * contain is the value of <tt>strerror(errno)</tt>, but usually it will
  * do much better, and indicate the underlying cause in more detail.
  *
  * The errno global variable will be used to obtain the error value to be
  * decoded.
  *
  * @param source
  *     The original source, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param target
  *     The original target, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param file_system_type
  *     The original file_system_type, exactly as passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The original flags, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The original data, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @returns
  *     The message explaining the error. This message buffer is shared by
  *     all libexplain functions which do not supply a buffer in their
  *     argument list. This will be overwritten by the next call to any
  *     libexplain function which shares this buffer, including other
  *     threads.
  * @note
  *     This function is <b>not</b> thread safe, because it shares a return
  *     buffer across all threads, and many other functions in this
  *     library.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * if (mount(source, target, file_system_type, flags, data) < 0)
  * {
  *     explain_output_error_and_die("%s\n", explain_mount(source, target,
  *         file_system_type, flags, data));
  * }
  * @endcode
  * @par
  * The above code example is available pre\-packaged as the
  * #explain_mount_or_die function.
  */
const char *explain_mount(const char *source, const char *target, const char
    *file_system_type, unsigned long flags, const void *data)
                                                  LIBEXPLAIN_WARN_UNUSED_RESULT;

/**
  * The explain_errno_mount function is used to obtain an explanation of an
  * error returned by the <i>mount</i>(2) system call. The least the
  * message will contain is the value of <tt>strerror(errnum)</tt>, but
  * usually it will do much better, and indicate the underlying cause in
  * more detail.
  *
  * @param errnum
  *     The error value to be decoded, usually obtained from the errno
  *     global variable just before this function is called. This is
  *     necessary if you need to call <b>any</b> code between the system
  *     call to be explained and this function, because many libc functions
  *     will alter the value of errno.
  * @param source
  *     The original source, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param target
  *     The original target, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param file_system_type
  *     The original file_system_type, exactly as passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The original flags, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The original data, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @returns
  *     The message explaining the error. This message buffer is shared by
  *     all libexplain functions which do not supply a buffer in their
  *     argument list. This will be overwritten by the next call to any
  *     libexplain function which shares this buffer, including other
  *     threads.
  * @note
  *     This function is <b>not</b> thread safe, because it shares a return
  *     buffer across all threads, and many other functions in this
  *     library.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * if (mount(source, target, file_system_type, flags, data) < 0)
  * {
  *     int err = errno;
  *     explain_output_error_and_die("%s", explain_errno_mount(err, source,
  *         target, file_system_type, flags, data));
  * }
  * @endcode
  * @par
  * The above code example is available pre-packaged as the
  * #explain_mount_or_die function.
  */
const char *explain_errno_mount(int errnum, const char *source, const char
    *target, const char *file_system_type, unsigned long flags, const void
    *data)
                                                  LIBEXPLAIN_WARN_UNUSED_RESULT;

/**
  * The explain_message_mount function is used to obtain an explanation of
  * an error returned by the <i>mount</i>(2) system call. The least the
  * message will contain is the value of <tt>strerror(errnum)</tt>, but
  * usually it will do much better, and indicate the underlying cause in
  * more detail.
  *
  * The errno global variable will be used to obtain the error value to be
  * decoded.
  *
  * @param message
  *     The location in which to store the returned message. If a suitable
  *     message return buffer is supplied, this function is thread safe.
  * @param message_size
  *     The size in bytes of the location in which to store the returned
  *     message.
  * @param source
  *     The original source, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param target
  *     The original target, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param file_system_type
  *     The original file_system_type, exactly as passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The original flags, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The original data, exactly as passed to the <i>mount</i>(2) system
  *     call.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * if (mount(source, target, file_system_type, flags, data) < 0)
  * {
  *     char message[3000];
  *     explain_message_mount(message, sizeof(message), source, target,
  *         file_system_type, flags, data);
  *     explain_output_error_and_die("%s", message);  * }
  * @endcode
  * @par
  * The above code example is available pre-packaged as the
  * #explain_mount_or_die function.
  */
void explain_message_mount(char *message, int message_size, const char *source,
    const char *target, const char *file_system_type, unsigned long flags,
    const void *data);

/**
  * The explain_message_errno_mount function is used to obtain an
  * explanation of an error returned by the <i>mount</i>(2) system call.
  * The least the message will contain is the value of
  * <tt>strerror(errnum)</tt>, but usually it will do much better, and
  * indicate the underlying cause in more detail.
  *
  * @param message
  *     The location in which to store the returned message. If a suitable
  *     message return buffer is supplied, this function is thread safe.
  * @param message_size
  *     The size in bytes of the location in which to store the returned
  *     message.
  * @param errnum
  *     The error value to be decoded, usually obtained from the errno
  *     global variable just before this function is called. This is
  *     necessary if you need to call <b>any</b> code between the system
  *     call to be explained and this function, because many libc functions
  *     will alter the value of errno.
  * @param source
  *     The original source, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param target
  *     The original target, exactly as passed to the <i>mount</i>(2)
  *     system call.
  * @param file_system_type
  *     The original file_system_type, exactly as passed to the
  *     <i>mount</i>(2) system call.
  * @param flags
  *     The original flags, exactly as passed to the <i>mount</i>(2) system
  *     call.
  * @param data
  *     The original data, exactly as passed to the <i>mount</i>(2) system
  *     call.
  *
  * @par Example:
  * This function is intended to be used in a fashion similar to the
  * following example:
  * @code
  * if (mount(source, target, file_system_type, flags, data) < 0)
  * {
  *     int err = errno;
  *     char message[3000];
  *     explain_message_errno_mount(message, sizeof(message), err, source,
  *         target, file_system_type, flags, data);
  *     explain_output_error_and_die("%s", message);
  * }
  * @endcode
  * @par
  * The above code example is available pre-packaged as the
  * #explain_mount_or_die function.
  */
void explain_message_errno_mount(char *message, int message_size, int errnum,
    const char *source, const char *target, const char *file_system_type,
    unsigned long flags, const void *data);

#ifdef __cplusplus
}
#endif

/* vim: set ts=8 sw=4 et : */
#endif /* LIBEXPLAIN_MOUNT_H */
