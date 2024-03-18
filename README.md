# minishell

A partial recreating of the bash shell, written in C. This was a group project done at Hive Helsinki with [taoramo](https://github.com/taoramo).

### Installing

Clone the repository and `make`.

The readline library must be installed and its location correctly defined in the Makefile file (includes and readline variables).

### Running

The shell can be ran in interactive mode:

`./minishell`

or with single commands:

`./minishell -c [command]`

### Implemented functionality

- Run any executables based on the environment variable PATH, an absolute path, or a relative path.
- Expands environment variables ($ VAR_NAME), exit status ($?), and wildcards (*).
- Handles single and double quotes, with only the meta-character '$' being interpreted in double quotes.
- Redirections >, <, >>, and <<, with the ability to redirect from the given fd (e.g. 2>out).
- Command piping with |.
- && and || for linking multiple commands.
- ctrl-C, ctrl-D and ctrl-\
- A memory of commands run in the interactive shell.
- Built ins:
   - echo with option -n
   - cd with only a relative or absolute path
   - pwd with no options
   - export with no options
   - unset with no options
   - env with no options or arguments
   - exit with no options
