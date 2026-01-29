/*
This project implements a Lexical Analyzer (Tokenizer) for the C programming language.
The lexical analyzer reads a C source file character by character and converts it into a sequence of tokens such as:
 -Keywords
 -Identifiers
 -Numbers (integer & floating-point)
 -Operators (single and multi-character)
 -Symbols
 -String literals
It also ignores comments and preprocessor directives, as they are not required for syntax analysis.*/

#include "header.h"

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Usage: %s <program.c\n",argv[0]);
		return 0;
	}

	char* dot = strrchr(argv[1], '.');
	if(!dot || strcmp(dot, ".c") != 0){
		printf("Error: File has no extension(.c)\n");
		return 0;
	}

	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("Error: File is not present\n");
		return 0;
	}

	tokenize(fp);
	fclose(fp);
	return 0;
}


/* 
	cmd1: gcc main.c helper.c -o lex
	cmd2:./lex sample.c
*/

