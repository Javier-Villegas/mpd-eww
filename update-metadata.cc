#include<cstdio>
#include<stdlib.h>
#include<string.h>
void get_substring(int max_char, char * orig, char ** output);

int main(int argc, char *argv[]){
	// Check arguments
	int max_char;
	if (argc < 3){
		printf("Needs 2 strings as input\n");
	}else if (argc < 4){
		max_char = 20;
	}else{
		max_char = atoi(argv[1]);
	}
	char* input1;
	char* input2;
	get_substring(max_char, argv[1], &input1);
	get_substring(max_char, argv[2], &input2);	
	
	char output[strlen(input1)+strlen(input2)+20];
	sprintf(output,"command x %s %s\n", input1,input2);
	printf("%s", output);
	return 0;

}


void get_substring(int max_char, char * orig, char ** output){
	//UTF16 is likely to exist in the input
	unsigned cnt=0, i;
	for(i=0; cnt < max_char && i < strlen(orig);i++){
		if((unsigned(orig[i]) & 0xF0) == 0xF0){
			i+=3;
		}else if((unsigned(orig[i]) & 0xE0) == 0xE0){
			i+=2;
		}else if((unsigned(orig[i]) & 0xC0) == 0xC0){
			++i;
		}
		cnt++;
		i++;
	}
	//char output[i+4];
	*output = (char *)malloc(i+5);
	if (strlen(orig) < max_char){
		strcpy(*output,orig);
	}else{
		strncpy(*output,orig,i);
		*output[i+3] = '\0';
		*output[i+2] = '.';		
		*output[i+1] = '.';
		*output[i] = '.';
	}
	printf("%s\n",*output);
	return;
}
