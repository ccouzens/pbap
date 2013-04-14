#include <stdio.h>
#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: %s bluetooth_mac_address\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  bdaddr_t bd_addr;
  const char *bd_addr_str = argv[1];
  if (str2ba(bd_addr_str, &bd_addr) < 0) {
    fprintf(stderr, "%s is an invalid bluetooth mac address\n", bd_addr_str);
    exit(EXIT_FAILURE);
  }

  uuid_t pbap_server_service_class_uuid;
  sdp_uuid32_create(&pbap_server_service_class_uuid, PBAP_PSE_SVCLASS_ID);
}
