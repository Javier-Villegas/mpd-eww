#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<libmpd.h>
#include <unistd.h>

#define MAX_CHAR 20
void get_substring(int max_char, char * orig);
void status_changed(MpdObj *mi, ChangedStatusType what);

int main(int argc, char *argv[]){
	int run = 1, iport = 6600;
    char *hostname = getenv("MPD_HOST");
    char *port = getenv("MPD_PORT");
    char *password = getenv("MPD_PASSWORD");
    MpdObj *obj = NULL;

	if(!hostname) {
		hostname = "localhost";
	}
	if(port){
		iport = atoi(port);
	}

	obj = mpd_new(hostname, iport,password);

	mpd_signal_connect_status_changed(obj,(StatusChangedCallback)status_changed, NULL);
	mpd_set_connection_timeout(obj, 10);

	if(!mpd_connect(obj)){
		mpd_send_password(obj);
   		do{
			mpd_status_update(obj);
		}while(!usleep(100000) &&  run);
	}
	return 0;
}


void get_substring(int max_char, char * orig){
	//UTF8 encoding is likely to exist in the input
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
	}
	if (strlen(orig) > i){
		orig[i-1] = '.';
		orig[i-2] = '.';
		orig[i-3] = '.';
	}
	orig[i] = '\0';
	return;
}

void status_changed(MpdObj *mi, ChangedStatusType what){
	if(what&MPD_CST_SONGID){
		printf("Read song\n");
		mpd_Song *song = mpd_playlist_get_current_song(mi);
		printf("Done\n");
		char output[500];
		if (song == NULL ){
			printf("Error getting metadata\n");
			printf("Song change detected!\nTitle: Missing\nArtist: Missing\n");
		}else{
			if (song->title != NULL) get_substring(MAX_CHAR,song->title);
			if (song->artist != NULL) get_substring(MAX_CHAR,song->artist);
			
			sprintf(output, "ffmpeg -i /HDD/music/\"%s\" -y ~/.config/eww/test.png; ~/Documents/eww/target/release/eww update title=\"%s\" artist=\"%s\" img=\"/home/javier/.config/eww/test.png\"",
					song->file, song->title, song->artist);
			system(output);
			printf("Song change detected!\nTitle: %s\nArtist: %s\n",
				song->title, song->artist);
		}
	}
}
