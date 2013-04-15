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
  bdaddr_t target;
  const char *target_str = argv[1];
  if (str2ba(target_str, &target) < 0) {
    fprintf(stderr, "%s is an invalid bluetooth mac address\n", target_str);
    exit(EXIT_FAILURE);
  }
  uint8_t port;
  uuid_t svc_uuid;
  sdp_uuid16_create(&svc_uuid, PBAP_PSE_SVCLASS_ID);
  sdp_session_t *session = sdp_connect( BDADDR_ANY, &target, 0);
  if (session == NULL) {
    perror("connecting to SDP");
    exit(EXIT_FAILURE);
  }
  sdp_list_t *response_list = NULL, *search_list, *attrid_list;
  search_list = sdp_list_append( NULL, &svc_uuid );
  uint32_t range = 0x0000ffff;
  attrid_list = sdp_list_append( NULL, &range);
  if (sdp_service_search_attr_req( session, search_list, SDP_ATTR_REQ_RANGE, attrid_list, &response_list) < 0){
    perror("search search request");
    exit(EXIT_FAILURE);
  }
  sdp_list_t *proto_list = NULL;
  for (sdp_list_t *r = response_list; r; r = r->next ) {
    sdp_record_t *rec = (sdp_record_t*) r->data;
    if (sdp_get_access_protos( rec, &proto_list ) == -1) {
      perror("sdp_get_access_protos");
      exit(EXIT_FAILURE);
    }
    port = sdp_get_proto_port( proto_list, RFCOMM_UUID );
    printf("found service running on RFCOMM port %d\n", port);
    sdp_list_free( proto_list, 0);
    sdp_record_free( rec );
  }
  sdp_list_free( response_list, 0);
  sdp_list_free( search_list, 0);
  sdp_list_free( attrid_list, 0);
  sdp_close( session );
  return 0;
}
