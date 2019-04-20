#include <stdio.h>

#include "Translate_Action.h"

void __exit() { puts("Action canceled, the program will exit"); }

void _hosts() { puts("Is this a HOSTS file? y/n"); }

void _dnsmasq() { puts("Is this a DNSMASQ.CONF.ADD file? y/n"); }

void _name_err() { puts("Could not recognize the file name, the program will exit"); }

void _manual() {
	puts("It seems that you have not put the file name into the program argument,");
	puts("do you want to translate a HOSTS file or a DNSMASQ file? h/d");
}

void _mode_choose() {
	puts("There are three modes, which are listed below:");
	puts("1. Only converting files without changing the order of addresses, post scripts will be reserved. (Press 1)");
	puts("2. Almost the same as mode 1 but post scripts will be deleted. (Press 2)");
	puts("3. Sort the IP addresses from small to large and the domains alphabetically, and the post scripts will be deleted. (Press 3)");
}

void _hosts_confirm() {
	char ans;
	_hosts();
	scanf("%c", &ans);
	switch(ans) {
		case 'y':;
		case 'Y':
			//action here
			printf("TESTH");
			break;
		default: __exit();
	}
}

void _dnsmasq_confirm() {
	char ans;
	_dnsmasq();
	scanf("%c", &ans);
	switch(ans) {
		case 'y':;
		case 'Y':
			//action here
			printf("TESTD");
			break;
		default: __exit();
	}
}

void _manual_confirm() {

	puts("This function is not avialable yet, the program will exit.");
	return;

	char ans;
	_manual();
	scanf("%c", &ans);
	switch(ans) {
		case 'h':;
		case 'H':
			//action here
			printf("TESTH");
			break;
		case 'd':;
		case 'D':
			//action here
			printf("TESTD");
			break;
		default: __exit();
	}
}

void H2D_Mode_Choose() {
	_mode_choose();
	char ans;
	scanf("%c", &ans);
	switch(ans) {
		default:;
		case '1':
			//action here
			break;
		case '2':
			//action here
			break;
		case '3':
			//action here
			break;
	}
}

void D2H_Mode_Choose() {
	_mode_choose();
	char ans;
	scanf("%c", &ans);
	switch(ans) {
		default:;
		case '1':
			//action here
			break;
		case '2':
			//action here
			break;
		case '3':
			//action here
			break;
	}
}
