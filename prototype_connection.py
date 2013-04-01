from bluetooth import discover_devices, lookup_name, BluetoothSocket, RFCOMM
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
  sock = BluetoothSocket( RFCOMM )
  sock.connect((target_address, 19))
  print "Socket established"
  sock.close()
