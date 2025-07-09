#!/bin/bash

echo "=== Testing Nested Heredocs ==="

echo "Test 1: Simple nested heredoc"
echo 'cat << OUTER
outer line 1
cat << INNER
inner line 1
inner line 2
INNER
outer line 2
OUTER' | ./minishell

echo -e "\nTest 2: Nested heredoc with different delimiters"
echo 'cat << FIRST
first level
cat << SECOND
second level
cat << THIRD
third level
THIRD
SECOND
FIRST' | ./minishell

echo -e "\nTest 3: Heredoc with command inside"
echo 'cat << TEST
line 1
echo "inside heredoc"
line 2
TEST' | ./minishell

echo -e "\nTest 4: Multiple heredocs in sequence"
echo 'cat << A
content A
A && cat << B
content B
B' | ./minishell 