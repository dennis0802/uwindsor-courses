using System;
using System.Collections.Generic;
using System.Text;

namespace ChainOfResponsibility
{
    /**
     * In summary:
     * Coupling the sender of a request to its receiver can be avoided by giving handlers a chance to handle
     * The handlers are chained until one can handle it.
     * There are requests to appraise paintings and depending on the cost, one of the appraisers will handle it.
     * Directors, Vice Presidents, and Presidents are the concrete handlers.
     */
    class Chain
    {
        public Chain()
        {
            // Setup chain of responsibility
            Appraiser bri = new Director();
            Appraiser teena = new Director();
            Appraiser kate = new VicePresident();
            Appraiser madison = new President();

            bri.SetSuccessor(kate);
            teena.SetSuccessor(kate);
            kate.SetSuccessor(madison);

            // Generate and process requests
            Appraisal a = new Appraisal(100, 350.00, "Watercolor");
            bri.ProcessRequest(a);

            a = new Appraisal(101, 400.00, "Watercolor");
            teena.ProcessRequest(a);

            a = new Appraisal(102, 20000.00, "Renaissance");
            bri.ProcessRequest(a);

            a = new Appraisal(103, 40000.0, "Baroque");
            teena.ProcessRequest(a);

            a = new Appraisal(104, 100000.0, "Modernism");
            bri.ProcessRequest(a);
            
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Handler
    public abstract class Appraiser
    {
        protected Appraiser successor;
        public void SetSuccessor(Appraiser successor)
        {
            this.successor = successor;
        }

        public abstract void ProcessRequest(Appraisal appraise);
    }

    // Concrete Handler
    public class Director : Appraiser
    {
        public override void ProcessRequest(Appraisal appraise)
        {
            if(appraise.Amt < 10000.0)
            {
                Console.WriteLine("{0} approved request #{1}", this.GetType().Name, appraise.Num);
            }
            else if(successor != null)
            {
                successor.ProcessRequest(appraise);
            }
        }
    }

    // Concrete Handler
    public class VicePresident : Appraiser
    {
        public override void ProcessRequest(Appraisal appraise)
        {
            if (appraise.Amt < 25000.0)
            {
                Console.WriteLine("{0} approved request #{1}", this.GetType().Name, appraise.Num);
            }
            else if (successor != null)
            {
                successor.ProcessRequest(appraise);
            }
        }
    }

    // Concrete Handler
    public class President : Appraiser
    {
        public override void ProcessRequest(Appraisal appraise)
        {
            if (appraise.Amt < 100000.0)
            {
                Console.WriteLine("{0} approved request #{1}", this.GetType().Name, appraise.Num);
            }
            else 
            {
                Console.Write("Request #{0} requires an executive meeting!", appraise.Num);
            }
        }
    }

    // Request details
    public class Appraisal
    {
        int num;
        double amt;
        string paintingType;

        public Appraisal(int num, double amt, string paintingType)
        {
            this.num = num;
            this.amt = amt;
            this.paintingType = paintingType;
        }

        public int Num
        {
            get { return num; }
            set { num = value; }
        }

        public double Amt
        {
            get { return amt; }
            set { amt = value; }
        }

        public string PaintingType
        {
            get { return paintingType; }
            set { paintingType = value; }
        }
    }

}
