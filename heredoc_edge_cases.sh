#!/bin/bash

MINISHELL=./minishell
BASH=/bin/bash

run_test() {
    desc="$1"
    cmd="$2"
    echo "\n===== $desc ====="
    echo "--- minishell ---"
    echo -e "$cmd" | $MINISHELL
    echo "--- bash ---"
    echo -e "$cmd" | $BASH
}

# 1. Empty heredoc
run_test "Empty heredoc" 'cat << EOF
EOF'

# 2. Heredoc with only delimiter
run_test "Only delimiter" 'cat << END
END'

# 3. Heredoc with special characters
run_test "Special characters" 'cat << DELIM
!@#$%^&*()_+
[]{};:,.<>/?\|`~
DELIM'

# 4. Heredoc with variable expansion
run_test "Variable expansion" 'VAR=hello
cat << DELIM
$VAR
DELIM'

# 5. Heredoc with quoted delimiter (no expansion)
run_test "Quoted delimiter (no expansion)" 'VAR=hello
cat << "DELIM"
$VAR
DELIM'

# 6. Multiple heredocs in one command
run_test "Multiple heredocs" 'cat << A && cat << B
foo
A
bar
B'

# 7. Heredoc with redirections
run_test "Heredoc with redirection" 'cat << END > heredoc_out.txt
file output
END
cat heredoc_out.txt
rm -f heredoc_out.txt'

# 8. Heredoc with pipes
run_test "Heredoc with pipe" 'cat << END | grep foo
foo
bar
END'

# 9. Heredoc with missing delimiter
run_test "Missing delimiter" 'cat << END
foo
bar'

# 10. Heredoc with EOF in the middle
run_test "EOF in the middle" 'cat << END
foo
bar
EOF
END' 