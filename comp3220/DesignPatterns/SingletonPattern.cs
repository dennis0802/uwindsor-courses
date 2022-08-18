using System;
using System.Collections.Generic;
using System.Text;

namespace Singleton
{
    /**
     * In summary:
     * There will be only one instance of the class - all paintings here refer to the same one.
     */
    class SingletonPattern
    {
        public SingletonPattern()
        {
            Painting p1 = Painting.GetPainting();
            Painting p2 = Painting.GetPainting();
            Painting p3 = Painting.GetPainting();
            Painting p4 = Painting.GetPainting();

            if(p1 == p2 && p2 == p3 && p3 == p4)
            {
                Console.WriteLine("Same instance\n");
            }

            Painting paintings = Painting.GetPainting();
            for(int i = 0; i < 15; i++)
            {
                string color = paintings.Color;
                Console.WriteLine("Color for painting: " + color);
            }

            Console.ReadKey();
            Console.WriteLine("");
        }
    }

    public class Painting
    {
        static Painting instance;
        List<string> colors = new List<string>();
        private static object picture = new object();
        Random r = new Random();

        protected Painting()
        {
            colors.Add("Red");
            colors.Add("Yellow");
            colors.Add("Blue");
        }

        public static Painting GetPainting()
        {
            if(instance == null)
            {
                lock (picture) ;
                if(instance == null)
                {
                    instance = new Painting();
                }
            }
            return instance;
        }

        public string Color
        {
            get
            {
                int index = r.Next(colors.Count);
                return colors[index].ToString();
            }
        }
    }
}
