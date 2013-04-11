#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <unistd.h>
#include <bluetooth/rfcomm.h>


void print_usage(const char* program_name) {
  fprintf(stderr, "usage: %s bluetooth_mac rfcomm_port\n", program_name);
}

int main(int argc, const char* argv[] ) {
  if (argc != 3) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  bdaddr_t bd_addr;
  const char *mac_str = argv[1];
  if (str2ba(mac_str, &bd_addr) < 0) {
    fprintf(stderr, "%s is an invalid bluetooth mac address\n", mac_str);
    exit(EXIT_FAILURE);
  }
  int port;
  port = atoi(argv[2]);
  int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
  struct sockaddr_rc addr = { 0 };
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) port;
  addr.rc_bdaddr = bd_addr;
  if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Couldn't connect");
  }
  close(s);

}
