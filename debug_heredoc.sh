#!/bin/bash

echo "=== Debug Heredoc Test ==="

echo "Test 1: Simple cat with heredoc"
echo 'cat << EOF
test line 1
test line 2
EOF' | ./minishell

echo -e "\nTest 2: Echo with heredoc"
echo 'echo "start" && cat << TEST
line1
line2
TEST' | ./minishell

echo -e "\nTest 3: Just heredoc content"
echo 'cat << HERE
content
HERE' | ./minishell 