using InTheHand.Net;
using InTheHand.Net.Sockets;
using InTheHand.Net.Bluetooth;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Brecham.Obex;

namespace PBAP2
{
    class Program
    {
        static void Main(string[] args)
        {
            BluetoothAddress addr = BluetoothAddress.Parse(PhoneMAC.macAddress);
            BluetoothClient c = new BluetoothClient();
            c.Connect(addr, BluetoothService.PhonebookAccessPse);
            using (ObexClientSession obexClient = new ObexClientSession(c.GetStream(), UInt16.MaxValue))
            {
                Guid targetHeader = new Guid("796135f0-f0c5-11d8-0966-0800200c9a66");
                obexClient.Connect(targetHeader.ToByteArray());
            }
        }
    }
}
