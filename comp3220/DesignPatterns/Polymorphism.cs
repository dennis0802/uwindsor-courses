using System;
using System.Collections.Generic;
using System.Text;

namespace PolymorphismPattern
{
    class Polymorphism
    {
        public Polymorphism()
        {
            ProductOrder p = new ProductOrder();
            p.GetPrice();
            Console.WriteLine("");
        }
    }

    /* 
     * In summary:
     * OrderItems can be many specific (child) classes of the generalized OrderItem class
     */

    class OrderItem
    {
        protected double price;
        protected String type;
        public OrderItem(double p_tmp) { }
        public String GetItemType() { return type; }
        public double GetItemPrice() { return price; }
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
        public MetalFrame(String name, double d) : base(d) { price = d; type = name; }
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

        public ProductOrder()
        {
            MakeOrder();
        }

        private void MakeOrder()
        {
            Random random = new Random();
            double d_tmp;
            int tmp;

            item_num = random.Next(15, 21);
            String[] name = new string[item_num];
            for (int i = 0; i < item_num; i++)
            {
                d_tmp = Math.Round(random.NextDouble() * 100, 2);
                tmp = random.Next(0, 7);

                switch (tmp)
                {
                    case 0: name[tmp] = "book"; break;
                    case 1: name[tmp] = "spray"; break;
                    case 2: name[tmp] = "oil"; break;
                    case 3: name[tmp] = "metal"; break;
                    case 4: name[tmp] = "wood"; break;
                    case 5: name[tmp] = "metal_spray"; break;
                    case 6: name[tmp] = "wood_oil"; break;
                    default: name[tmp] = "none"; break;
                }

                switch (name[tmp])
                {
                    case "book": orderItem[i] = new BookCopy(name[tmp], d_tmp); break;
                    case "spray": orderItem[i] = new SprayPaint(name[tmp], d_tmp); break;
                    case "oil": orderItem[i] = new OilPaint(name[tmp], d_tmp); break;
                    case "metal": orderItem[i] = new MetalFrame(name[tmp], d_tmp); break;
                    case "wood": orderItem[i] = new CarvedWood(name[tmp], d_tmp); break;
                    case "metal_spray": orderItem[i] = new MetalSpray(name[tmp], d_tmp); break;
                    case "wood_oil": orderItem[i] = new WoodOil(name[tmp], d_tmp); break;
                    default: break;
                }
            }
        }

        public void GetPrice()
        {
            int count;
            double price = 0.0;
            String[] names = { "book", "spray", "oil", "metal", "wood", "metal_spray", "wood_oil" };
            Console.WriteLine("There are " + item_num + " items:");
            for (int i = 0; i < 7; i++)
            {
                count = CountTypes(names[i]);
                Console.Write(names[i] + "(" + count + "):");
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
            Console.WriteLine("The total price is $" + Math.Round(price, 2));
        }
        public int CountTypes(string name)
        {
            int count = 0;
            for (int i = 0; i < item_num; i++)
            {
                if (orderItem[i].GetItemType() == name)
                {
                    count++;
                }
            }
            return count;
        }
    }
}
