using System;
using System.Collections.Generic;
using System.Text;

namespace ProxyPattern
{
    /**
     * In summary:
     * Provides a placeholder for another object to control access
     * A proxy object accesses the real subject, the Painting.
     * Paintings are what the proxy represents
     * The PaintingInterface defines the interface for the Real subject and the Proxy
     */
    class Proxy
    {
        public Proxy()
        {
            // Create proxy
            PaintingProxy proxy = new PaintingProxy();

            // Add color
            Console.WriteLine("Painting added color: " + proxy.AddRed());
            Console.WriteLine("Painting added color: " + proxy.AddBlue());
            Console.WriteLine("Painting added color: " + proxy.AddYellow());
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Subject
    public interface PaintingInterface
    {
        string AddRed();
        string AddBlue();
        string AddYellow();
    }

    // RealSubject
    public class Painting : PaintingInterface
    {
        public string AddRed() { return "red"; }
        public string AddBlue() { return "blue"; }
        public string AddYellow() { return "yellow"; }
    }

    // Proxy Object
    public class PaintingProxy : PaintingInterface
    {
        private Painting painting = new Painting();

        public string AddRed() { return painting.AddRed(); }
        public string AddBlue() { return painting.AddBlue(); }
        public string AddYellow() { return painting.AddYellow(); }
    }
}
