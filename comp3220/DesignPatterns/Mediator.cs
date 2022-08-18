using System;
using System.Collections.Generic;
using System.Text;

namespace MediatorPattern
{        
    /**
    * In summary:
    * Define an object that encapsulates how a set of objects interact
    * The musuem encapsulates how paintings interact with each other
    */
    class Mediator
    {

        public Mediator()
        {
            // Create museum
            Museum museum = new Museum();

            // Create paintings
            Painting wood1 = new WoodOil("Mona Lisa");
            Painting wood2 = new WoodOil("Starry Night");
            Painting wood3 = new WoodOil("Guernica");
            Painting spray1 = new MetalSpray("Friends");
            Painting spray2 = new MetalSpray("DJ");
            Painting spray3 = new MetalSpray("Barking Dogs");

            museum.Register(wood1);
            museum.Register(wood2);
            museum.Register(wood3);
            museum.Register(spray1);
            museum.Register(spray2);
            museum.Register(spray3);

            // Receive paintings info
            wood1.Receive("Vincent Van Gogh", "A beautiful woman.");
            wood2.Receive("Vincent Van Gogh", "A painting of a starry night.");
            wood3.Receive("Vincent Van Gogh", "Depicting suffering during the 1937 Spanish Civil War");
            spray1.Receive("Keith Haring", "A spray painting of friends shoulder to shoulder");
            spray2.Receive("Keith Haring", "A spray painting of a DJ bringing the beats");
            spray3.Receive("Keith Haring", "A spray painting of barking dogs");

            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Mediator class
    public abstract class AbstractMuseum
    {
        public abstract void Register(Painting painting);
        public abstract void Display(string artist, string type, string description);
    }

    // Concrete Mediator
    public class Museum : AbstractMuseum
    {
        private Dictionary<string, Painting> paintings = new Dictionary<string, Painting>();

        public override void Register(Painting painting)
        {
            if (!paintings.ContainsValue(painting))
            {
                paintings[painting.Name] = painting;
            }
            painting.Museum = this;
        }

        public override void Display(string artist, string type, string description)
        {
            Painting painting = paintings[type];
            if(painting != null)
            {
                painting.Receive(artist, description);
            }
        }
    }

    // AbstractColleague
    public class Painting
    {
        Museum museum;
        string name;

        // Constructor
        public Painting(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }

        public Museum Museum
        {
            get { return museum; }
            set { museum = value; }
        }

        public void Display(string type, string description)
        {
            museum.Display(name, type, description);
        }

        public virtual void Receive(string artist, string description)
        {
            Console.WriteLine("From {0} is the painting named {1}: '{2}'", artist, Name, description);
        }
    }

    // ConcreteColleague
    public class MetalSpray : Painting
    {
        public MetalSpray(string name) : base(name) { }
        public override void Receive(string artist, string description)
        {
            Console.Write("To a metal spray painting: ");
            base.Receive(artist, description);
        }
    }

    // ConcreteColleague
    public class WoodOil : Painting
    {
        public WoodOil(string name) : base(name) { }
        public override void Receive(string artist, string description)
        {
            Console.Write("To a wood oil painting: ");
            base.Receive(artist, description);
        }
    }
}
