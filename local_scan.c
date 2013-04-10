#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <unistd.h>

int main(int argc, const char* argv[] ) {
  int adapter_id = hci_get_route(NULL);
  if (adapter_id < 0) {
    perror("finding default adapter");
    exit(1);
  }
  int sock = hci_open_dev(adapter_id);
  if (sock < 0) {
    perror("opening default adapter");
    exit(1);
  }
  inquiry_info *devices = NULL;
  int num_rsp = hci_inquiry(adapter_id, 8, 255, NULL, &devices, IREQ_CACHE_FLUSH);
  if (num_rsp < 0) {
    perror("inquiring for local devices");
    exit(1);
  }
  printf("%d devices found\n", num_rsp);
  for(int i = 0; i < num_rsp; i++) {
    char address[19] = { 0 };
    char name[248] = { 0 };
    bdaddr_t *bd_addr = &(devices + i)->bdaddr;
    ba2str(bd_addr, address);
    if (hci_read_remote_name(sock, bd_addr, sizeof(name), name, 0) != 0 ) {
      printf("couldn't identify name of %s\n", address);
      strncpy(name, "[Unknown]", sizeof(name));
    }
    printf("%d %s: %s\n", i, address, name);
  }
  free(devices);
  if (close(sock) < 0) {
    perror("closing socket");
    exit(1);
  }
}
