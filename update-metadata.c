#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void get_substring(int max_char, char * orig, char ** output);

int main(int argc, char *argv[]){
	// Check arguments
	int max_char;
	if (argc < 4){
		printf("Needs 3 strings as input\n");
	}else if (argc < 5){
		max_char = 20;
	}else{
		max_char = atoi(argv[1]);
	}
	printf()
	char* input1;
	char* input2;
	get_substring(max_char, argv[1], &input1);
	get_substring(max_char, argv[2], &input2);	
	
	char output[strlen(input1)+strlen(input2)+500];
	sprintf(output,"ffmpeg -i /HDD/music/\"%s\" -y ~/.config/eww/test.png; ~/Documents/eww/target/release/eww update title=\"%s\" artist=\"%s\"\n", argv[3],input1,input2);
	printf("%s", output);
	printf("%s\n%s\n%s\n", argv[1], argv[2], argv[3]);
	system(output);
	return 0;

}


void get_substring(int max_char, char * orig, char ** output){
	//UTF16 is likely to exist in the input
	unsigned cnt=0, i;
	for(i=0; cnt < max_char && i < strlen(orig);i++){
		if((orig[i] & 0xF0) == 0xF0){
			i+=3;
		}else if((orig[i] & 0xE0) == 0xE0){
			i+=2;
		}else if((orig[i] & 0xC0) == 0xC0){
			++i;
		}
		cnt++;
		i++;
	}
	//char output[i+4];
	output[0] = (char *)malloc(i+5);
	if (strlen(orig) < max_char){
		strcpy(output[0],orig);
	}else{
		strncpy(output[0],orig,i);
		output[0][i+3] = '\0';
		output[0][i+2] = '.';		
		output[0][i+1] = '.';
		output[0][i] = '.';
	}
	return;
}
