#include <stdio.h>
#include <string.h>
#define MAX_LINE_LENGTH 65536

int sscanline(const char *src, char *tar) {
	memset(tar, 0, MAX_LINE_LENGTH);
	if(strlen(src) == 0) { return 0; }
	int i, _head, _end;
	i = 0, _head = 0, _end = 0;
	while(src[i] == ' ' || src[i] == '\t') { i++; }
	_head = i;
	while(src[i] != '#' && src[i] != '\0') { i++; }
	_end = i;
	if(_head == _end) { return 0; }
	for(i = 0; i < _end - _head; i++) { tar[i] = src[_head + i]; }
	tar[i + 1] = '\0';
	return 1;
}

int fscanline(FILE *src, char *tar) {
	char _buf[65536];
	if(fscanf(src, "%[^\n]", _buf) != EOF) {
		int res = sscanline(_buf, tar);
		memset(_buf, 0, MAX_LINE_LENGTH);
		fgetc(src);
		return res;
	} else { return EOF; }
}
