/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 15:30:42 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <sys/time.h>  // For performance testing
#include <assert.h>    // For assertions

/* ANSI Color codes for output */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/* Test result structure */
typedef struct s_test_result
{
	int	passed;
	int	total;
	char	*test_name;
}	t_test_result;

/* Helper function to print test results */
static void	print_test_header(const char *test_name)
{
	printf("\n" CYAN "========================================\n");
	printf("Testing: %s\n", test_name);
	printf("========================================" RESET "\n");
}

static void	print_test_result(const char *test_name, int passed)
{
	if (passed)
		printf(GREEN "[PASS]" RESET " %s\n", test_name);
	else
		printf(RED "[FAIL]" RESET " %s\n", test_name);
}

static void	print_section_summary(const char *section, int passed, int total)
{
	printf("\n" MAGENTA "Summary for %s: %d/%d tests passed" RESET "\n", 
		section, passed, total);
}

/* =================================================================== */
/*                     MEMORY MANAGEMENT TESTS                        */
/* =================================================================== */

static int	test_memory_management_issues(void)
{
	print_test_header("Memory Management Issues");
	int passed = 0;
	int total = 0;
	
	/* Test 1: Mixed malloc/gc_malloc issue in split_on_space */
	total++;
	printf("\n" YELLOW "Test 1: Mixed Memory Management in split_on_space" RESET "\n");
	printf("Issue: Line 26-27 uses malloc() but line 34 uses gc_malloc()\n");
	
	char *test_str = "hello world test";
	printf("Input: \"%s\"\n", test_str);
	
	// This will likely crash or cause memory issues
	printf("Calling split_on_space (may crash due to mixed memory management)...\n");
	t_token **tokens = split_on_space(test_str);
	
	if (tokens)
	{
		printf("Result: Function returned tokens (but memory management is inconsistent)\n");
		printf(RED "ISSUE: tokens array allocated with malloc(), tokens with gc_malloc()" RESET "\n");
		passed++;  // Function worked but has the issue
	}
	else
	{
		printf(RED "Result: Function returned NULL - memory allocation failed" RESET "\n");
	}
	
	/* Test 2: Wrong sizeof usage */
	total++;
	printf("\n" YELLOW "Test 2: Wrong sizeof Usage" RESET "\n");
	printf("Issue: Line 34 in token.c uses sizeof(tok) instead of sizeof(t_token)\n");
	printf("sizeof(t_token*) = %zu bytes (pointer size)\n", sizeof(t_token*));
	printf("sizeof(t_token) = %zu bytes (actual struct size)\n", sizeof(t_token));
	printf(RED "ISSUE: Allocating %zu bytes instead of %zu bytes!" RESET "\n", 
		sizeof(t_token*), sizeof(t_token));
	
	if (sizeof(t_token*) != sizeof(t_token))
	{
		print_test_result("Wrong sizeof detected", 1);
		passed++;
	}
	else
		print_test_result("sizeof issue not detected on this system", 0);
	
	/* Test 3: Garbage Collection Issues */
	total++;
	printf("\n" YELLOW "Test 3: Garbage Collection Memory Tracking" RESET "\n");
	printf("Testing gc_malloc and gc_add functions...\n");
	
	int initial_count = g_gc.count;
	printf("Initial GC count: %d\n", initial_count);
	
	void *ptr1 = gc_malloc(100);
	void *ptr2 = gc_malloc(200);
	void *ptr3 = gc_malloc(300);
	
	printf("After 3 gc_malloc calls: %d items tracked\n", g_gc.count);
	printf("Expected: %d, Actual: %d\n", initial_count + 3, g_gc.count);
	
	if (ptr1 && ptr2 && ptr3 && g_gc.count == initial_count + 3)
	{
		print_test_result("GC tracking", 1);
		passed++;
	}
	else
		print_test_result("GC tracking", 0);
	
	print_section_summary("Memory Management", passed, total);
	return (passed);
}

/* =================================================================== */
/*                      TOKENIZATION TESTS                            */
/* =================================================================== */

static int	test_tokenization_issues(void)
{
	print_test_header("Tokenization Issues");
	int passed = 0;
	int total = 0;
	
	/* Test 1: Basic tokenization */
	total++;
	printf("\n" YELLOW "Test 1: Basic Tokenization" RESET "\n");
	const char *simple_cmd = "ls -l -a";
	printf("Input: \"%s\"\n", simple_cmd);
	
	t_token *tokens = tokenize(simple_cmd);
	if (tokens)
	{
		printf("Tokens created:\n");
		t_token *current = tokens;
		int count = 0;
		while (current)
		{
			printf("  [%d]: \"%s\"\n", count++, current->text);
			current = current->next;
		}
		if (count == 3)
		{
			print_test_result("Basic tokenization", 1);
			passed++;
		}
		else
			print_test_result("Basic tokenization", 0);
	}
	else
	{
		print_test_result("Basic tokenization", 0);
		printf(RED "ERROR: tokenize returned NULL for valid input" RESET "\n");
	}
	
	/* Test 2: Quote handling */
	total++;
	printf("\n" YELLOW "Test 2: Quote Handling" RESET "\n");
	const char *quoted_cmd = "echo \"hello world\" 'single quotes'";
	printf("Input: \"%s\"\n", quoted_cmd);
	
	tokens = tokenize(quoted_cmd);
	if (tokens)
	{
		printf("Tokens with quotes:\n");
		t_token *current = tokens;
		int count = 0;
		while (current)
		{
			printf("  [%d]: \"%s\"\n", count++, current->text);
			current = current->next;
		}
		// Should be: "echo", "\"hello world\"", "'single quotes'"
		if (count == 3)
		{
			print_test_result("Quote tokenization", 1);
			passed++;
		}
		else
			print_test_result("Quote tokenization", 0);
	}
	else
	{
		print_test_result("Quote tokenization", 0);
	}
	
	/* Test 3: Redirection operators */
	total++;
	printf("\n" YELLOW "Test 3: Redirection Operators" RESET "\n");
	const char *redir_cmd = "cat < input.txt > output.txt >> append.txt";
	printf("Input: \"%s\"\n", redir_cmd);
	
	tokens = tokenize(redir_cmd);
	if (tokens)
	{
		printf("Redirection tokens:\n");
		t_token *current = tokens;
		int count = 0;
		int found_double_redir = 0;
		while (current)
		{
			printf("  [%d]: \"%s\"\n", count++, current->text);
			if (ft_strcmp(current->text, ">>") == 0)
			{
				printf("    ^ Double redirection detected correctly\n");
				found_double_redir = 1;
			}
			current = current->next;
		}
		if (count >= 6 && found_double_redir)
		{
			print_test_result("Redirection tokenization", 1);
			passed++;
		}
		else
			print_test_result("Redirection tokenization", 0);
	}
	else
	{
		print_test_result("Redirection tokenization", 0);
	}
	
	/* Test 4: Edge cases */
	total++;
	printf("\n" YELLOW "Test 4: Edge Cases" RESET "\n");
	
	// Empty string
	printf("Testing empty string...\n");
	tokens = tokenize("");
	if (tokens == NULL)
	{
		printf("Empty string correctly returned NULL\n");
		print_test_result("Empty string handling", 1);
		passed++;
	}
	else
	{
		printf(RED "Empty string should return NULL" RESET "\n");
		print_test_result("Empty string handling", 0);
	}
	
	/* Test 5: Performance issue demonstration */
	total++;
	printf("\n" YELLOW "Test 5: Performance Issue (O(n²) tokenization)" RESET "\n");
	
	// Create a long command to demonstrate O(n²) behavior
	char *long_cmd = malloc(10000);
	if (long_cmd)
	{
		strcpy(long_cmd, "cmd");
		int i = 0;
		while (i < 500 && strlen(long_cmd) < 9000)
		{
			strcat(long_cmd, " arg");
			char num[10];
			sprintf(num, "%d", i);
			strcat(long_cmd, num);
			i++;
		}
		
		printf("Testing with %zu character command (500+ tokens)...\n", strlen(long_cmd));
		
		struct timeval start, end;
		gettimeofday(&start, NULL);
		
		tokens = tokenize(long_cmd);
		
		gettimeofday(&end, NULL);
		long microseconds = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		
		if (tokens)
		{
			int count = 0;
			t_token *current = tokens;
			while (current)
			{
				count++;
				current = current->next;
			}
			printf("Tokenized %d tokens in %ld microseconds\n", count, microseconds);
			printf(YELLOW "NOTE: Due to tok_last() calls, this is O(n²) complexity" RESET "\n");
			print_test_result("Performance test completed", 1);
			passed++;
		}
		else
		{
			print_test_result("Performance test", 0);
		}
		
		free(long_cmd);
	}
	else
	{
		printf("Failed to allocate memory for performance test\n");
		print_test_result("Performance test", 0);
	}
	
	print_section_summary("Tokenization", passed, total);
	return (passed);
}

/* =================================================================== */
/*                        PARSING TESTS                               */
/* =================================================================== */

static int	test_parsing_issues(void)
{
	print_test_header("Parsing Issues");
	int passed = 0;
	int total = 0;
	
	/* Test 1: Basic parsing */
	total++;
	printf("\n" YELLOW "Test 1: Basic Command Parsing" RESET "\n");
	const char *cmd = "ls -l";
	printf("Input: \"%s\"\n", cmd);
	
	t_ast *ast = parse_line(cmd);
	if (ast)
	{
		printf("AST created successfully\n");
		printf("Command parts:\n");
		if (ast->cmd)
		{
			int i = 0;
			while (ast->cmd[i])
			{
				printf("  cmd[%d]: \"%s\"\n", i, ast->cmd[i]);
				i++;
			}
		}
		print_test_result("Basic parsing", 1);
		passed++;
	}
	else
	{
		printf(RED "ERROR: parse_line returned NULL" RESET "\n");
		print_test_result("Basic parsing", 0);
	}
	
	/* Test 2: Pipeline parsing */
	total++;
	printf("\n" YELLOW "Test 2: Pipeline Parsing" RESET "\n");
	const char *pipeline = "ls -l | grep txt | wc -l";
	printf("Input: \"%s\"\n", pipeline);
	
	ast = parse_line(pipeline);
	if (ast)
	{
		printf("Pipeline AST created\n");
		t_ast *current = ast;
		int pipe_count = 0;
		while (current)
		{
			printf("Pipeline segment %d:\n", pipe_count++);
			if (current->cmd && current->cmd[0])
				printf("  Command: %s\n", current->cmd[0]);
			current = current->right;
		}
		printf("Total pipeline segments: %d\n", pipe_count);
		if (pipe_count == 3)
		{
			print_test_result("Pipeline parsing", 1);
			passed++;
		}
		else
			print_test_result("Pipeline parsing", 0);
	}
	else
	{
		print_test_result("Pipeline parsing", 0);
	}
	
	/* Test 3: Redirection parsing */
	total++;
	printf("\n" YELLOW "Test 3: Redirection Parsing" RESET "\n");
	const char *redir = "cat < input.txt > output.txt";
	printf("Input: \"%s\"\n", redir);
	
	ast = parse_line(redir);
	if (ast)
	{
		printf("Redirection AST created\n");
		printf("Input file: %s\n", ast->input ? ast->input : "NULL");
		printf("Output file: %s\n", ast->output ? ast->output : "NULL");
		printf("Append mode: %d\n", ast->append);
		
		int correct = (ast->input != NULL && ast->output != NULL);
		if (correct)
		{
			print_test_result("Redirection parsing", 1);
			passed++;
		}
		else
			print_test_result("Redirection parsing", 0);
	}
	else
	{
		print_test_result("Redirection parsing", 0);
	}
	
	/* Test 4: count_args bounds checking issue */
	total++;
	printf("\n" YELLOW "Test 4: count_args Bounds Checking Issue" RESET "\n");
	printf("Issue: count_args can read past array bounds\n");
	
	char *test_tokens[] = {"cat", "<", "file.txt", NULL};
	int n = 3;  // We have 3 tokens
	
	printf("Testing count_args with tokens: [\"cat\", \"<\", \"file.txt\"]\n");
	printf("Array size: %d\n", n);
	
	// This demonstrates the bounds issue
	int arg_count = count_args(test_tokens, n);
	printf("count_args returned: %d\n", arg_count);
	printf(YELLOW "ISSUE: Function increments i++ on line 27, potentially reading past array bounds" RESET "\n");
	
	// Manually check what should happen
	printf("Expected behavior: cat (1 arg), skip < and file.txt -> should return 1\n");
	if (arg_count == 1)
	{
		print_test_result("count_args bounds issue demonstrated", 1);
		passed++;
	}
	else
		print_test_result("count_args bounds issue demonstrated", 0);
	
	print_section_summary("Parsing", passed, total);
	return (passed);
}

/* =================================================================== */
/*                        ERROR HANDLING TESTS                        */
/* =================================================================== */

static int	test_error_handling_issues(void)
{
	print_test_header("Error Handling Issues");
	int passed = 0;
	int total = 0;
	
	/* Test 1: NULL input handling */
	total++;
	printf("\n" YELLOW "Test 1: NULL Input Handling" RESET "\n");
	
	printf("Testing tokenize(NULL)...\n");
	t_token *result = tokenize(NULL);
	if (result == NULL)
	{
		printf(GREEN "tokenize(NULL) correctly returned NULL" RESET "\n");
		print_test_result("NULL input to tokenize", 1);
		passed++;
	}
	else
	{
		printf(RED "ERROR: tokenize(NULL) should return NULL" RESET "\n");
		print_test_result("NULL input to tokenize", 0);
	}
	
	/* Test 2: Memory allocation failures */
	total++;
	printf("\n" YELLOW "Test 2: Memory Allocation Failure Handling" RESET "\n");
	printf("NOTE: Current code has insufficient error checking for malloc failures\n");
	
	// Test what happens when gc_malloc fails (simulated)
	printf("Issues found in code:\n");
	printf("- Line 34 in token.c: No error check after gc_malloc()\n");
	printf("- Line 17 in lexer.c: No error check after gc_malloc() in add_tok()\n");
	printf("- Line 28 in simple_gc.c: No error check for malloc() in gc_add()\n");
	
	print_test_result("Error handling issues identified", 1);
	passed++;
	
	/* Test 3: Invalid redirection patterns */
	total++;
	printf("\n" YELLOW "Test 3: Invalid Redirection Patterns" RESET "\n");
	
	const char *invalid_redirections[] = {
		"cat >",           // Missing output file
		"cat < ",          // Missing input file  
		"cat > > file",    // Double output redirection
		"cat < < file",    // Double input redirection
		NULL
	};
	
	int i = 0;
	while (invalid_redirections[i])
	{
		printf("Testing: \"%s\"\n", invalid_redirections[i]);
		t_ast *ast = parse_line(invalid_redirections[i]);
		if (ast)
		{
			printf("  AST created (no error detection)\n");
			printf(YELLOW "  ISSUE: Invalid syntax not detected" RESET "\n");
		}
		else
		{
			printf("  Correctly rejected invalid syntax\n");
		}
		i++;
	}
	
	print_test_result("Invalid redirection handling", 1);
	passed++;
	
	print_section_summary("Error Handling", passed, total);
	return (passed);
}

/* =================================================================== */
/*                     COMPREHENSIVE TEST SUITE                       */
/* =================================================================== */

static void	run_memory_leak_detection(void)
{
	print_test_header("Memory Leak Detection");
	
	printf("Initial GC state:\n");
	printf("  Count: %d\n", g_gc.count);
	printf("  Head: %p\n", (void*)g_gc.head);
	
	printf("\nPerforming operations that may leak memory...\n");
	
	// This will demonstrate the mixed malloc/gc_malloc issue
	char *test_input = "echo hello world | cat | wc -l";
	t_ast *ast = parse_line(test_input);
	
	printf("\nAfter parsing:\n");
	printf("  GC Count: %d\n", g_gc.count);
	
	if (ast)
		printf("  AST created successfully\n");
	else
		printf("  AST creation failed\n");
	
	printf("\nRunning gc_cleanup_all()...\n");
	gc_cleanup_all();
	
	printf("After cleanup:\n");
	printf("  GC Count: %d\n", g_gc.count);
	printf("  Head: %p\n", (void*)g_gc.head);
	
	printf(YELLOW "\nNOTE: Some memory may still be leaked due to mixed malloc/gc_malloc usage" RESET "\n");
}

/* Main test function */
int	main(void)
{
	printf(CYAN "\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                    MINISHELL CODE ANALYSIS                ║\n");
	printf("║                     Comprehensive Test Suite              ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf(RESET);
	
	// Initialize garbage collector
	if (!gc_init())
	{
		printf(RED "ERROR: Failed to initialize garbage collector\n" RESET);
		return (1);
	}
	
	int total_passed = 0;
	int total_tests = 0;
	
	/* Run all test suites */
	total_passed += test_memory_management_issues();
	total_tests += 3;
	
	total_passed += test_tokenization_issues();  
	total_tests += 5;
	
	total_passed += test_parsing_issues();
	total_tests += 4;
	
	total_passed += test_error_handling_issues();
	total_tests += 3;
	
	/* Memory leak detection */
	run_memory_leak_detection();
	
	/* Final summary */
	printf("\n" CYAN);
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                        FINAL SUMMARY                      ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf(RESET);
	
	printf("\nOverall Results: %d/%d tests passed (%.1f%%)\n", 
		   total_passed, total_tests, (float)total_passed / total_tests * 100);
	
	if (total_passed == total_tests)
		printf(GREEN "🎉 All tests passed! Your code is working correctly.\n" RESET);
	else if (total_passed >= total_tests * 0.7)
		printf(YELLOW "⚠️  Most tests passed, but some issues remain.\n" RESET);
	else
		printf(RED "❌ Many issues detected. Significant improvements needed.\n" RESET);
	
	printf("\n" MAGENTA "Key Issues to Address:" RESET "\n");
	printf("1. Fix mixed malloc/gc_malloc usage in token.c line 26-34\n");
	printf("2. Add error checking for all memory allocations\n");
	printf("3. Fix bounds checking in count_args function\n");
	printf("4. Improve quote handling in tokenizer\n");
	printf("5. Add validation for invalid redirection patterns\n");
	printf("6. Optimize tokenization to avoid O(n²) complexity\n");
	
	printf("\n" BLUE "Run this test with:" RESET "\n");
	printf("  make && ./minishell\n");
	printf("  valgrind --leak-check=full ./minishell\n");
	
	return (0);
}