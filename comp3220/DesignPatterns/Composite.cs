using System;
using System.Collections.Generic;
using System.Text;

namespace CompositePattern
{
    /**
     * In summary, the object is divided into a tree structure to represent its parts
     * The drawing is a tree of composite elements, whose leaves are part of the composite elements
     * These leaves are the primitive elements of the drawing (shapes and lines)
     */
    class Composite
    {
        public Composite()
        {
            // Tree structure
            CompositeElement root = new CompositeElement("Picture");
            root.Add(new PrimitiveElement("Red Line"));
            root.Add(new PrimitiveElement("Blue Circle"));
            root.Add(new PrimitiveElement("Green Box"));

            // Branch
            CompositeElement comp = new CompositeElement("Two Circles");
            comp.Add(new PrimitiveElement("Black Circle"));
            comp.Add(new PrimitiveElement("White Circle"));
            root.Add(comp);

            // Add and remove primitive
            PrimitiveElement pe = new PrimitiveElement("Yellow Line");
            root.Add(pe);
            root.Remove(pe);

            root.Display(1);
            Console.Write("\n");
            Console.ReadKey();

        }

        // Component
        public abstract class DrawingElement
        {
            protected string name;

            public DrawingElement(string name)
            {
                this.name = name;
            }

            public abstract void Add(DrawingElement d);
            public abstract void Remove(DrawingElement d);
            public abstract void Display(int indent);
        }

        // Leaf
        public class PrimitiveElement : DrawingElement
        {
            public PrimitiveElement(string name) : base(name)
            {

            }

            public override void Add(DrawingElement c)
            {
                Console.WriteLine("Cannot add to a Primitive Element");
            }
            public override void Remove(DrawingElement c)
            {
                Console.WriteLine("Cannot remove from a Primitive Element");
            }
            public override void Display(int indent)
            {
                Console.WriteLine(new String('-', indent) + " " + name);
            }
        }

        // Composite
        public class CompositeElement : DrawingElement
        {
            List<DrawingElement> elements = new List<DrawingElement>();

            public CompositeElement(string name) : base(name)
            {

            }
            public override void Add(DrawingElement d)
            {
                elements.Add(d);
            }
            public override void Remove(DrawingElement d)
            {
                elements.Remove(d);
            }
            public override void Display(int indent)
            {
                Console.WriteLine(new String('-', indent) + " " + name);

                // Display children
                foreach(DrawingElement d in elements)
                {
                    d.Display(indent + 2);
                }
            }
        }
    }
}
