#include "header.h"	
#define BUF_SIZE 256  //max size for token buffer



/*checks whether given string is valid number or not
 *supports for int and floating-point numbers*/
int isNumber(const char *s, int line, int col, const char *filename, char *type)
{
	int dot = 0;  //to ensure only one decimal point
	int len = strlen(s);

	//Hexadecimal
	if(s[0]=='0' && (s[1]=='x' || s[1]=='X')){
		if(len <= 2){
			printf(RED "%s/%d:%d: Invalid Hexa-decimal constant\n" RESET,filename,line,col );
			exit(1);
		}
		for(int i=2; s[i]; i++){
			if(!isxdigit(s[i])){
				printf(RED"%s/%d:%d Invalid digit '%c' in hex constant\n"RESET, filename, line, col+i, s[i]);
				exit(1);
			}
		}
		strcpy(type, "HEXADECIMAL");
		return 1;
	}
	
	//octal
	if(s[0]=='0' && s[1] && isdigit(s[1])){
		for(int i=1; s[i]; i++){
			if(s[i]<'0' || s[i]>'7'){
				printf(RED "%s/%d:%d Invalid digit '%c' in octal constant\n" RESET, filename, line, col+i, s[i]);
			       	exit(1);
			}
		}
		strcpy(type, "OCTAL");
		return 1;
	}

	//binary
	if(s[0]=='0' && (s[1]=='b' || s[1] == 'B'))
	{
		if(len <= 2){
			printf(RED "%s/%d:%d: Invalid binary constant\n" RESET, filename, line, col);
		       	exit(1);
		}
		for(int i=2; s[i]; i++){
			if(s[i] != '0' && s[i] != '1'){
				printf(RED "%s/%d:%d: invalid digit '%c' in binary constant\n" RESET,filename, line, col+i, s[i]);
                		exit(1);
            		}
		}
		strcpy(type, "BINARY");
		return 1;
	}	
	
	//decimal or float
	int i=0;
	
	while(isdigit(s[i]))
		i++;
	
	/* optional fractional part */
	if(s[i] == '.'){
    		dot = 1;
    		i++;
    		while(isdigit(s[i]))
        		i++;
	}

	/* optional float suffix */
	if(s[i] == 'f' || s[i] == 'F' || s[i] == 'l' || s[i] == 'L')
    		i++;

	/* if anything remains → invalid */
	if(s[i] != '\0') {
    		printf(RED "%s/%d:%d: invalid numeric constant '%s'\n" RESET,filename, line, col, s);
    		exit(1);
	}

	if(dot)
                strcpy(type, "FLOAT");
        else
                strcpy(type, "DECIMAL");

	return 1;
}

//check datatype keywords
int isDatatype(const char *s)
{
    const char *types[] = {"int","float","double","char","long","short"};

    for(int i = 0; i < 6; i++){
        if(strcmp(s, types[i]) == 0)
            return 1;
    }
    return 0;
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
int isSymbol(char c)
{
	for(int i=0; i<sizeof(symbols)/sizeof(symbols[0]); i++){
		if(c == symbols[i])
			return 1;
	}
	return 0;
}


//check single-char operator
int isOperator(char c)
{
	for(int i = 0; i < sizeof(operators)/sizeof(operators[0]); i++){
        	if(c == operators[i])
            		return 1;
    	}
    	return 0;
}

//check multi-char operator 
int isMultiOp(const char* s)
{ 
	for(int i=0; i<sizeof(oper1)/sizeof(oper1[0]); i++)
	{ 
		if(strcmp(s,oper1[i]) ==0) 
			return 1; 
	} 
	return 0; 
}


//process buffer (after hitting delimiter)
void processBuffer(char* buffer, int line, int col, const char *filename, int *expecting_identifier, int *expect_semicolon, int *identifier_found)
{

	if(buffer[0] == '\0')
		return;
	
	/* ---------- KEYWORD ---------- */
	if(isKeyword(buffer)){
		/* if previous statement needed ';' but new keyword started */
        	if(*expect_semicolon){
                	printf(RED "%d:%d: Missing ';' before '%s'\n" RESET, line, col, buffer);
                	exit(1);
        	}
		
		printf(BLUE "%-15s" RESET " %s\n", "KEYWORD     :", buffer);
		
		if(isDatatype(buffer))
    			*expecting_identifier = 1;

		/* return requires semicolon */
               	if(strcmp(buffer,"return")==0)
                       	*expect_semicolon = 1;
	}

	/* ---------- NUMBER ---------- */
	else if(isdigit(buffer[0]) || (buffer[0]=='.' && isdigit(buffer[1]))){
		/* Reject mixed numeric tokens like 123abc */
                /*for(int i = 0; buffer[i]; i++){
                        if(!isdigit(buffer[i]) && buffer[i] != '.' && !(i > 1 && (buffer[1]=='x' || buffer[1]=='X' || buffer[1]=='b' || buffer[1]=='B')))
                        {
                                printf(RED "%d:%d: Invalid numeric constant '%s'\n" RESET,
                                       line, col, buffer);
                                exit(1);
                        }
                }*/

		/* If we were expecting an identifier → error */
        	if(*expecting_identifier){
                	printf(RED "%d:%d: Variable name cannot be a constant\n" RESET,line, col);
                	exit(1);
        	}

		char type[12];
		if(isNumber(buffer, line, col, filename, type))
			printf(GREEN "%-15s" RESET "%s(%s)\n", "NUMBER	    :", buffer, type);
	}
	
	/* ---------- IDENTIFIER ---------- */
	else if(isalpha(buffer[0]) || buffer[0] == '_'){
		/* Validate identifier characters */
                for(int i=0; buffer[i]; i++){
                        if(!isalnum(buffer[i]) && buffer[i] != '_'){
                                printf(RED "%d:%d: Invalid identifier '%s'\n" RESET, line, col, buffer);
                                exit(1);
                        }
                }

		printf(CYAN "%-15s" RESET " %s\n", "IDENTIFIER  :", buffer);
		
		if(*expecting_identifier){
			*expecting_identifier = 0;  /* variable name found */
			*expect_semicolon = 1;   // declaration must end with ;
		}
	}

	/* ---------- INVALID TOKEN ---------- */
	else{
		printf(RED "%d:%d: invalid token '%s'\n" RESET, line, col, buffer);
        	exit(1);
    	}
	
	buffer[0] = '\0'; //reset buffer after processing
}


/* main tokenizer
 * Reads characters from source file and identifies tokens */
void tokenize(FILE *fp, const char *filename)
{
	char c;
	char buffer[BUF_SIZE] = "";

	int i=0, line=1, col=0;
	int round = 0, square = 0, curly = 0;

	int token_start_col = 0;

	/* Syntax tracking flags */
        int expecting_identifier = 0;   // after type keyword
        int expect_semicolon = 0;       // after declaration/assignment
	int identifier_found = 0;

	while( (c = fgetc(fp)) != EOF)
	{
		col++;

		if(c == '\n'){
			processBuffer(buffer,line,col, filename, &expecting_identifier, &expect_semicolon, &identifier_found);
			line++;
			col =0;
			i=0;
			continue;
		}

		//skips preprocessor directive
		if(c == '#'){
			while((c = fgetc(fp)) != '\n' && c!= EOF);
			line++;
			col =0;
			continue;
		}

		// handles comments
		if(c == '/'){
    			char next = fgetc(fp);

    			// single-line comment
    			if(next == '/'){
        			while((c = fgetc(fp)) != '\n' && c != EOF);
        			line++;
        			col = 0;
        			continue;
    			}

    			//multi-line comment
    			if(next == '*'){
        			char prev = 0;
        			int closed = 0;

        			while((c = fgetc(fp)) != EOF){
            				if(c == '\n'){
                				line++;
                				col = 0;
            				}

            				if(prev == '*' && c == '/'){
                				closed = 1;
                				break;
            				}
            				prev = c;
        			}

        			if(!closed){
            				printf(RED "%d:%d: unterminated comment\n" RESET, line, col);
            				exit(1);
        			}
        			continue;
    			}

    			//not a comment → treat as operator
    			ungetc(next, fp);
		}

		//handling string-literal
		if(c == '"'){
			processBuffer(buffer, line, col, filename, &expecting_identifier, &expect_semicolon, &identifier_found);
			i=0;

			char str[256];
			int si=0;
			int start_col = col;

			while((c=fgetc(fp)) != '"') 
			{
				if( c == EOF || c == '\n'){
					printf(RED "%d:%d: missing terminating '\"' character\n" RESET, line, start_col);
            				exit(1);
        			}
				if( si < sizeof(str)-1 )
					str[si++] = c;
			}

			str[si] = '\0';
			printf(MAGENTA "%-15s" RESET " \"%s\"\n","STRING      :",str);
			continue;
		}
		
		//Bracket handling	
		if(isSymbol(c)){
			if(i>0){
				processBuffer(buffer, line, col, filename, &expecting_identifier, &expect_semicolon, &identifier_found);
				i=0;
			}

			/* function declaration like int main() */
    			/*if(c == '(' && expecting_identifier){
    				printf(RED "%d:%d: Missing function/variable name\n" RESET, line, col);
        			exit(1);
			}*/

			if(c == '(')
        			expect_semicolon = 0;

			if(c == ';')
        			expect_semicolon = 0;

			if(c == '(') 
				round++;
			else if(c == ')'){
			       	round--;
        			if(round < 0){
            				printf(RED "%d:%d: unmatched closing bracket ')'\n" RESET,line, col);
            				exit(1);
        			}
    			}
    			
			if(c == '[') 
				square++;
    			else if(c == ']'){
        			square--;
        			if(square < 0){
            				printf(RED "%d:%d: unmatched closing bracket ']'\n" RESET,line, col);
            				exit(1);
        			}
    			}
			
			if(c == '{') 
				curly++;
			else if(c == '}'){
        			curly--;
        			if(curly < 0){
            				printf(RED "%d:%d: unmatched closing bracket '}'\n" RESET,line, col);
            				exit(1);
        			}
    			}

    			printf(LIGHT_YELLOW "SYMBOL      :" RESET "   %c\n", c);
    			continue;
		}

		//if whitespace -> process buffer
		if(isspace(c)){
			processBuffer(buffer, line, col, filename, &expecting_identifier, &expect_semicolon, &identifier_found);
			i=0;
			continue;
		}

		//Check multi-cha operator
		if(isOperator(c))
		{
			// allow '.' to be part of float
    			if(c == '.' && i > 0 && isdigit(buffer[i-1])){
        			buffer[i++] = c;
        			buffer[i] = '\0';
        			continue;
    			}


    			processBuffer(buffer, line, col, filename, &expecting_identifier, &expect_semicolon, &identifier_found);
    			i = 0;
				

    			int next = fgetc(fp);
			if(next != EOF)
			{
    				char op[3] = {c, next, '\0'};
			
			/*if(c == '=')
                                expect_semicolon = 1;*/

    				if(isMultiOp(op))
        				printf(ORANGE "%-15s" RESET " %s\n", "OPERATOR    :", op);
    			
				else{
        				ungetc(next, fp);
        				printf(ORANGE "%-15s" RESET " %c\n", "OPERATOR    :", c);
    				}
				if(c == '=')
        				expect_semicolon = 1;
			}
			else
				printf(ORANGE "%-15s" RESET " %c\n","OPERATOR :",c);
    			continue;
		}


		//accumulate in buffer
		if(i < BUF_SIZE-1){
			buffer[i++] = c;
			buffer[i] = '\0';
		}
	}

	/* Process any remaining buffer */
        processBuffer(buffer, line, col, filename,&expecting_identifier,&expect_semicolon, &identifier_found);

	/* EOF validations */

        if(expecting_identifier)
                printf(RED "%d:%d: Missing variable name in declaration\n" RESET, line, col);
	if(expect_semicolon){
 	       	printf(RED "%d:%d: Missing ';'\n" RESET, line, col);
	   	exit(1);
	}

	if(round > 0)
		printf(RED "Error: missing ')'\n" RESET);
	if(square > 0)
		printf(RED "Error: missing ']'\n" RESET);
	if(curly > 0)
		printf(RED "Error: missing '}'\n" RESET);
	
}
