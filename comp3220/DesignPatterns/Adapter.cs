using System;
using System.Collections.Generic;
using System.Text;

namespace AdapterPattern
{
    /**
     * In summary, the adapter will allow the adaptee to work with other classes due to incompatible interfaces
     * The target is a painting, the adapter is the finished painting, the painting databank is the adaptee
     * The finished painting allows the painting databank to adapt to the painting.
     */
    class Adapter
    {
        public Adapter()
        {
            // Non-adapted painting
            Painting unknown = new Painting();
            unknown.Display();

            // Adapted paintings
            Painting painting1 = new FinishedPainting("Brianna");
            painting1.Display();

            Painting painting2 = new FinishedPainting("Madison");
            painting2.Display();

            Painting painting3 = new FinishedPainting("Ben");
            painting3.Display();
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Target
    public class Painting
    {
        protected double minCost;
        protected double maxCost;
        protected string frame;
        protected string draft;

        // Request
        public virtual void Display()
        {
            Console.WriteLine("\nPainting: Unknown ----- ");
        }
    }

    // Adapter
    public class FinishedPainting : Painting
    {
        private string artist;
        private PaintingBank bank;

        public FinishedPainting(string artist)
        {
            this.artist = artist;
        }

        // Request
        // Adaptee
        public override void Display()
        {
            bank = new PaintingBank();
            minCost = bank.GetMinCost(artist, "Watercolor");
            maxCost = bank.GetMaxCost(artist, "Watercolor");
            frame = bank.GetFrame(artist);
            draft = bank.GetDraft(artist);

            Console.WriteLine("\nArtist: {0} ----- ", artist);
            Console.WriteLine(" Appraised Cost: ${0}-${1}", minCost, maxCost);
            Console.WriteLine(" Frame: {0}", frame);
            Console.WriteLine(" Draft: {0}", draft);
        }
    }

    // Adaptee
    public class PaintingBank
    {
        public double GetMinCost(string artist, string type)
        {
            if(type == "Acrylic")
            {
                switch (artist.ToLower())
                {
                    case "brianna": return 20.0f;
                    case "madison": return 15.0f;
                    case "ben": return 25.0f;
                    default: return 0f;
                }
            }
            else
            {
                switch (artist.ToLower())
                {
                    case "brianna": return 25.0f;
                    case "madison": return 20.0f;
                    case "ben": return 30.0f;
                    default: return 0f;
                }
            }
        }

        public double GetMaxCost(string artist, string type)
        {
            Random r = new Random();
            if (type == "Acrylic")
            {
                switch (artist.ToLower())
                {
                    case "brianna": return Math.Round(r.NextDouble() * (100-25)+25,2);
                    case "madison": return Math.Round(r.NextDouble() * (100-20)+20,2);
                    case "ben": return Math.Round(r.NextDouble() * (100-30)+30, 2);
                    default: return 0f;
                }
            }
            else
            {
                switch (artist.ToLower())
                {
                    case "brianna": return Math.Round(r.NextDouble() * (100 - 25) + 30, 2);
                    case "madison": return Math.Round(r.NextDouble() * (100 - 20) + 25, 2);
                    case "ben": return Math.Round(r.NextDouble() * (100 - 30) + 35, 2);
                    default: return 0f;
                }
            }
        }

        public string GetFrame(string artist)
        {
            switch (artist.ToLower())
            {
                case "brianna": return "anime";
                case "madison": return "baroque";
                case "ben": return "wood";
                default: return "none";
            }
        }

        public string GetDraft(string artist)
        {
            switch (artist.ToLower())
            {
                case "brianna": return "solar dye and embroidery";
                case "madison": return "pen";
                case "ben": return "pencil";
                default: return "none";
            }
        }
    }
}
