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

// Project-specific includes including hardware abstraction layer (hal)
#include "wsh/wsh.h"		// support for embedded shell
#include "wsh/wsh_cmds.h"	// wsh standard commands
#include "wsh/wsh_wrapper.h"	// function prototypes

#include <string.h>		// string functions (strcmp)
#include <stdint.h>
#include <stdio.h>

// --- example functions ------------------------------

static unsigned long extract_val(const char *nptr)
{
	char *end;
	return wsh_strtoul(nptr, &end, 0);	// should handle errno somehow, but didn't get it working...
}

static uint8_t demo = 1;

static void set_demo(uint8_t val)
{
	demo = val;
}

static uint8_t get_demo(void)
{
	return demo;
}

// --------------------------------------------------

static void print_unknown_arg(char *arg)
{
	printf("*** unknown argument '%s'\n", arg);
}

static void print_unknown_cmd(char *cmd)
{
	printf("*** unknown command '%s'\n", cmd);
}

static void print_too_many_args(void)
{
	printf("*** too many arguments\n");
}

//static void print_non_numeric_arg (char* cmd)
//{
//  xil_printf("*** non-numeric argument '%s'\n", cmd);
//}

// --------------------------------------------------

static int check_argc(int argc, int lower, int upper, char *usage)
{
	if (argc < lower) {
		printf("*** argument missing:\n");
		printf("usage: %s\n", usage);
		return -1;
	}
	if (argc > upper) {
		print_too_many_args();
		return -1;
	}
	return 0;
}

static int check_cmd(int argc, char *top_usage, char **usage)
{
	if (argc < 1) {
		printf("*** command missing\n");
		printf("usage: %s\n", top_usage);
		while (*usage != 0) {
			printf("         %s\n", *usage);
			usage++;
		}
		return -1;
	}
	return 0;
}

static int my_cmd_demo(int argc, char **argv)
{
	char *usage[] = { "set   load demo (1 | 2 | 3)",
		"get   print current demo configuration",
		0
	};

	if (check_cmd(argc, "demo", usage))	// check for existing arguments
		return -1;

	if (strcmp("get", argv[0]) == 0) {
		if (check_argc(argc, 1, 1, ""))	// check # of arguments
			return -1;

		// get demo configuration
		printf("demo configuration %d\n", get_demo());

	} else if (strcmp("set", argv[0]) == 0) {
		if (check_argc(argc, 2, 2, "demo set ID"))	// check # of args: 2 required
			return -1;

		// set demo configuration
		unsigned long val = extract_val(argv[1]);	// extract numeric value

		if ((val < 1) || (val > 3)) {
			print_unknown_arg(argv[1]);
			return -1;
		}

		set_demo(val);
		printf("selecting demo %d\n", get_demo());

	} else {
		print_unknown_cmd(argv[0]);
		return -1;
	}
	return 0;
}


// specify shell commands
wsh_cmd_t shell_commands[] = {
	{"rd", wsh_cmd_rd},
	{"wr", wsh_cmd_wr},
	{"demo", my_cmd_demo},
	{"history", wsh_cmd_history},
	{"clear", wsh_cmd_clear},
	{"quit", wsh_cmd_quit},
	{"help", wsh_cmd_help},
	{0, 0},			// must be the last entry
};

wsh_cmd_t *wsh_cmds = shell_commands;
