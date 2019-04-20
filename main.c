#include "include/Identification.h"
#include "include/UI.h"

int main(int argc, char *argv[]) {
	char ans;
	if(argc > 1) {
		switch(Recognition(argv[1])) {
			case 1: 
				_hosts_confirm();
				break;
			case 2:
				_dnsmasq_confirm();
				break;
			default: _name_err();
		}
	} else { _manual_confirm(); }
	return 0;
}