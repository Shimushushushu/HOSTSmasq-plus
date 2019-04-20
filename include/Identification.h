#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int Recognition(char *tar) {
	char tmp[32];
	strcpy(tmp, tar);
	for(int i = 0; i < strlen(tmp); i++) { tmp[i] = tolower(tmp[i]); }
	if(strcmp(tmp, "dnsmasq.conf.add") == 0) { return 2; }
	else if(strcmp(tmp, "hosts") == 0) { return 1; }
	return 0;
}