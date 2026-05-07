#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

static const char* res_kwords_data[] = {"const","volatile","extern","auto","register","static","signed","unsigned",
					"long", "short","double","int","char","float","struct","union","enum","void","typedef"};

static const char* res_kwords_non_data[] = {"goto", "return", "continue", "break", "if", "else", "for", "while", "do",
						"switch","case","default","sizeof"};

static const char operators[] = {'/', '+', '-', '*', '%', '=', '<','>','~','&',',','!','^','|', '?','.'};

static const char symbols[] = {'{','}','[',']','(',')',';',':'};

static const char* oper1[] = {"||", "&&", "<=", ">=", "==", "!=", "->", "++", "--", "-=", "+=", "*=", "/=", "|=", "&=", ">>", "<<", ">>=", "<<=", "%="};

void tokenize(FILE *fp, const char *filename);



#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define LIGHT_YELLOW "\033[93m"
#define BRIGHT_RED   "\033[91m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_WHITE "\033[97m"
#define LIGHT_CYAN   "\033[96m"
#define ORANGE "\033[38;5;208m"

#endif

