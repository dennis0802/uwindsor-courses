using System;
using System.Collections.Generic;
using System.Text;

namespace StrategyPattern
{
    class Strategy
    {
        /**
         * In summary:
         * A family of algorithms can be defined, encapslated, and interchangeable.
         * The sorting method for the list of paintings can vary depending on the client.
         */
        public Strategy()
        {
            SortedList paintings = new SortedList();
            paintings.Add("Mona Lisa");
            paintings.Add("Starry Night");
            paintings.Add("Guernica");
            paintings.Add("DJ");
            paintings.Add("Birth of Venus");

            paintings.SetSortStrategy(new QuickSort());
            paintings.Sort();

            paintings.SetSortStrategy(new QuickSort());
            paintings.Sort();

            paintings.SetSortStrategy(new QuickSort());
            paintings.Sort();

            Console.WriteLine();
            Console.ReadKey();
        }
    }

    // Strategy
    public abstract class SortStrategy
    {
        public abstract void Sort(List<string> list);
    }

    // Concrete Strategy
    public class QuickSort : SortStrategy
    {
        public override void Sort(List<string> list)
        {
            list.Sort(); // default is QuickSort
            Console.WriteLine("QuickSorted list: ");
        }
    }

    // Concrete Strategy
    public class ShellSort : SortStrategy
    {
        public override void Sort(List<string> list)
        {
            //list.Sort();
            Console.WriteLine("ShellSorted list: ");
        }
    }

    // Concrete Strategy
    public class MergeSort : SortStrategy
    {
        public override void Sort(List<string> list)
        {
            //list.Sort(); 
            Console.WriteLine("MergeSorted list: ");
        }
    }

    // Context
    public class SortedList
    {
        private List<string> list = new List<string>();
        private SortStrategy sortStrategy;

        public void SetSortStrategy(SortStrategy sortStrategy)
        {
            this.sortStrategy = sortStrategy;
        }

        public void Add(String name)
        {
            list.Add(name);
        }

        public void Sort()
        {
            sortStrategy.Sort(list);

            foreach(string name in list)
            {
                Console.WriteLine(" " + name);
            }
            Console.WriteLine();
        }
    }
}
