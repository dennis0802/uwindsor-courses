using System;
using System.Collections.Generic;
using System.Text;

namespace CommandPatternRun
{
    /**
     * In summary:
     * The draw requests are encapsulated as objects
     * The clients can be parameterized with different requests because of this
     */

    // Driver
    class CommandPattern
    {
        public CommandPattern()
        {
            User user = new User();

            user.Draw('r');
            user.Draw('b');
            user.Draw('y');
            user.Draw('r');

            user.Undo(4);
            user.Redo(3);
            Console.Write("\n");
            Console.ReadKey();
        }
    }

    // Command class
    public abstract class Command
    {
        public abstract void Execute();
        public abstract void UnExecute();
    }

    // Concrete command
    public class DrawCommand : Command
    {
        char @color;
        Canvas canvas;

        public DrawCommand(Canvas canvas, char @color)
        {
            this.canvas = canvas;
            this.@color = @color;
        }

        public char Color
        {
            set { @color = value; }
        }

        public override void Execute()
        {
            canvas.Operation(@color);
        }

        public override void UnExecute()
        {
            canvas.Operation(Undo(color, canvas.colors));
        }

        private char Undo(char @color, List<string> colors)
        {
            switch (@color)
            {
                case 'r': colors.RemoveAt(colors.FindLastIndex(x => x.Contains("Red"))); return '\0';
                case 'b': colors.RemoveAt(colors.FindLastIndex(x => x.Contains("Blue"))); return '\0';
                case 'y': colors.RemoveAt(colors.FindLastIndex(x => x.Contains("Yellow"))); return '\0';
                default: throw new ArgumentException("@operator");
            }
        }
    }

    // Receiver of the command
    public class Canvas
    {
        public List<string> colors = new List<string>();
        public void Operation(char @color)
        {
            switch (@color)
            {
                case 'r': colors.Add("Red"); break;
                case 'b': colors.Add("Blue"); break;
                case 'y': colors.Add("Yellow"); break;
            }
            Console.WriteLine("Current colors: ");
            foreach(String usedColor in colors)
            {
                Console.WriteLine(" {0}", usedColor);
            }
        }
    }

    // Invoker
    public class User
    {
        Canvas canvas = new Canvas();
        List<Command> commands = new List<Command>();
        int current = 0;

        public void Redo(int levels)
        {
            Console.WriteLine("\n---- Redo {0} levels ", levels);
            for(int i = 0; i < levels; i++)
            {
                if(current < commands.Count - 1)
                {
                    Command command = commands[current++];
                    command.Execute();
                }
            }
        }

        public void Undo(int levels)
        {
            Console.WriteLine("\n---- Undo {0} levels ", levels);
            for (int i = 0; i < levels; i++)
            {
                if (current > 0)
                {
                    Command command = commands[--current] as Command;
                    command.UnExecute();
                }
            }
        }

        public void Draw(char @color)
        {
            Command command = new DrawCommand(canvas, color);
            command.Execute();

            commands.Add(command);
            current++;
        }
    }

}
