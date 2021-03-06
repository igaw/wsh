/*
 *  WSH
 *
 *  Copyright (C) 2007-2011  Daniel Wagner <wagi@monom.org>
 *  Copyright (C) 2007-2011  Peter Luethi <luethi@electronic-engineering.ch>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef WSH_WRAPPER_H		/* prevent circular inclusions */
#define WSH_WRAPPER_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

#include "wsh/wsh.h"		// support for embedded shell

extern wsh_cmd_t *wsh_cmds;	// implemented in project-specific file wsh_cmds.c

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------
// Need to be implemented in wsh_wrapper.c for each project separately to
// ensure portability.

int wsh_getchar(void);
int wsh_putchar(int c);
int wsh_strcmp(const char *s1, const char *s2);
char *wsh_strcpy(char *dest, const char *src);
int wsh_strlen(const char *s);
char *wsh_strtok(char *str, const char *delim);
unsigned long wsh_strtoul(const char *nptr, char **endptr, int base);
int wsh_printf(const char *format, ...);
void wsh_debug_printf(const char *format, ...);
int wsh_cache_data_flush(const void *restrict addr_p, unsigned int length);


#ifdef __cplusplus
}
#endif
#endif				//WSH_WRAPPER_H
