using System;
using System.Collections.Generic;
using System.Text;

namespace FacadePattern
{
    /**
     * In summary:
     * Provides a unified interface to a set of interfaces in a subsystem
     * The painting provides a unified interface to the interfaces for Frame, Draft, and Oil
     */
    class Facade
    {
        public Facade()
        {
            Painting painting = new Painting();

            Customer customer = new Customer("Brianna Bucases");
            bool eligible = painting.IsSellable(customer, "carved wood", "light color", "oil");
            Console.WriteLine("\n" + customer.Name + " has been " + (eligible ? "Approved" : "Rejected"));
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Subsystem
    public class Frame
    {
        public bool HasGoodFrame(Customer c, string frame)
        {
            Console.WriteLine("Check database for " + c.Name + " seeking a " + frame);
            return true;
        }
    }

    public class Draft
    {
        public bool HasGoodDraft(Customer c, string draft)
        {
            Console.WriteLine("Check database for " + c.Name + " seeking a " + draft);
            return true;
        }
    }

    public class PaintingType
    {
        public bool HasGoodType(Customer c, string type)
        {
            Console.WriteLine("Check database for " + c.Name + " seeking a " + type);
            return true;
        }
    }

    // Customer
    public class Customer
    {
        private string name;

        public Customer(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }
    }

    // Facade
    public class Painting
    {
        Frame frame = new Frame();
        Draft draft = new Draft();
        PaintingType type = new PaintingType();
        
        // Check worthiness of selling this painting
        public bool IsSellable(Customer c, string frame, string draft, string type)
        {
            Console.WriteLine("{0} is looking for a painting: {1}, {2}, {3}", c.Name, frame, draft, type);
            bool eligible = true;

            if (!this.frame.HasGoodFrame(c, frame))
            {
                eligible = false;
            }
            else if(!this.draft.HasGoodDraft(c, draft))
            {
                eligible = false;
            }
            else if(!this.type.HasGoodType(c, type))
            {
                eligible = false;
            }

            return eligible;
        }
    }
}
