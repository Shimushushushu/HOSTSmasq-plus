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

void H2D_Read() {
	int n = 0, res;
	char buf[MAX_LINE_LENGTH];
	res = fscanline(in, buf);
	while(res != EOF) {
		if(res > 0) {
			sscanf(buf, "%s %s", addr[n].ip, addr[n].domain);
			IS_IPv4_Check(n);
			IP_Hash(n);
			n++;
		}
		memset(buf, 0, MAX_LINE_LENGTH);
		res = fscanline(in, buf);
	}
	cnt = n;
}

void D2H_Read() {
	int n = 0, res;
	char buf1[65536], buf2[65536], buf3[256], *tar1, *tar2;
	res = fscanf(in, "%[^\n]", buf1);
	while(res >= 0) {
		if(res != 0) {
			sscanf(buf1, "%[^#]", buf2);
			tar1 = strchr(buf2, '/');
			tar1++;
			while(sscanf(tar1, "%[^/]", buf3) != EOF) {
				
			}

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
			for(k = i; k < j; k++) { fprintf(out, "%s/", addr[k].domain); }
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
			for(k = i; k < j; k++) { fprintf(out, "%s/", addr[k].domain); }
			fprintf(out, "%s\n", addr[i].ip);
			i = j;
		}
	}
}

void D2H_Convert() {
	qsort(addr, cnt, sizeof addr[0], cmp);
	for(int i = 0; i < cnt; i++) {
		if(addr[i].IS_IPv4) { fprintf(out, "%s\t%s\n", addr[i].ip, addr[i].domain); }
	}
	for(int i = 0; i < cnt; i++) {
		if(!addr[i].IS_IPv4) { fprintf(out, "%s\t%s\n", addr[i].ip, addr[i].domain); }
	}
}