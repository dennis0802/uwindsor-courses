using System;
using System.Collections.Generic;
using System.Text;

namespace IteratorPattern
{
    /**
     * In summary:
     * Access the elements of an aggregate object without exposing the underlying representation
     * Iterators traverse the collection of colors. Both the iterator and collection are based off their abstract versions 
     */
    class IteratorRun
    {
        public IteratorRun()
        {
            Collection collection = new Collection();
            collection[0] = new Color("Red");
            collection[1] = new Color("Orange");
            collection[2] = new Color("Yellow");
            collection[3] = new Color("Green");
            collection[4] = new Color("Blue");
            collection[5] = new Color("Violet");
            collection[6] = new Color("Black");
            collection[7] = new Color("White");
            collection[8] = new Color("Brown");

            Iterator iterator = collection.CreateIterator();
            iterator.Step = 2;

            Console.WriteLine("Iterating over color collection:");
            for (Color color = iterator.First() ; !iterator.IsDone; color = iterator.Next())
            {
                Console.WriteLine(color.Name);
            }
            Console.Write("\n");
            Console.ReadKey();
        }

    }

    // Collection item
    public class Color
    {
        string name;

        public Color(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }
    }

    // Aggregate
    public interface IAbstractCollection
    {
        Iterator CreateIterator();
    }

    // ConcreteAggregate
    public class Collection : IAbstractCollection
    {
        List<Color> colors = new List<Color>();

        public Iterator CreateIterator()
        {
            return new Iterator(this);
        }

        public int Count
        {
            get { return colors.Count; }
        }

        public Color this[int index]
        {
            get { return colors[index]; }
            set { colors.Add(value); }
        }
    }

    // Iterator
    public interface IAbstractIterator
    {
        Color First();
        Color Next();
        bool IsDone { get; }
        Color CurrentColor { get; }
    }

    // Concrete Iterator
    public class Iterator : IAbstractIterator
    {
        Collection collection;
        int current = 0, step = 1;

        public Iterator(Collection collection)
        {
            this.collection = collection;
        }

        public Color First()
        {
            current = 0;
            return collection[current] as Color;
        }

        public Color Next()
        {
            current += step;
            if (!IsDone)
            {
                return collection[current] as Color;
            }
            else
            {
                return null;
            }
        }

        public int Step
        {
            get { return step; }
            set { step = value; }
        }

        public Color CurrentColor
        {
            get { return collection[current] as Color; }
        }

        public bool IsDone
        {
            get { return current >= collection.Count; }
        }
    }
}
