*This project has been created as part of the 42 curriculum by jinliang, potabaga*

# Minishell

## Description
Minishell is a simplified bash-like shell that parses user input, handles quoting, environment expansion, redirections, pipes, signals, and built-in commands, using only allowed system calls and strict subject constraints.

### GOAL
Implement a basic UNIX shell that behaves like bash for all required features.

### Features

- Command Execution: Run executables from absolute, relative, or PATH-based paths

- Built-in Commands:
 Implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

- Redirections: Support for `<`, `>`, `>>` with proper file descriptor management

- Pipes: Handle multiple commands connected with `|`

- Environment Variables: Expand `$VAR` and `$?` for exit status

- Quotes Handling: Support for single quotes `'` (no expansion) and double quotes `"` (expansion)

- Signal Handling: Graceful handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`

- Error Management: Informative error messages without crashing

## Instructions



#### Compile the project:

```bash
make
```
#### Start the shell by running:
```bash
./minishell
```
#### Enter commandes in prompt
```text
minishell$> echo "Hello World"
```
#### Exit the shell
```text
minishell$> exit
```
or by pressing `Ctrl-D`

#### Cleaning
```bash
make clean 		# Remove object files
make fclean		# Remove object files and executable
make re			# Recompile from scratch
```

### Project Structure
```text
Lexer → Expander → Parser → Executor
```


## Resources 
### Official Documentation
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
### Tutorials & Articles
- [Writing a Simple Shell in C](https://www.geeksforgeeks.org/c/making-linux-shell-c/)

### Requirements
- Compiler: `gcc` / `clang`
- Build Tool: `Make`
- Dependencies: 
	- libft

### AI Usage
During the development of this project, AI tools (ChatGPT and Deepseek) were used for:
- Debugging assistance: Identifying and fixing segmentation faults and memory leaks

- Concept clarification: Understanding complex topics like process forking and file descriptor inheritance

- Code optimization: Refactoring repetitive code and improving error handling

- Documentation: Generating comments and this README structure

All AI-generated code was reviewed, tested, and modified as needed to ensure compliance with the 42 Norm and project requirements.

## Known Limitations
- No logical operators (&&, ||) i.e., no bonus

## Author
GitHub: [@jinlng](https://github.com/jinlng) & [@tabagary](https://github.com/tabagary)