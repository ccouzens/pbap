#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <unistd.h>
#include <bluetooth/rfcomm.h>
#include <openobex/obex.h>

void print_usage(const char* program_name) {
  fprintf(stderr, "usage: %s bluetooth_mac rfcomm_port\n", program_name);
}

static void obex_event_cb(obex_t *handle, obex_object_t *obj, int mode,
  int event, int obex_cmd, int obex_rsp)
{
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
  obex_t *handle;
  handle = OBEX_Init(OBEX_TRANS_BLUETOOTH, obex_event_cb, 0);
  if (BtOBEX_TransportConnect(handle, BDADDR_ANY, &bd_addr, port) < 0) {
    perror("Couldn't connect");
    exit(EXIT_FAILURE);
  }

  OBEX_TransportDisconnect(handle);
  OBEX_Cleanup(handle);

}
