using Brecham.Obex;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Thought.vCards;

namespace PBAP2
{
    class Pbap
    {
        public static IEnumerable<vCard> CardsFromStreamReader(StreamReader reader)
        {
            while (!reader.EndOfStream)
            {
                vCardReader cardReader = new vCardStandardReader();
                vCard card;
                try
                {
                    card = cardReader.Read(reader);
                }
                catch (ArgumentNullException)
                {
                    continue;
                }
                yield return card;
            }

        }

        public static IEnumerable<vCard> CardsFromObexClient(ObexClientSession obexClient, string phoneBook)
        {
            ObexGetStream stream = obexClient.Get(phoneBook, "x-bt/phonebook");
            return CardsFromStreamReader(new StreamReader(stream, Encoding.UTF8));
        }

    }
}
