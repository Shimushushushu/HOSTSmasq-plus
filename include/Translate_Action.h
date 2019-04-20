#include "Translate_Base_Kai.h"

FILE *in, *out;

void H2D_Init(char *src) {
	in = fopen(src, "r");
	out = fopen("dnsmasq.conf.add", "w");
}

void D2H_Init(char *src) {
	in = fopen(src, "r");
	out = fopen("hosts", "w");
}

void End() {
	fclose(in);
	fclose(out);
}

/*
void H2D_Read() {
	int n = 0, i = 0, j = 0;
	char buf[256];
	while(fscanf(in, "%[^\n]", buf) != EOF ) {
		if(strchr(buf, '#') == NULL ||
			(strlen(strchr(buf, '#')) - strlen(strchr(buf, '.'))) * strlen(strchr(buf, '.')) < 0 ||
			(strlen(strchr(buf, '#')) - strlen(strchr(buf, ':'))) * strlen(strchr(buf, ':')) < 0) {
			while(buf[i] == ' ') { i++; }
			while(buf[i] != ' ') {
				addr[n].ip[j] = buf[i];
				i++, j++;
			}
			IS_IPv4_Check(n);
			IP_Hash(n);
			j=0;
			while(buf[i] == ' ') { i++; }
			while((buf[i] != ' ') && (buf[i] != '\0') && (buf[i] != '#')) {
				addr[n].ad[j] = buf[i];
				i++, j++;
			}
			n++, i = 0, j = 0;
		}
		fgetc(in);
	}
	cnt = n;
}
*/

void H2D_Read() {
	int n = 0, res;
	char buf1[512], buf2[512];
	res = fscanf(in, "%[^\n]", buf1);
	while(res >= 0) {
		if(res != 0) {
			sscanf(buf1, "%[^#]", buf2);
			sscanf(buf2, "%s %s", addr[n].ip, addr[n].ad);
			IS_IPv4_Check(n);
			IP_Hash(n);
			n++;
		}
		fgetc(in);
		res = fscanf(in, "%[^\n]", buf1);
	}
	cnt = n;
}

void D2H_Read() {
	int n = 0, res;
	char buf1[65536], buf2[65536];
	res = fscanf(in, "%[^\n]", buf1);
	while(res >= 0) {
		if(res != 0) {
			sscanf(buf1, "%[^#]", buf2);
			//TODO
		}
		fgetc(in);
		res = fscanf(in, "%[^\n]", buf1);
	}
	cnt = n;
}

void H2D_Convert() {
	qsort(addr, cnt, sizeof addr[0], cmp);
	int i = 0, j = 0, k;
	while(i < cnt) {
		if(!addr[i].IS_IPv4) { continue; }
		if(strcmp(addr[i].ip_cmp, addr[j].ip_cmp) == 0) { j++; }
		else {
			fprintf(out, "address=/");
			for(k = i; k < j; k++) { fprintf(out, "%s/", addr[k].ad); }
			fprintf(out, "%s\n", addr[i].ip);
			i = j;
		}
	}
	i = 0, j = 0;
	while(i < cnt) {
		if(addr[i].IS_IPv4) { continue; }
		if(strcmp(addr[i].ip_cmp, addr[j].ip_cmp) == 0) { j++; }
		else {
			fprintf(out, "address=/");
			for(k = i; k < j; k++) { fprintf(out, "%s/", addr[k].ad); }
			fprintf(out, "%s\n", addr[i].ip);
			i = j;
		}
	}
}

void D2H_Convert() {
	qsort(addr, cnt, sizeof addr[0], cmp);
	for(int i = 0; i < cnt; i++) {
		if(addr[i].IS_IPv4) { fprintf(out, "%s\t%s\n", addr[i].ip, addr[i].ad); }
	}
	for(int i = 0; i < cnt; i++) {
		if(!addr[i].IS_IPv4) { fprintf(out, "%s\t%s\n", addr[i].ip, addr[i].ad); }
	}
}