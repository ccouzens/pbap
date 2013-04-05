#!/usr/bin/env python
from bluetooth import discover_devices, lookup_name, BluetoothSocket, RFCOMM, find_service
from sys import argv

if __name__ == '__main__':
  target_name = argv[1]
  print "looking for", target_name
  target_address = None
  nearby_devices = discover_devices()
  for address in nearby_devices:
    if target_name == lookup_name(address):
      target_address = address
      break
  if target_address is None:
    raise Exception("Could not find bluetooth device")
  print "found", target_address
  pbap_servers = find_service(uuid='112F', address=target_address)
  number_of_matching_servers = len(pbap_servers)
  if number_of_matching_servers != 1:
    print "Found %d matching servers" % number_of_matching_servers
  if number_of_matching_servers == 0:
    raise Exception("No PBAP servers found")
  pbap_server = pbap_servers[0]
  sock = BluetoothSocket( RFCOMM )
  sock.connect((target_address, pbap_server['port']))
  print "Socket established"
  sock.close()
