#include "header.h"	
#define BUF_SIZE 256  //max size for token buffer


/*checks whether given string is valid number or not
 *supports for int and floating-point numbers*/
int isNumber(const char *s){
	int dot = 0;  //to ensure only one decimal point
	for(int i=0; s[i]; i++){
		if(s[i] == '.'){
			if(dot)
				return 0;
			dot = 1;
		}
		else if(!isdigit(s[i])){
			return 0;
		}
	}
	return 1;
}

//check keyword
int isKeyword(const char* word)
{
	for(int i=0; i<sizeof(res_kwords_data)/sizeof(res_kwords_data[0]); i++){
		if(strcmp(word, res_kwords_data[i])==0)
			return 1;
	}

	for(int j=0; j< sizeof(res_kwords_non_data)/sizeof(res_kwords_non_data[0]); j++){
                if(strcmp(word, res_kwords_non_data[j])==0)
                        return 1;
        }
	return 0;
}

//check single-char symbol
int isSymbol(char c){
	for(int i=0; i<sizeof(symbols)/sizeof(symbols[0]); i++){
		if(c == symbols[i])
			return 1;
	}
	return 0;
}

//check single-char operator
int isOperator(char c){
	for(int i=0; i<sizeof(operators)/sizeof(operators[0]); i++){
		if(c == operators[i])
			return 1;
	}
	return 0;
}

//check multi-char operator
int isMultiOp(const char* s){
	for(int i=0; i<sizeof(oper1)/sizeof(oper1[0]); i++){
		if(strcmp(s,oper1[i]) ==0)
			return 1;
	}
	return 0;
}

//process buffer (after hitting delimiter)
void processBuffer(char* buffer){
	if( *buffer == '\0')
		return;
	if(isKeyword(buffer))
		printf("%-12s %s\n", "KEYWORD     :", buffer);
	else if(isNumber(buffer))
		printf("%-12s %s\n", "NUMBER	    :", buffer);
	else
		printf("%-12s %s\n", "IDENTIFIER  :", buffer);
	
	buffer[0] = '\0'; //reset buffer after processing
}

/* main tokenizer
 * Reads characters from source file and identifies tokens */
void tokenize(FILE *fp){
	char c;
	char buffer[BUF_SIZE] = "";
	int i=0;

	while( (c = fgetc(fp)) != EOF)
	{

		//skips preprocessor directive
		if(c == '#'){
			while((c = fgetc(fp)) != '\n' && c!= EOF);
			continue;
		}

		//handles comment
		if(c == '/'){
			char next = fgetc(fp);

			//Single-line comment
			if(next == '/'){
				while( (c = fgetc(fp))!= '\n' && c != EOF );
				continue;
			}
			
			//multi-line comments
			if(next == '*'){
				char prev = 0;
				while( (c = fgetc(fp)) != EOF){
					if(prev == '*' && c== '/')
						break;
					prev = c;
				}
				continue;
			}
			ungetc(next, fp);
		}

		//handling string-literal
		if(c == '"'){
			processBuffer(buffer);
			i=0;

			char str[256];
			int si=0;
			while((c=fgetc(fp)) != '"' && c!=EOF){
				if( si < sizeof(str)-1)
					str[si++] = c;
			}
			str[si] = '\0';
			printf("%-12s \"%s\"\n","STRING      :",str);
			continue;
		}
		
		
		//if whitespace -> process buffer
		if(isspace(c)){
			processBuffer(buffer);
			i=0;
			continue;
		}

		//Check multi-cha operator
		if(isOperator(c)){
			buffer[i] = '\0';
			processBuffer(buffer);
			i=0;

			char next = fgetc(fp);
			char op[3] = {c,next,'\0'};
			
			if(isMultiOp(op))
				printf("%-12s %s\n", "OPERATOR    :", op);
			else{
				ungetc(next, fp);
				printf("%-12s %c\n", "OPERATOR    :", c);
			}
			continue;
		}

		//check symbols
		if(isSymbol(c)){
			processBuffer(buffer);
			i=0;
			printf("%-12s %c\n","SYMBOL      :", c);
			continue;
		}

		//accumulate in buffer
		if(i < BUF_SIZE-1){
			buffer[i++] = c;
			buffer[i] = '\0';
		}
	}

	//Last token(if file doesn't end with space)
	processBuffer(buffer);
}
