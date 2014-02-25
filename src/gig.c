#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "commands.h"

const char version[] = "0.0.1";

const char usage_string[] =
	"gig [--version] <command> [<arguments>]";


char *shift_args(int *argc, char ***argv) {
	char *shifted_arg = **argv;

	(*argc)--;
	(*argv)++;

	return shifted_arg;
}

static struct command commands[] = {

};

int run_command(const char *command_name, const int argc, const char **argv) {
	int commands_length = sizeof(commands) / sizeof(commands[0]);

	int i;
	for (i = 0; i < commands_length; i++) {
		struct command *cmd = commands + i;

		if (!strcmp(command_name, cmd->name)) {
			return cmd->function(argc, argv);
		}
	}

	return -1;
}

bool is_command(const char *command_name) {
	int commands_length = sizeof(commands) / sizeof(commands[0]);

	int i;
	for (i = 0; i < commands_length; i++) {
		struct command *cmd = commands + i;

		if (!strcmp(command_name, cmd->name)) {
			return true;
		}
	}

	return false;
}

int main(int argc, char **argv) {
	// Pop the first argument as it's the binary name
	char *binary_name = shift_args(&argc, &argv);

	char *argument;

	while ((argument = shift_args(&argc, &argv)) != NULL) {
		if (argument[0] != '-') {
			break;
		}

		if (!strcmp(argument, "--version")) {
			printf("%s: version %s\n", binary_name, version);
			return 0;
		}

		if (!strcmp(argument, "--help") || !strcmp(argument, "-h")) {
			return run_command("help", argc, (const char**) argv);
		}
	}

	char *command_name = argument;

	if (command_name != NULL && is_command(command_name)) {
		return run_command(command_name, argc, (const char**) argv);
	} else {
		// There wasn't a command passed
		printf("%s\n", usage_string);
		return 1;
	}
}
