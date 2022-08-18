using System;
using System.Collections.Generic;
using System.Text;

namespace AbstractFactoryPattern
{
    /* 
     * In summary:
     * Factories implement from the abstract factory
     * These factories make the products which implement the abstract products
     * Here, wood oil painting factories and machine spray factories make their respective paintings
     * The picture and frame are products that implement from their abstract product
     */
    class AbstractFactoryRun
    {
        public AbstractFactoryRun()
        {
            Console.Write("Please enter picture type: ");
            Client client = new Client();
            string frame = Console.ReadLine();
            client.CreatePictureWithFrame(frame);
            Console.ReadKey(true);
            Console.WriteLine("");
        }
    }

    class Client
    {
        private AbstractFactory abstractFactory = null;
        public void CreatePictureWithFrame(string pictureName)
        {
            if(pictureName.ToLower() == "oil")
            {
                abstractFactory = new WoodOil();
            }
            else if(pictureName.ToLower() == "spray")
            {
                abstractFactory = new MachineSpray();
            }
            else
            {
                Console.WriteLine("Invalid painting type entered.");
                return;
            }
            Console.Write($"{abstractFactory.GetPicturePaint().GetPictureInfo()}");
            Console.WriteLine($"{abstractFactory.GetPictureFrame().GetFrameInfo()}");
        }
    }

    //-----------------------------------------
    // Abstract Product A - Frame Info
    interface AbstractFrame
    {
        string GetFrameInfo();
    }

    // Product A1
    class CarvedWood : AbstractFrame
    {
        //double price;

        public string GetFrameInfo()
        {
            return "in a beautiful carved wooden frame.";
        }
    }

    // Product A2
    class MetalFrame : AbstractFrame
    {
        //double price;

        public string GetFrameInfo()
        {
            return "in a durable metal frame.";
        }
    }

    //-----------------------------------------
    // Abstract Product B - Picture/Paint Info
    interface AbstractPicture
    {
        string GetPictureInfo();
    }

    // Product B1
    class OilPaint : AbstractPicture
    {
        public string GetPictureInfo()
        {
            return "This is an oil painting, ";
        }
    }

    // Product B2
    class SprayPaint : AbstractPicture
    {
        public string GetPictureInfo()
        {
            return "This is a spray painting, ";
        }
    }

    //-----------------------------------------
    // Abstract Factory
    interface AbstractFactory
    {
        AbstractPicture GetPicturePaint();
        AbstractFrame GetPictureFrame();
    }

    // Concerte Factory 1
    class WoodOil : AbstractFactory
    {
        public AbstractPicture GetPicturePaint()
        {
            return new OilPaint();
        }

        public AbstractFrame GetPictureFrame()
        {
            return new CarvedWood();
        }
    }

    // Concrete Factory 2
    class MachineSpray : AbstractFactory
    {
        public AbstractPicture GetPicturePaint()
        {
            return new SprayPaint();
        }

        public AbstractFrame GetPictureFrame()
        {
            return new MetalFrame();
        }
    }

}
