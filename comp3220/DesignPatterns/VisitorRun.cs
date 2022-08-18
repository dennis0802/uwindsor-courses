using System;
using System.Collections.Generic;
using System.Text;

namespace VisitorPattern
{
    /**
     * In summary:
     * An operation can be performed on the elements of an object and define a new operation without changing
     * the classes of the elements that it operates.
     */
    class VisitorRun
    {
        public VisitorRun()
        {
            Paintings painting = new Paintings();
            painting.Attach(new WoodOil());
            painting.Attach(new MetalSpray());

            painting.Accept(new PriceVisitor());
            painting.Accept(new DaysVisitor());

            Console.WriteLine();
            Console.ReadKey();

        }
    }

    // Visitor
    public interface IVisitor
    {
        void Visit(Element element);
    }

    // ConcreteVisitor
    public class PriceVisitor : IVisitor
    {
        public void Visit(Element element)
        {
            Painting painting = element as Painting;
            
            // 10% more valuable!
            painting.Price *= 1.10;

            Console.WriteLine("{0} {1}'s new price: {2:C}", painting.GetType().Name, painting.Name, painting.Price);
        }
    }

    // ConcreteVisitor
    public class DaysVisitor : IVisitor
    {
        public void Visit(Element element)
        {
            Painting painting = element as Painting;

            // Provide 3 more hanging days
            painting.DaysUp += 3;

            Console.WriteLine("{0} {1} has now hung for this many days: {2}", painting.GetType().Name, painting.Name, painting.DaysUp);
        }
    }

    // Element
    public abstract class Element
    {
        public abstract void Accept(IVisitor visitor);
    }

    // ConcreteElement
    public class Painting : Element
    {
        private int daysUp;
        private double price;
        private string name;
        public string draft;
        public string frame;

        public Painting(string name, int daysUp, double price)
        {
            this.name = name;
            this.daysUp = daysUp;
            this.price = price;
        }

        public int DaysUp
        {
            get { return daysUp; }
            set { daysUp = value; }
        }

        public double Price
        {
            get { return price; }
            set { price = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public override void Accept(IVisitor visitor)
        {
            visitor.Visit(this);
        }
    }

    // ObjectStructure
    public class Paintings
    {
        private List<Painting> paintings = new List<Painting>();

        public void Attach(Painting painting)
        {
            paintings.Add(painting);
        }

        public void Detach(Painting painting)
        {
            paintings.Remove(painting);
        }

        public void Accept(IVisitor visitor)
        {
            foreach(Painting painting in paintings)
            {
                painting.Accept(visitor);
            }
        }
    }

    // Painting types
    public class WoodOil : Painting
    {
        public WoodOil() : base("Starry Night", 5, 10000.0)
        {
            frame = "in a beautifully carved wooden frame";
            draft = "in pencil";
        }
    }

    public class MetalSpray : Painting
    {
        public MetalSpray() : base("DJ", 5, 11000.0)
        {
            frame = "in a durable metal frame";
            draft = "in light color";
        }
    }
}
