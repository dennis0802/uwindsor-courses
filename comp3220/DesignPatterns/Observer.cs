using System;
using System.Collections.Generic;
using System.Text;

namespace ObserverPattern
{
    /**
     * In summary:
     * When the price of a Painting changes, all its observers will know.
     * For example, a wood oil painting is the concrete subject and bidders will be notified
     * This forms a one-to-many relationship; one painting to many bidders.
     */
    class Observer
    {
        public Observer()
        {
            // Create paintings and attach bidders
            WoodOil wood = new WoodOil("Mona Lisa", 4000.00);
            MetalSpray metal = new MetalSpray("DJ", 2000.00);
            wood.Attach(new Bidder("Benjamin Armaly"));
            metal.Attach(new Bidder("Brianna Bucasas"));

            // Changes will notify bidders
            wood.Price = 4100.00;
            wood.Price = 4200.00;
            metal.Price = 6900.00;
            metal.Price = 6969.00;

            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Subject
    public abstract class Painting
    {
        private string name;
        private double price;
        private List<IBidder> bidders = new List<IBidder>();

        public Painting(string name, double price)
        {
            this.name = name;
            this.price = price;
        }
        public void Attach(IBidder bidder)
        {
            bidders.Add(bidder);
        }
        public void Detach(IBidder bidder)
        {
            bidders.Remove(bidder);
        }

        public void Notify()
        {
            foreach(IBidder bidder in bidders)
            {
                bidder.Update(this);
            }
            Console.WriteLine("");
        }

        public double Price
        {
            get { return price; }
            set
            {
                if(price != value)
                {
                    price = value;
                    Notify();
                }
            }
        }

        public string Name
        {
            get { return name; }
        }
    }

    // ConcreteSubject
    public class WoodOil : Painting
    {
        public WoodOil(string name, double price) : base(name, price) { }
    }

    public class MetalSpray : Painting
    {
        public MetalSpray(string name, double price) : base(name, price) { }
    }

    // Observer
    public interface IBidder
    {
        void Update(Painting painting);
    }

    // ConcreteObserver
    public class Bidder : IBidder
    {
        private string name;
        private Painting painting;

        public Bidder(string name)
        {
            this.name = name;
        }

        public void Update(Painting painting)
        {
            Console.WriteLine("Notified {0} of {1}'s " + "change to {2:C}", name, painting.Name, painting.Price);
        }

        public Painting Painting
        {
            get { return painting; }
            set { painting = value; }
        }
    }
}
