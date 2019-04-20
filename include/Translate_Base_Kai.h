#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cnt = 0;

struct address {
	char ad[256], ip[64], ip_cmp[64];
	bool IS_IPv4;
} addr[65536];

void IS_IPv4_Check(int x) {
	char *tar = addr[x].ip;
	if((tar = strchr(addr[x].ip, '.')) != NULL) { addr[x].IS_IPv4 = true; }
	else {addr[x].IS_IPv4 = false; }
}

void IP_Hash(int x) {
	char *tar1 = addr[x].ip, *tar2 = addr[x].ip;
	int len, i=0;
	if(addr[x].IS_IPv4) {
		while((tar1 = strchr(tar2, '.')) != NULL) {
			len = strlen(tar2) - strlen(tar1);
			while(len < 3) {
				addr[x].ip_cmp[i] = '0';
				i++, len++;
			}
			strcat(addr[x].ip_cmp, tar2);
			i += (strlen(tar2) - strlen(tar1) + 1);
			for(int j = i;j < 64; j++) { addr[x].ip_cmp[j] = '\0'; }
			tar1++;
			tar2 = tar1;
		}
		tar1 = strchr(tar2, '\0');
		len = strlen(tar2) - strlen(tar1);
		while(len < 3) {
			addr[x].ip_cmp[i] = '0';
			i++, len++;
		}
		strcat(addr[x].ip_cmp, tar2);
		i += (strlen(tar2) - strlen(tar1) + 1);
		for(int j = i;j < 64; j++) { addr[x].ip_cmp[j] = '\0'; }
	} else {
		int cnt = 0;
		while((tar1 = strchr(tar2, ':')) != NULL) { cnt++, tar1++, tar2 = tar1; }
		if(cnt == 7) {
			tar1 = addr[x].ip, tar2 = addr[x].ip;
			while((tar1 = strchr(tar2, ':')) != NULL) {
			len = strlen(tar2) - strlen(tar1);
			while(len < 4) {
				addr[x].ip_cmp[i] = '0';
				i++, len++;
			}
			strcat(addr[x].ip_cmp, tar2);
			i += (strlen(tar2) - strlen(tar1) + 1);
			for(int j = i;j < 64; j++) { addr[x].ip_cmp[j] = '\0'; }
			tar1++;
			tar2 = tar1;
		}
		tar1 = strchr(tar2, '\0');
		len = strlen(tar2) - strlen(tar1);
		while(len < 4) {
			addr[x].ip_cmp[i] = '0';
			i++, len++;
		}
		strcat(addr[x].ip_cmp, tar2);
		i += (strlen(tar2) - strlen(tar1) + 1);
		for(int j = i;j < 64; j++) { addr[x].ip_cmp[j] = '\0'; }
		} else {
			printf("%d  ", cnt);
			puts("Unavailable yet");
		}
	}
}

int cmp(const void *a, const void *b) {
	struct address *aa = (struct address *)a, *bb = (struct address *)b;
	return (int)strcmp(aa->ip_cmp , bb->ip_cmp);
}