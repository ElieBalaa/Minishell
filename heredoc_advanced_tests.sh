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

# 11. Heredoc with newlines in delimiter
run_test "Newlines in delimiter" 'cat << "END
"
hello
END
'

# 12. Heredoc with spaces in delimiter
run_test "Spaces in delimiter" 'cat << "END OF DOC"
hello
END OF DOC'

# 13. Heredoc with tabs
run_test "Tabs in heredoc" 'cat << EOF
line1	tabbed
line2	more	tabs
EOF'

# 14. Heredoc with backslashes
run_test "Backslashes in heredoc" 'cat << EOF
line1\\
line2\\\\
EOF'

# 15. Heredoc with quotes
run_test "Quotes in heredoc" 'cat << EOF
"quoted text"
'"'"'single quoted'"'"'
EOF'

# 16. Heredoc with command substitution (bash only)
run_test "Command substitution in heredoc" 'cat << EOF
$(echo "command output")
EOF'

# 17. Heredoc with arithmetic expansion (bash only)
run_test "Arithmetic expansion in heredoc" 'cat << EOF
$((2 + 2))
EOF'

# 18. Heredoc with parameter expansion (bash only)
run_test "Parameter expansion in heredoc" 'cat << EOF
${VAR:-default}
EOF'

# 19. Heredoc with here-string
run_test "Here-string comparison" 'cat <<< "hello world"'

# 20. Heredoc with process substitution (bash only)
run_test "Process substitution" 'cat <(echo "hello")'

# 21. Heredoc with multiple redirections
run_test "Multiple redirections" 'cat << EOF 2>&1
error and output
EOF'

# 22. Heredoc with exec
run_test "Exec with heredoc" 'exec cat << EOF
exec test
EOF'

# 23. Heredoc with function
run_test "Function with heredoc" 'test_func() {
    cat << EOF
function heredoc
EOF
}
test_func'

# 24. Heredoc with subshell
run_test "Subshell with heredoc" '(cat << EOF
subshell heredoc
EOF)'

# 25. Heredoc with background process
run_test "Background heredoc" 'cat << EOF &
background test
EOF' 