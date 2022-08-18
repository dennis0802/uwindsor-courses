using System;
using System.Collections.Generic;
using System.Text;

namespace MementoPattern
{
    /**
     * In summary:
     * The internal state of painting can be saved and restored later, without violating encapsulation
     */
    class MementoRun
    {
        public MementoRun()
        {
            Painting p = new Painting();
            p.Draft = "in paper with pencil";
            p.Frame = "in a beautifully carved wooden frame";

            // Store state
            PaintingMemory m = new PaintingMemory();
            m.Memento = p.SaveMemento();

            // Change originator
            p.Draft = "in light color";
            p.Frame = "in a durable metal frame";

            // Restore state
            p.RestoreMemento(m.Memento);

            Console.WriteLine();
            Console.ReadKey();
        }
    }

    // Originator
    public class Painting
    {
        string frame;
        string draft;

        public string Draft
        {
            get { return draft; }
            set
            {
                draft = value;
                Console.WriteLine("Draft: " + draft);
            }
        }

        public string Frame
        {
            get { return frame; }
            set
            {
                frame = value;
                Console.WriteLine("Frame: " + frame);
            }
        }

        public Memento SaveMemento()
        {
            Console.WriteLine("\nSaving painting state ---\n");
            return new Memento(draft, frame);
        }

        public void RestoreMemento(Memento memento)
        {
            Console.WriteLine("\nRestoring painting state ---\n");
            Frame = memento.Frame;
            Draft = memento.Draft;
        }
    }

    // Memento
    public class Memento
    {
        string draft;
        string frame;

        public Memento(string draft, string frame)
        {
            this.draft = draft;
            this.frame = frame;
        }

        public string Draft
        {
            get { return draft; }
            set { draft = value; }
        }

        public string Frame
        {
            get { return frame; }
            set { frame = value; }
        }
    }

    // Caretaker
    public class PaintingMemory
    {
        Memento memento;

        public Memento Memento
        {
            set { memento = value; }
            get { return memento; }
        }
    }
    
}
