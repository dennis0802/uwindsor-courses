using System;
using System.Collections.Generic;
using System.Text;

namespace StatePatternRun
{
    /**
     * In summary:
     * The painting type will change state depending on the internal amount of red and blue it has.
     * The behaviour will change (ex. blue will be more likely to interfere on a brush on a red painting)
     */
    class StatePattern
    {
        public StatePattern()
        {
            Painting painting = new Painting("Ben Armaly");

            painting.AddRed(500.0);
            painting.AddRed(300.0);
            painting.AddRed(550.0);
            painting.AddInterference();
            painting.AddBlue(2000.00);
            painting.AddBlue(1100.00);

            Console.Write("");
            Console.ReadKey();
        }
    }

    // State
    public abstract class State
    {
        protected Painting painting;
        // The smaller the value, the more colder and blue it is.
        // The higher the value, the more warm and red it is.
        protected double colorBalance;
        protected double upperLimit;
        protected double lowerLimit;
        protected double balanceChange;
        // For this painting, assume each paint stroke may incur some leftover blue from not washing the brush properly
        protected double interference;

        public Painting Painting
        {
            get { return painting; }
            set { painting = value; }
        }
        public double ColorBalance
        {
            get { return colorBalance; }
            set { colorBalance = value; }
        }

        public abstract void AddBlue(double amount);
        public abstract void AddRed(double amount);
        public abstract void AddInterference();
    }

    // ConcreteState
    // Cold state means the painting has mostly blue colors
    public class ColdState : State
    {
        public ColdState(State state)
        {
            this.colorBalance = state.ColorBalance;
            this.painting = state.Painting;
            Initialize();
        }

        private void Initialize()
        {
            colorBalance = 0.0;
            lowerLimit = -100.0;
            upperLimit = 0.0;
            balanceChange = 15.00;
            interference = 0.0;
        }

        public override void AddRed(double amount)
        {
            colorBalance += amount;
            StateChangeCheck();
        }

        public override void AddBlue(double amount)
        {
            amount = amount - balanceChange;
            Console.WriteLine("The painting is as blue as it could be.");
        }

        public override void AddInterference()
        {
            // Interference will not affect this
        }

        private void StateChangeCheck()
        {
            if(colorBalance > upperLimit)
            {
                painting.State = new NeutralState(this);
            }
        }
    }

    // ConcreteState
    // Neutral state means amount of blue and red / cold and warm colors are equal
    public class NeutralState : State
    {
        public NeutralState(State state) : this(state.ColorBalance, state.Painting) { }
        public NeutralState(double colorBalance, Painting painting)
        {
            this.colorBalance = colorBalance;
            this.painting = painting;
            Initialize();
        }

        private void Initialize()
        {
            lowerLimit = 0.0;
            upperLimit = 1000.0;
        }

        public override void AddRed(double amount)
        {
            colorBalance += amount;
            StateChangeCheck();
        }

        public override void AddBlue(double amount)
        {
            colorBalance -= amount;
            StateChangeCheck();
        }

        public override void AddInterference()
        {
            colorBalance += interference * colorBalance;
            StateChangeCheck();
        }

        private void StateChangeCheck()
        {
            if (colorBalance > upperLimit)
            {
                painting.State = new WarmState(this);
            }
        }
    }

    // ConcreteState
    // Warm state means there is mostly red colors in the painting
    public class WarmState : State
    {
        public WarmState(State state) : this(state.ColorBalance, state.Painting) { }
        public WarmState(double colorBalance, Painting painting)
        {
            this.colorBalance = colorBalance;
            this.painting = painting;
            Initialize();
        }

        private void Initialize()
        {
            interference = 0.05;
            lowerLimit = 1000.0;
            upperLimit = 10000000.0;
        }

        public override void AddRed(double amount)
        {
            colorBalance += amount;
            StateChangeCheck();
        }

        public override void AddBlue(double amount)
        {
            colorBalance -= amount;
            StateChangeCheck();
        }

        public override void AddInterference()
        {
            colorBalance += interference * colorBalance;
            StateChangeCheck();
        }

        private void StateChangeCheck()
        {
            if(colorBalance < 0.0)
            {
                painting.State = new ColdState(this);
            }
            else if (colorBalance < lowerLimit)
            {
                painting.State = new NeutralState(this);
            }
        }
    }

    // Context
    public class Painting
    {
        private State state;
        private string owner;

        // Constructor
        public Painting(string owner)
        {
            this.owner = owner;
            this.state = new NeutralState(0.0, this);
        }

        public double ColorBalance
        {
            get { return state.ColorBalance; }
        }

        public State State
        {
            get { return state; }
            set { state = value; }
        }

        public void AddBlue(double amount)
        {
            state.AddBlue(amount);
            Console.WriteLine("Added {0} units of blue --- ", amount);
            Console.WriteLine(" Color Balance: {0}", this.ColorBalance);
            Console.WriteLine(" Status = {0}", this.State.GetType().Name);
            Console.WriteLine("");
        }

        public void AddRed(double amount)
        {
            state.AddRed(amount);
            Console.WriteLine("Added {0} units of red --- ", amount);
            Console.WriteLine(" Color Balance: {0}", this.ColorBalance);
            Console.WriteLine(" Status = {0}", this.State.GetType().Name);
            Console.WriteLine("");
        }

        public void AddInterference()
        {
            state.AddInterference();
            Console.WriteLine("Blue Interference Added --- ");
            Console.WriteLine(" Color Balance: {0}", this.ColorBalance);
            Console.WriteLine(" Status = {0}", this.State.GetType().Name);
        }

    }
}
