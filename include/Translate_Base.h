#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct address {
	char ad[256]; char ip[64]; char ip_cmp[64];
	bool IS_IPv4;
	void IS_IPv4_Check() {
		char *tar = ip;
		if((tar = strchr(ip, '.')) != NULL) { IS_IPv4 = true; }
		else {IS_IPv4 = false; }
	}
	void IP_Hash() {
		char *tar1 = ip; char *tar2 = ip;
		int len; int i=0;
		if(IS_IPv4) {
			while((tar1 = strchr(tar2, '.')) != NULL) {
				len = strlen(tar2) - strlen(tar1);
				while(len < 3) {
					ip_cmp[i] = '0';
					i++, len++;
				}
				strcat(ip_cmp, tar2);
				i += (strlen(tar2) - strlen(tar1) + 1);
				for(int j = i;j < 64; j++) { ip_cmp[j] = '\0'; }
				tar1++;
				tar2 = tar1;
			}
			tar1 = strchr(tar2, '\0');
			len = strlen(tar2) - strlen(tar1);
			while(len < 3) {
				ip_cmp[i] = '0';
				i++, len++;
			}
			strcat(ip_cmp, tar2);
			i += (strlen(tar2) - strlen(tar1) + 1);
			for(int j = i;j < 64; j++) { ip_cmp[j] = '\0'; }
		} else {
			int cnt = 0;
			while((tar1 = strchr(tar2, ':')) != NULL) { cnt++, tar1++, tar2 = tar1; }
			if(cnt == 7) {
				tar1 = ip, tar2 = ip;
				while((tar1 = strchr(tar2, ':')) != NULL) {
				len = strlen(tar2) - strlen(tar1);
				while(len < 4) {
					ip_cmp[i] = '0';
					i++, len++;
				}
				strcat(ip_cmp, tar2);
				i += (strlen(tar2) - strlen(tar1) + 1);
				for(int j = i;j < 64; j++) { ip_cmp[j] = '\0'; }
				tar1++;
				tar2 = tar1;
			}
			tar1 = strchr(tar2, '\0');
			len = strlen(tar2) - strlen(tar1);
			while(len < 4) {
				ip_cmp[i] = '0';
				i++, len++;
			}
			strcat(ip_cmp, tar2);
			i += (strlen(tar2) - strlen(tar1) + 1);
			for(int j = i;j < 64; j++) { ip_cmp[j] = '\0'; }
			} else {
				printf("%d  ", cnt);
				puts("Unavailable yet");
			}
		}
	}
} addr[65536];

int cmp(const void *a, const void *b) {
	struct address *aa = (address *)a;
	struct address *bb = (address *)b;
	if(aa->ip_cmp == bb->ip_cmp) { return 0; }
	else if(aa->ip_cmp < bb->ip_cmp) { return -1; }
	return 1;
}