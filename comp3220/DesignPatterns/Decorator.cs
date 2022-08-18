using System;
using System.Collections.Generic;
using System.Text;

namespace DecoratorPattern
{
    /**
     * In summary:
     * Add more responsibilties to an object dynamically, an alternative to subclassing
     * Paintings are the interface that can have more responsbilities dynamically
     * Concrete paintigns (metal spray, wood oil) are the objects that can be affected
     * Decorators have a reference to the Painting and have an itnerface conformign to Painting's interface
     * Concrete decorators (purchase, bid) are the responsibilities to add, instead of subclasses for purchasing and bidding
     */
    class DecoratorDriver
    {
        public DecoratorDriver()
        {
            // Make paintings
            MetalSpray metalSpray = new MetalSpray("Brianna Bucases", "Silver");
            metalSpray.Display();

            WoodOil woodOil = new WoodOil("Ben Armaly", "Oak");
            woodOil.Display();

            // Make biddable, then bid and display
            Console.Write("\nMaking oil painting biddable:");
            Bidding bidOilPainting = new Bidding(woodOil);
            Purchase purchaseOil = new Purchase(woodOil);
            bidOilPainting.BidPainting("Peter Thai");
            bidOilPainting.BidPainting("Madison Bromaroff");
            purchaseOil.BuyPainting("Teena");
            purchaseOil.BuyPainting("Dennis Dao");
            bidOilPainting.Display();
            purchaseOil.Display();
            purchaseOil.ReturnPainting("Teena");
            bidOilPainting.Display();
            purchaseOil.Display();

            
            Console.Write("\nMaking spray painting biddable and purchaseable:");
            Bidding bidSprayPainting = new Bidding(metalSpray);
            Purchase purchaseSpray = new Purchase(woodOil);
            bidSprayPainting.BidPainting("Anthony Fanara");
            bidSprayPainting.BidPainting("John Kehoe");
            purchaseSpray.BuyPainting("Kevin Trinh");
            bidSprayPainting.Display();
            purchaseSpray.Display();
            
            Console.Write("\n");
            Console.ReadKey();

        }
    }

    // Decorator
    public abstract class Decorator : Painting
    {
        protected Painting painting;

        public Decorator(Painting painting)
        {
            this.painting = painting;
        }

        public override void Display()
        {
            painting.Display();
        }
    }

    // Concrete Decorator
    public class Bidding : Decorator
    {
        protected readonly List<string> bidders = new List<string>();

        // Constructor
        public Bidding(Painting painting) : base(painting) { }

        public void BidPainting(string name)
        {
            bidders.Add(name);
            painting.NumBids++;
        }

        public void UnbidPainting(string name)
        {
            bidders.Remove(name);
            painting.NumBids--;
        }

        public override void Display()
        {
            base.Display();
            foreach(string bidder in bidders)
            {
                Console.WriteLine(" Bidder: " + bidder);
            }
        }
    }

    // Concrete Decorator
    public class Purchase : Decorator
    {
        protected readonly List<string> buyers = new List<string>();

        // Constructor
        public Purchase(Painting painting) : base(painting) { }

        public void BuyPainting(string name)
        {
            buyers.Add(name);
            painting.NumPurchases++;
        }

        public void ReturnPainting(string name)
        {
            buyers.Remove(name);
            painting.NumPurchases--;
        }

        public override void Display()
        {
            base.Display();
            foreach (string buyer in buyers)
            {
                Console.WriteLine(" Buyer: " + buyer);
            }
        }
    }

    // Component
    public abstract class Painting
    {
        private string frame, draft;
        private int numBids, numPurchases;

        public int NumBids
        {
            get { return numBids; }
            set { numBids = value; }
        }

        public int NumPurchases
        {
            get { return numPurchases; }
            set { numPurchases = value; }
        }

        public string Frame
        {
            get { return frame; }
            set { frame = value; }
        }

        public string Draft
        {
            get { return draft; }
            set { draft = value; }
        }

        public abstract void Display();
    }

    // Concrete component
    public class MetalSpray : Painting
    {
        private string artist;
        private string metalType;

        public MetalSpray(string artist, string metalType)
        {
            this.artist = artist;
            this.metalType = metalType;
            this.Draft = " draft with light color";
            this.Frame = " in a durable metal frame";
            this.NumBids = 0;
            this.NumPurchases = 0;
        }

        public override void Display()
        {
            Console.WriteLine("\nPainting ------");
            Console.WriteLine("Artist: {0}", artist);
            Console.WriteLine("Drafted in: {0}", Draft);
            Console.WriteLine("Framed in: {0}", Frame);
            Console.WriteLine("Frame Type: {0}", metalType);
            Console.WriteLine("Number of bids: {0}", NumBids);
            Console.WriteLine("Number of purchases: {0}", NumPurchases);
        }
    }

    // Concrete component
    public class WoodOil : Painting
    {
        private string artist;
        private string woodType;

        public WoodOil(string artist, string woodType)
        {
            this.artist = artist;
            this.woodType = woodType;
            this.Draft = " draft with pencil and paper";
            this.Frame = " in a beautifully carved wooden frame";
            this.NumBids = 0;
            this.NumPurchases = 0;
        }

        public override void Display()
        {
            Console.WriteLine("\nPainting ------");
            Console.WriteLine("Artist: {0}", artist);
            Console.WriteLine("Drafted in: {0}", Draft);
            Console.WriteLine("Framed in: {0}", Frame);
            Console.WriteLine("Frame Type: {0}", woodType);
            Console.WriteLine("Number of bids: {0}", NumBids);
            Console.WriteLine("Number of purchases: {0}", NumPurchases);
        }
    }
}
