#!/usr/bin/env python
from bluetooth import lookup_name, BluetoothSocket, RFCOMM, find_service
from sys import argv

if __name__ == '__main__':
  target_name = argv[1]
  print "looking for", target_name
  target_address = None
  pbap_servers = find_service(uuid='112F')
  pbap_devices = set(pbap_server['host'] for pbap_server in pbap_servers)

  print "found %d PBAP server devices hosting %d PBAP servers" % (len(pbap_devices), len(pbap_servers))

  for address in pbap_devices:
    if target_name == lookup_name(address):
      target_address = address
      break
  if target_address is None:
    raise Exception("Could not find bluetooth device")
  print "found", target_address
  pbap_servers = [pbap_server for pbap_server in pbap_servers if pbap_server['host'] == target_address]
  number_of_matching_servers = len(pbap_servers)
  if number_of_matching_servers != 1:
    print "Found %d matching servers" % number_of_matching_servers
  if number_of_matching_servers == 0:
    raise Exception("No PBAP servers found")
  pbap_server = pbap_servers[0]
  sock = BluetoothSocket( RFCOMM )
  port = pbap_server['port']
  sock.connect((target_address, port))
  print "Socket established on port %d" % port
  sock.close()
