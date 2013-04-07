#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, const char* argv[] ) {
  int adapter_id = hci_get_route(NULL);
  return adapter_id;
}
