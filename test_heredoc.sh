#!/bin/bash

echo "Testing heredoc functionality..."

echo "Test 1: Basic heredoc with cat"
echo 'cat << EOF
hello
world
EOF' | ./minishell

echo -e "\nTest 2: Heredoc with echo"
echo 'echo "Testing heredoc:" && cat << DELIM
line1
line2
line3
DELIM' | ./minishell

echo -e "\nTest 3: Heredoc with wc -l"
echo 'wc -l << COUNT
one
two
three
COUNT' | ./minishell

echo -e "\nTest 4: Heredoc with grep"
echo 'grep "hello" << SEARCH
hello world
goodbye world
hello again
SEARCH' | ./minishell 