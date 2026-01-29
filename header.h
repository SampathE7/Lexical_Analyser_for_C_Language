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

static char* oper1[] = {"||", "&&", "<=", ">=", "==", "!=", "->", "++", "--", "-=", "+=", "*=", "/=", "|=", "&=", ">>", "<<", ">>=", "<<=", "%="};

void tokenize(FILE *);

#endif

