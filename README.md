# Minishell

A custom Unix shell implementation built in C as part of the 42 School curriculum. This project recreates basic shell functionality with proper memory management, signal handling, and full compliance with 42 coding standards (norminette).

## Features

### Core Shell Functionality
- **Interactive Command Line**: Readline integration with history support
- **Command Execution**: Execute system commands with PATH resolution
- **Pipeline Support**: Handle command chaining with pipes (`|`)
- **Redirection**: Input/output redirection (`<`, `>`, `>>`)
- **Quote Handling**: Proper parsing of single and double quotes
- **Variable Expansion**: Environment variable expansion (`$VAR`)
- **Signal Handling**: Graceful handling of SIGINT and SIGTERM

### Built-in Commands
- `echo` - Display text (with `-n` option support)
- `cd` - Change directory
- `pwd` - Print working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display environment variables
- `exit` - Exit shell with status code

### Advanced Features
- **Context-Based Garbage Collector**: Automatic memory management with cleanup
- **Error Handling**: Comprehensive error checking and reporting
- **Memory Safety**: No memory leaks, proper resource cleanup
- **42 Standards Compliant**: Full norminette compliance

## Architecture

### Core Components

#### Memory Management
The project implements a custom garbage collector integrated into the main shell context:
```c
typedef struct s_minishell {
    char         **env;      // Environment variables
    int          last_exit;  // Last command exit status
    t_simple_gc  gc;        // Garbage collector state
} t_minishell;
```

#### Tokenization & Parsing
- **Lexical Analysis**: Token-based parsing with quote and operator recognition
- **AST Generation**: Abstract syntax tree for command structure
- **Expansion**: Variable and quote expansion before execution

#### Execution Engine
- **Built-in Detection**: Identify and execute built-in commands
- **Process Management**: Fork and execute external commands
- **Pipeline Handling**: Multi-command pipeline execution

## Installation

### Prerequisites
- GCC compiler
- GNU Make
- Readline library development files

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/ElieBalaa/Minishell.git
cd Minishell

# Compile the project
make

# Run the shell
./minishell
```

### Clean Build
```bash
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Clean rebuild
```

## Usage

### Basic Commands
```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> pwd
/current/working/directory

minishell> export MY_VAR="test"
minishell> echo $MY_VAR
test
```

### Pipeline Example
```bash
minishell> ls -la | grep ".c" | wc -l
```

### Redirection Example
```bash
minishell> echo "output" > file.txt
minishell> cat < file.txt
output
```

## Project Structure

```
├── src/
│   ├── builtins/          # Built-in command implementations
│   ├── execution/         # Command execution engine
│   ├── gc/               # Garbage collector system
│   └── tokenizer/        # Parsing and tokenization
├── includes/             # Header files
├── libft/               # Custom C library
├── Makefile             # Build configuration
└── README.md           # Project documentation
```

## Technical Implementation

### Garbage Collector
The project features a context-based garbage collector that:
- Tracks all dynamic allocations in a linked list
- Provides automatic cleanup on command completion
- Handles emergency cleanup during signal interruption
- Eliminates memory leaks through systematic resource management

### Signal Handling
- **SIGINT (Ctrl+C)**: Interrupt current command, display new prompt
- **SIGTERM**: Graceful shutdown with cleanup
- **Signal Safety**: Proper cleanup of resources during interruption

### Memory Safety
- All allocations tracked and freed
- No global variables (except for signal handling)
- Proper error handling for allocation failures
- Valgrind clean execution

## Standards Compliance

### 42 Norminette
The project achieves full compliance with 42 coding standards:
- Maximum 25 lines per function
- Maximum 4 parameters per function
- Maximum 5 functions per file
- Snake_case naming convention
- Proper indentation with tabs
- No forbidden constructs

### Code Quality
- Comprehensive error handling
- Modular architecture
- Clear separation of concerns
- Extensive documentation

## Testing

### Manual Testing
```bash
# Test basic functionality
echo "test" | ./minishell

# Test built-ins
./minishell
minishell> echo -n "no newline"
minishell> cd /tmp && pwd
minishell> exit 42
```

### Memory Testing
```bash
# Check for memory leaks
valgrind --leak-check=full ./minishell
```

## Development Status

### Completed Features ✅
- [x] Task 1: Garbage Collector Refactoring
- [x] Context-based memory management
- [x] Full norminette compliance
- [x] All built-in commands
- [x] Pipeline and redirection support
- [x] Signal handling
- [x] Environment variable management

### Future Enhancements
- [ ] Here-document support (`<<`)
- [ ] Advanced scripting features
- [ ] Job control
- [ ] Command history persistence

## Contributors

- **ElieBalaa** - Core implementation and architecture
- **Omar Iskandarani** - Development and implementation
- **42 School** - Project specifications and requirements

## License

This project is part of the 42 School curriculum and follows the school's academic guidelines.

---

**Note**: This implementation is designed for educational purposes as part of the 42 School curriculum. It demonstrates systems programming concepts including process management, memory allocation, signal handling, and Unix shell architecture. 