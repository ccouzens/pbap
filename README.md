PBAP (Phone Book Access Profile)
================================

An experiment to see if I can connect to PBAP on my Android CyanogenMod phone via Bluetooth.
To begin with, I'll be happy just to see a list of contacts.

Edited output of `sdptool browse _phoneMACAddress_`:

<pre>
Service Name: OBEX Phonebook Access Server
Service RecHandle: 0x10009
Service Class ID List:
  "Phonebook Access - PSE" (0x112f)
Protocol Descriptor List:
  "L2CAP" (0x0100)
  "RFCOMM" (0x0003)
    Channel: 19
  "OBEX" (0x0008)
Profile Descriptor List:
  "Phonebook Access" (0x1130)
    Version: 0x0100
</pre>

Documentation
-------------
[Specification](https://www.bluetooth.org/docman/handlers/downloaddoc.ashx?doc_id=230887)

[OpenOBEX API](http://dev.zuckschwerdt.org/openobex/doxygen/)

[OpenOBEX website](http://dev.zuckschwerdt.org/openobex/)

[OpenOBEX code](https://www.gitorious.org/openobex)

[Bluetooth Programming for Linux](http://people.csail.mit.edu/albert/bluez-intro/)

[Bluetooth service classes (including PBAP)](https://www.bluetooth.org/Technical/AssignedNumbers/service_discovery.htm)

[BlueZ gitweb](https://git.kernel.org/cgit/bluetooth/bluez.git)
The documentation for BlueZ seems to be the code itself.

[Gnome Bluetooth UI](https://developer.gnome.org/gnome-bluetooth/stable/BluetoothChooser.html)
