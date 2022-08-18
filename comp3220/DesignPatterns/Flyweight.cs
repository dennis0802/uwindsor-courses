using System;
using System.Collections.Generic;
using System.Text;

namespace FlyweightPattern
{
    /**
     * In summary:
     * Large numbers of fine grained objects can be supported.
     * In art, a sequence of colors may be used - red, blue, and yellow are used in large amounts and are fine grained
     */
    class Flyweight
    {
        public Flyweight()
        {
            // Build a painting with a series of colors
            string colorString = "RBYRBYYBR";
            char[] colors = colorString.ToCharArray();

            ColorFactory factory = new ColorFactory();
            int opacity = 5;

            foreach(char c in colors)
            {
                opacity++;
                Color color = factory.GetColor(c);
                color.Display(opacity);
            }

            Console.WriteLine();
            Console.ReadKey();
        }
    }

    // FlyweightFactory
    public class ColorFactory
    {
        private Dictionary<char, Color> colors = new Dictionary<char, Color>();

        public Color GetColor(char key)
        {
            Color color = null;
            if (colors.ContainsKey(key))
            {
                color = colors[key];
            }
            else
            {
                switch (key)
                {
                    case 'R': color = new Red(); break;
                    case 'B': color = new Blue(); break;
                    case 'Y': color = new Yellow(); break;
                }
                colors.Add(key, color);
            }
            return color;
        }
    }

    // Flyweight
    public abstract class Color
    {
        protected char symbol;
        protected int amt;
        protected int opacity;

        public abstract void Display(int opacity);
    }

    // ConcreteFlyweight
    public class Red : Color
    {
        public Red()
        {
            symbol = 'R';
            amt = 30;
        }

        public override void Display(int opacity)
        {
            this.opacity = opacity;
            Console.WriteLine(symbol + ": Red (opacity " + this.opacity + ")");
        }
    }

    // ConcreteFlyweight
    public class Blue : Color
    {
        public Blue()
        {
            symbol = 'B';
            amt = 30;
        }

        public override void Display(int opacity)
        {
            this.opacity = opacity;
            Console.WriteLine(symbol + ": Blue (opacity " + this.opacity + ")");
        }
    }

    // ConcreteFlyweight
    public class Yellow : Color
    {
        public Yellow()
        {
            symbol = 'Y';
            amt = 30;
        }

        public override void Display(int opacity)
        {
            this.opacity = opacity;
            Console.WriteLine(symbol + ": Yellow (opacity " + this.opacity + ")");
        }
    }
}
