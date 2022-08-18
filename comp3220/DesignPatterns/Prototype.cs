using System;
using System.Collections.Generic;
using System.Text;

namespace PrototypePattern
{
    /*
     * In summary:
     * The PaintingPrototype is an interface allows itself to be cloned.
     * Paintings are concrete products that can clone itself
     * The PaintingManager creates objects by asking the PaintingPrototype to clone itelf.
     */
    class Prototype
    {
        public Prototype()
        {
            PaintingManager pm = new PaintingManager();

            pm["Acrylic"] = new Painting("Acrylic");
            pm["Oil"] = new Painting("Oil");
            pm["Watercolor"] = new Painting("Watercolor");

            Painting painting1 = pm["Acrylic"].Clone() as Painting;
            Painting painting2 = pm["Oil"].Clone() as Painting;
            Painting painting3 = pm["Watercolor"].Clone() as Painting;
            Console.ReadKey();
            Console.WriteLine("");
        }
    }

    public abstract class PaintingPrototype
    {
        public abstract PaintingPrototype Clone();
    }

    public class Painting : PaintingPrototype
    {
        string type;

        public Painting(string type)
        {
            this.type = type;
        }

        public override PaintingPrototype Clone()
        {
            Console.WriteLine("Cloning painting:");
            Console.WriteLine(type);

            return this.MemberwiseClone() as PaintingPrototype;
        }
    }

    public class PaintingManager
    {
        private Dictionary<string, PaintingPrototype> paintings = new Dictionary<string, PaintingPrototype>();

        // Indexer
        public PaintingPrototype this[string key]
        {
            get { return paintings[key]; }
            set { paintings.Add(key, value); }
        }
    }
}
