using System;
using System.Collections.Generic;
using System.Text;

namespace BuilderPattern
{
    /* 
     * In summary:
     * The ArtShop directs the PaintingBuilder
     * PaintingBuilder is the abstract interface for paintings
     * WoodOilBuilders and MachineSprayBuilders build pieces of the product
     * Paintings are the complex object to be built
     */
    class Builder
    {
        public Builder()
        {
            PaintingBuilder builder;
            ArtShop artShop = new ArtShop();

            builder = new WoodOilBuilder();
            artShop.Construct(builder);
            builder.Painting.Show();

            builder = new MachineSprayBuilder();
            artShop.Construct(builder);
            builder.Painting.Show();

            Console.ReadKey();
        }
    }

    class ArtShop
    {
        public void Construct(PaintingBuilder paintingBuilder)
        {
            paintingBuilder.BuildDrawing();
            paintingBuilder.BuildFrame();
        }
    }

    abstract class PaintingBuilder
    {
        protected Painting painting;
        public Painting Painting
        {
            get
            {
                return painting;
            }
        }

        public abstract void BuildDrawing();
        public abstract void BuildFrame();
            
    }

    class MachineSprayBuilder : PaintingBuilder
    {
        public MachineSprayBuilder()
        {
            painting = new Painting("MachineSpray");
        }

        public override void BuildDrawing()
        {
            painting["drawing"] = "Drafted with a pencil ";
        }

        public override void BuildFrame()
        {
            painting["frame"] = "To be placed in a durable metal frame.";
        }
    }

    class WoodOilBuilder : PaintingBuilder
    {
        public WoodOilBuilder()
        {
            painting = new Painting("WoodOil");
        }

        public override void BuildDrawing()
        {
            painting["drawing"] = "Drafted with light color ";
        }

        public override void BuildFrame()
        {
            painting["frame"] = "To be placed in a beautiful carved wooden frame.";
        }
    }

    class Painting
    {
        private string paintingType;
        private Dictionary<string, string> parts = new Dictionary<string, string>();
        public Painting(string paintingType)
        {
            this.paintingType = paintingType;
        }

        public string this[string key]
        {
            get { return parts[key]; }
            set { parts[key] = value; }
        }

        public void Show()
        {
            Console.WriteLine("Painting type: {0}", paintingType);
            Console.WriteLine(parts["drawing"]);
            Console.WriteLine(parts["frame"]);
            Console.WriteLine("");
        }
    }
}
