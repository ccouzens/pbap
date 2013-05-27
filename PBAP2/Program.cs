using InTheHand.Net;
using InTheHand.Net.Sockets;
using InTheHand.Net.Bluetooth;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PBAP2
{
    class Program
    {
        static void Main(string[] args)
        {
            BluetoothAddress addr = BluetoothAddress.Parse(PhoneMAC.macAddress);
            BluetoothClient c = new BluetoothClient();
            c.Connect(addr, BluetoothService.PhonebookAccessPse);
        }
    }
}
