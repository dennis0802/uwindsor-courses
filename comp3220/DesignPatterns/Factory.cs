using System;
using System.Collections.Generic;
using System.Text;

namespace FactoryPattern
{
    /* 
     * In summary:
     * Factories implement from the abstract factory
     * Here, BookFactory and ProductFactory makes instances of OrderItems (concrete products)
     * The Products are the Books and Painting types
     */
    class Factory
    {
        public Factory()
        {
            ProductOrder p = new ProductOrder();
            p.GetPrice();
            Console.WriteLine("");
        }
    }

    class OrderItem
    {
        protected double price;
        protected String type;
        public OrderItem(double p_tmp) { }
        public double GetItemPrice() { return price; }
        public String GetItemType() { return type; }
        public double RandomPrice(double min, double max)
        {
            Random random = new Random();
            return random.NextDouble() * (max - min) + min;
        }
    }

    class BookCopy : OrderItem
    {
        public BookCopy(String name, double d) : base(d) { price = d; type = name; }
    }
    class SprayPaint : OrderItem
    {
        public SprayPaint(String name, double d) : base(d) { price = d; type = name; }
    }

    class OilPaint : OrderItem
    {
        public OilPaint(String name, double d) : base(d) { price = d; type = name; }
    }

    class MetalFrame : OrderItem
    {
        public MetalFrame(String name, double d) : base(d) { price = d; type = name;}
    }

    class CarvedWood : OrderItem
    {
        public CarvedWood(String name, double d) : base(d) { price = d; type = name; }
    }

    class MetalSpray : OrderItem
    {
        public MetalSpray(String name, double d) : base(0)
        {
            var metal = new MetalFrame(name, d);
            var spray = new SprayPaint(name, d);
            price = metal.GetItemPrice() + spray.GetItemPrice();
            type = name;
        }
    }

    class WoodOil : OrderItem
    {
        public WoodOil(String name, double d) : base(0)
        {
            var wood = new CarvedWood(name, d);
            var oil = new OilPaint(name, d);
            price = wood.GetItemPrice() + oil.GetItemPrice();
            type = name;
        }
    }

    class ProductOrder
    {
        int item_num;
        OrderItem[] orderItem = new OrderItem[20];
        Random random = new Random();

        public ProductOrder()
        {
            ProductFactory factory;
            item_num = random.Next(15, 21);
            String[] name = new string[7];
            for (int i = 0; i < item_num; i++)
            {
                double d_tmp = Math.Round(random.NextDouble() * 100, 2);
                int tmp = random.Next(0, 7);

                if(tmp < 1)
                {
                    name[tmp] = "book";
                    factory = new BookFactory();
                }
                else
                {
                    switch (tmp)
                    {
                        case 1: name[tmp] = "spray";  break;
                        case 2: name[tmp] = "oil"; break;
                        case 3: name[tmp] = "metal"; break;
                        case 4: name[tmp] = "wood"; break;
                        case 5: name[tmp] = "metal_spray"; break;
                        case 6: name[tmp] = "wood_oil"; break;
                        default: break;
                    }
                    factory = new ArtFactory();
                }
                orderItem[i] = factory.MakeProduct(name[tmp], d_tmp);
            }
        }

        public void GetPrice()
        {
            double price = 0.0;
            int count;
            String[] names = { "book", "spray", "oil", "metal", "wood", "metal_spray", "wood_oil" };
            
            // Output to the screen
            Console.WriteLine("There are " + item_num + " items:");
            for (int i = 0; i < 7; i++)
            {
                count = CountTypes(names[i]);
                Console.Write(names[i] + "("+count+"):");
                for (int j = 0; j < item_num; j++)
                {
                    if (orderItem[j].GetItemType() == names[i])
                    {
                        Console.Write(" $" + orderItem[j].GetItemPrice() + " ");
                    }
                }
                Console.Write("\n");
            }

            // Get the price
            for (int i = 0; i < item_num; i++)
            {
                if (orderItem[i] == null)
                {
                    continue;
                }
                price += orderItem[i].GetItemPrice();
            }
            Console.WriteLine("The total price is $" + Math.Round(price,2));
        }

        public int CountTypes(string name)
        {
            int count = 0;
            for(int i = 0; i < item_num; i++)
            {
                if(orderItem[i].GetItemType() == name)
                {
                    count++;
                }
            }
            return count;
        }
    }

    abstract class ProductFactory
    {
        public abstract OrderItem MakeProduct(string name, double price);
    }

    class BookFactory : ProductFactory
    {
        public override OrderItem MakeProduct(string name, double d)
        {
            return new BookCopy(name, d);
        }
    }

    class ArtFactory : ProductFactory
    {
        public override OrderItem MakeProduct(string name, double d)
        {
            switch (name)
            {
                case "spray": return new SprayPaint(name, d);
                case "oil": return new OilPaint(name, d);
                case "metal": return new MetalFrame(name, d);
                case "wood": return new CarvedWood(name, d);
                case "metal_spray": return new MetalSpray(name, d);
                case "wood_oil": return new WoodOil(name, d);
                default: return null;
            }
        }
    }
}
