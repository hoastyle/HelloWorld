#include <stdio.h>
#include "dbg.h"
#include "wav_parser.h"

int main(int argc, char *argv[])
{
	char *filename = NULL;
	int fd;
	char *devicename = "default";
	WAVContainer_t wav;
	snd_pcm_t **handle; 

	if(argc != 2) {
		log_err("Usage: ./play <filename>\n");
		exit(1);
	}

	filename = argv[1];

	fd = open(filename, O_RDONLY);
	if(fd < 0) {
		log_err("Open %s failed\n", filename);
		exit(1);
	}

	//read wav header to wav
	if(WAV_ReadHeader(fd, &wav) < 0) {
		sentinel("Error WAV_Parse [%s]\n", filename);
	}

	//open pcm device
	if(snd_pcm_open(handle, devicename, ))

error:
	close(fd);
}
