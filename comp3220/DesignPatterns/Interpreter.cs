using System;
using System.Collections.Generic;
using System.Text;

namespace InterpreterPattern
{
    /**
     * In summary:
     * It defines a representation for the color grammar
     * There is an interpreter to interpret colors in the color string.
     */
    class Interpreter
    {
        public Interpreter()
        {
            string paintString = "RBYYRBBYRBRY";
            char[] colors = paintString.ToCharArray();
            Context context = new Context(paintString);

            // Build the parse tree
            List<Expression> tree = new List<Expression>();

            foreach(char color in colors)
            {
                tree.Add(new ColorExpression());
            }

            foreach (Expression exp in tree)
            {
                exp.Interpret(context);
            }
            Console.WriteLine("{0} = {1}", paintString, context.Output);
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Context
    public class Context
    {
        string input;
        string output;

        public Context(string input)
        {
            this.input = input;
        }

        public string Input
        {
            get { return input; }
            set { input = value; }
        }

        public string Output
        {
            get { return output; }
            set { output = value; }
        }
    }

    // AbstractExpression
    public abstract class Expression
    {
        public void Interpret(Context context)
        {
            if(context.Input.Length == 0)
            {
                return;
            }
            if (context.Input.StartsWith(Red()))
            {
                context.Output += "Red ";
                context.Input = context.Input.Substring(1);
            }
            else if (context.Input.StartsWith(Yellow()))
            {
                context.Output += "Yellow ";
                context.Input = context.Input.Substring(1);
            }
            else if (context.Input.StartsWith(Blue()))
            {
                context.Output += "Blue ";
                context.Input = context.Input.Substring(1);
            }
        }
        public abstract string Blue();
        public abstract string Red();
        public abstract string Yellow();
    }

    // TerminalExpression
    public class ColorExpression : Expression
    {
        public override string Red()
        {
            return "R";
        }
        public override string Blue()
        {
            return "B";
        }
        public override string Yellow()
        {
            return "Y";
        }
    }
}
