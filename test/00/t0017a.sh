#!/bin/sh
#
# libexplain - Explain errno values returned by libc functions
# Copyright (C) 2008, 2010, 2011 Peter Miller
# Written by Peter Miller <pmiller@opensource.org.au>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.
#

TEST_SUBJECT="fcntl vs EFAULT"
. test_prelude

fmt > test.ok << 'fubar'
fcntl(fildes = 42, command = F_SETLKW, data = PPPPPPPP) failed, Bad address
(EFAULT) because data refers to memory that is outside the process's accessible
address space; this is more likely to be a software error (a bug) than it is to
be a user error
fubar
test $? -eq 0 || no_result

explain -e EFAULT fcntl 42 F_SETLKW > test.out.4
test $? -eq 0 || fail

fmt -w 700 < test.out.4 > test.out.3
test $? -eq 0 || no_result

sed 's|, data = [^,)]*)|, data = PPPPPPPP)|' < test.out.3 > test.out.2
test $? -eq 0 || no_result

fmt < test.out.2 > test.out
test $? -eq 0 || no_result

diff test.ok test.out
test $? -eq 0 || fail

#
# Only definite negatives are possible.
# The functionality exercised by this test appears to work,
# no other guarantees are made.
#
pass

# vim:ts=8:sw=4:et
