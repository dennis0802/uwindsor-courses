using System;
using System.Collections.Generic;
using System.Text;

namespace FactoryBridgePattern
{
    /* 
     * In summary:
     * A combination of the Factory and Bridge patterns
     * Abstract factories make the Paintings and Frames
     * The drawing is still separated from the Picture
     * Drawing types are refined drawings
     */
    class FactoryBridge
    {
        public FactoryBridge()
        {
            Console.Write("Please enter picture type (oil/spray): ");
            Client client = new Client();
            string pictureType = Console.ReadLine();
            client.CreatePictureWithFrame(pictureType);
            Console.ReadKey(true);
            Console.WriteLine("");
        }
    }

    class Client
    {
        private AbstractFactory abstractFactory = null;
        public void CreatePictureWithFrame(string pictureName)
        {
            switch (pictureName.ToLower())
            {
                case "oil": abstractFactory = new WoodOil(); break;
                case "spray": abstractFactory = new MetalSpray(); break;
                default: Console.WriteLine("Sorry, wrong input!"); break;
            }
            Console.Write($"{abstractFactory.GetPaint().GetPictureInfo()}");
            Console.WriteLine($"{abstractFactory.GetFrame().GetFrameInfo()}");
        }
    }

    //-----------------------------------------
    // Abstract Factory
    public abstract class AbstractFactory
    {
        protected AbstractPicture paint;
        protected Drawing drawing;
        public abstract AbstractPicture GetPaint();
        public abstract AbstractFrame GetFrame();
    }

    // Concerte Factory 1
    public class WoodOil : AbstractFactory
    {
        public override AbstractPicture GetPaint()
        {
            drawing = new BrushDraw();
            paint = new OilPaint(drawing);
            Console.Write("For oil painting, ");
            paint.draw();
            return new OilPaint(drawing);
        }

        public override AbstractFrame GetFrame()
        {
            return new CarvedWood();
        }
    }

    // Concrete Factory 2
    public class MetalSpray : AbstractFactory
    {
        public override AbstractPicture GetPaint()
        {
            drawing = new BrushDraw();
            paint = new SprayPaint(drawing);
            Console.Write("For spray painting, ");
            paint.draw();
            return new SprayPaint(drawing);
        }

        public override AbstractFrame GetFrame()
        {
            return new MetalFrame();
        }
    }

    //-----------------------------------------
    // Abstract Product A - Frame Info
    public interface AbstractFrame
    {
        string GetFrameInfo();
    }

    // Product A1
    public class CarvedWood : AbstractFrame
    {
        public string GetFrameInfo()
        {
            return "to be placed in a beautiful carved wooden frame.";
        }
    }

    // Product A2
    public class MetalFrame : AbstractFrame
    {
        public string GetFrameInfo()
        {
            return "to be placed in a durable metal frame.";
        }
    }

    //-----------------------------------------
    // Abstract Product B - Picture/Paint Info
    public abstract class AbstractPicture
    {
        abstract public void draw();
        abstract public string GetPictureInfo();
        protected Drawing my_drawing;

        public AbstractPicture(Drawing drawing) { my_drawing = drawing; }
        public void draft_picture() { my_drawing.draft_picture(); }
        public void color_picture() { my_drawing.color_picture(); }
    }

    // Product B1
    public class OilPaint : AbstractPicture
    {
        public OilPaint(Drawing drawing) : base(drawing) { }
        public override void draw()
        {
            draft_picture();
            color_picture();
        }
        public override string GetPictureInfo()
        {
            return "It produces an oil painting, ";
        }
    }

    // Product B2
    public class SprayPaint : AbstractPicture
    {
        public SprayPaint(Drawing drawing) : base(drawing) { }
        public override void draw()
        {
            draft_picture();
            color_picture();
        }
        public override string GetPictureInfo()
        {
            return "It produces a spray painting, ";
        }
    }

    //-----------------------------------------
    // Drawing
    public abstract class Drawing
    {
        abstract public void draft_picture();
        abstract public void color_picture();
    }

    public class BrushDraw : Drawing
    {
        public override void draft_picture()
        {
            Console.Write("draft with light color ");
        }
        public override void color_picture()
        {
            Console.WriteLine("and color with brushes.");
        }
    }

    public class CanSpray : Drawing
    {
        public override void draft_picture()
        {
            Console.Write("draft with a pencil ");
        }
        public override void color_picture()
        {
            Console.WriteLine("and color with spray cans.");
        }
    }
}
