using InTheHand.Net;
using InTheHand.Net.Sockets;
using InTheHand.Net.Bluetooth;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Brecham.Obex;
using System.IO;
using Thought.vCards;

namespace PBAP2
{
    class Program
    {
        static readonly byte[] PBAP_TARGET = new byte[] {
            0x79, 0x61, 0x35, 0xf0, 0xf0, 0xc5, 0x11, 0xd8, 0x09, 0x66,
            0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66
        };
        static void Main(string[] args)
        {
            BluetoothAddress addr = BluetoothAddress.Parse(PhoneMAC.macAddress);
            BluetoothClient c = new BluetoothClient();
            c.Connect(addr, BluetoothService.PhonebookAccessPse);
            using (ObexClientSession obexClient = new ObexClientSession(c.GetStream(), UInt16.MaxValue))
            {
                obexClient.Connect(PBAP_TARGET);
                using (ObexGetStream stream = obexClient.Get("/telecom/pb", "x-bt/phonebook"))
                {
                    using (StreamReader reader = new StreamReader(stream, Encoding.UTF8))
                    {
                        while (!reader.EndOfStream)
                        {
                            vCardReader cardReader = new vCardStandardReader();
                            vCard card;
                            try
                            {
                                card = cardReader.Read(reader);
                            } catch(ArgumentNullException) {
                                Console.WriteLine("skipping");
                                continue;
                            }
                            Console.WriteLine("not skipping " + card.GivenName + " " + card.FamilyName);
                        }
                    }
                };
            }
        }
    }
}
