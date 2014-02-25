#ifndef COMMANDS_H

#define COMMANDS_H

struct command {
	const char *name;
	int (*function)(const int, const char **);
};

extern int run_command(const char *command_name, const int argc, const char **argv);

extern bool is_command(const char *command_name);

#endif