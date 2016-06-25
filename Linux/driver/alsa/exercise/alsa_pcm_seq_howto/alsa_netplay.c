#include <stdio.h>
#include <alsa/asoundlib.h>
#include <string.h>
#include "dbg.h"

int main(int argc, char *argv[])
{
	/*handle for pcm device*/
	snd_pcm_t *pcm_handle;
	snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
	/* typedef snd_pcm_hw_params
	 * information about the hardware and configuration
	 */
	snd_pcm_hw_params_t *hwparams;
	char *pcm_name;

	//copy and create a string
	pcm_name = strdup("hw:0,0");

	snd_pcm_hw_params_alloca(&hwparams);

	if(snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
		log_err("Error opening PCM device %s\n", pcm_name);
		exit(1);
	}

}
