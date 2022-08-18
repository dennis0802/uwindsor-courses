using System;
using System.Collections.Generic;
using System.Text;

namespace TemplatePattern
{
    /**
     * In summary:
     * The skeleton of the algorithm can be defined in an operation and steps deferred to subclasses
     * Subclasses can redefine steps without changing the structure
     * A template is provided to create, add, process, and disconnect a list of Frames and a list of Painting types
     */
    class Template
    {
        public Template()
        {
            DataAccessor paintingTypes = new PaintingTypes();
            paintingTypes.Run(5);

            DataAccessor frameTypes = new Frames();
            frameTypes.Run(4);

            Console.WriteLine();
            Console.ReadKey();
        }
    }

    // AbstractClass
    public abstract class DataAccessor
    {
        public abstract void Connect();
        public abstract void Select();
        public abstract void Process(int top);
        public abstract void Disconnect();

        // Template method
        public void Run(int top)
        {
            Connect();
            Select();
            Process(top);
            Disconnect();
        }
    }

    // ConcreteClass
    public class PaintingTypes : DataAccessor
    {
        private List<string> types;

        public override void Connect()
        {
            types = new List<string>();
        }

        public override void Select()
        {
            types.Add("Watercolor");
            types.Add("Acrylic");
            types.Add("Oil");
            types.Add("Spray");
            types.Add("Marker");
            types.Add("Chalk");
            types.Add("Pastel");
            types.Add("Digital");
        }

        public override void Process(int top)
        {
            Console.WriteLine("Mediums ---- ");

            for(int i = 0; i < top; i++)
            {
                Console.WriteLine(types[i]);
            }
            Console.WriteLine();
        }

        public override void Disconnect()
        {
            types.Clear();
        }
    }

    // ConcreteClass
    public class Frames : DataAccessor
    {
        private List<string> types;

        public override void Connect()
        {
            types = new List<string>();
        }

        public override void Select()
        {
            types.Add("Oak");
            types.Add("Silver");
            types.Add("Birch");
            types.Add("Plastic");
            types.Add("Pine");
            types.Add("Bronze");
            types.Add("Copper");
            types.Add("None");
        }

        public override void Process(int top)
        {
            Console.WriteLine("Frames ---- ");

            for (int i = 0; i < top; i++)
            {
                Console.WriteLine(types[i]);
            }
            Console.WriteLine();
        }

        public override void Disconnect()
        {
            types.Clear();
        }
    }


}
