#include "sound.h"

void play_sound () {
	ca_context_play (ca_gtk_context_get (), 1, CA_PROP_MEDIA_FILENAME, RES_DIR "/galarm2.ogg", NULL);
} 
