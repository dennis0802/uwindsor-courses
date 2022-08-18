using System;
using PolymorphismPattern;
using FactoryPattern;
using AbstractFactoryPattern;
using BridgePattern;
using FactoryBridgePattern;
using BuilderPattern;
using PrototypePattern;
using Singleton;
using AdapterPattern;
using CompositePattern;
using DecoratorPattern;
using FacadePattern;
using FlyweightPattern;
using ProxyPattern;
using ChainOfResponsibility;
using CommandPatternRun;
using InterpreterPattern;
using IteratorPattern;
using MediatorPattern;
using MementoPattern;
using ObserverPattern;
using StatePatternRun;
using StrategyPattern;
using TemplatePattern;
using VisitorPattern;

namespace DesignPatterns
{
    // Driver class for all design patterns
    class Program
    {
        static void Main(string[] args)
        {
            string input;
            Boolean exitFlag = false;
            while (!exitFlag)
            {
                Console.WriteLine("This program displays design patterns, using art products as a common theme\n\nEnter:");
                Console.WriteLine("'poly' for Polymorpishm");
                Console.WriteLine("'factory' for Factory");
                Console.WriteLine("'abstractfactory' for AbstractFactory");
                Console.WriteLine("'bridge' for Bridge");
                Console.WriteLine("'factorybridge' for Bridge + AbstractFactory");
                Console.WriteLine("'builder' for Builder");
                Console.WriteLine("'prototype' for Prototype");
                Console.WriteLine("'singleton' for Singleton");
                Console.WriteLine("'adapter' for Adapter");
                Console.WriteLine("'composite' for Composite");
                Console.WriteLine("'decorate' for Decorator");
                Console.WriteLine("'facade' for Facade");
                Console.WriteLine("'flyweight' for Flyweight");
                Console.WriteLine("'proxy' for Proxy");
                Console.WriteLine("'chain' for Chain of Responsibility");
                Console.WriteLine("'command' for Command");
                Console.WriteLine("'interpret' for Interpreter");
                Console.WriteLine("'iterate' for Iterator");
                Console.WriteLine("'mediator' for Mediator");
                Console.WriteLine("'memento' for Memento");
                Console.WriteLine("'observer' for Observer");
                Console.WriteLine("'state' for State");
                Console.WriteLine("'strat' for Strategy");
                Console.WriteLine("'temp' for Template");
                Console.WriteLine("'visit' for Visitor");
                Console.WriteLine("'exit' to Exit\n");
                Console.Write("> ");
                input = Console.ReadLine();
                input = input.ToLower();

                switch (input)
                {
                    case "poly":
                        Console.WriteLine("POLYMORPHISM METHOD: Painting types and books are specialized Order Items");
                        Polymorphism p = new Polymorphism();
                        break;

                    case "factory":
                        Console.WriteLine("\nFACTORY METHOD: Standardizes the architectural model for a range of Paintings and books");
                        Factory f = new Factory();
                        break;

                    case "abstractfactory":
                        Console.WriteLine("\nABSTRACT FACTORY METHOD: Frames and picture info are related to each other as a full Painting");
                        AbstractFactoryRun a = new AbstractFactoryRun();
                        break;

                    case "bridge":
                        Console.WriteLine("\nBRIDGE METHOD: The painting is separated from the drawing");
                        Bridge b = new Bridge();
                        break;

                    case "factorybridge":
                        Console.WriteLine("\nBRIDGE FACTORY METHOD: The painting is separated from the drawing, the Frame and Drawing are related as a full Painting");
                        FactoryBridge fb = new FactoryBridge();
                        break;

                    case "builder":
                        Console.WriteLine("\nBUILDER METHOD: Separating the construction of a painting from its representation so the process can make different paintings");
                        Builder builder = new Builder();
                        break;

                    case "prototype":
                        Console.WriteLine("\nPROTOTYPE METHOD: The painting is a prototype that can be cloned into more paintings using a manager");
                        Prototype proto = new Prototype();
                        break;

                    case "singleton":
                        Console.WriteLine("\nSINGLETON METHOD: The painting has an Instance operation to access the unique instance; created and maintained");
                        SingletonPattern s = new SingletonPattern();
                        break;

                    case "adapter":
                        Console.WriteLine("\nADAPTER METHOD: The finished paintings have a databank adapting to it. The target is on a general painting");
                        Adapter ad = new Adapter();
                        break;

                    case "composite":
                        Console.WriteLine("\nCOMPOSITE METHOD: The drawing is divided into a tree of elements (shapes, lines)");
                        Composite c = new Composite();
                        break;

                    case "decorate":
                        Console.WriteLine("\nDECORATOR METHOD: Paintings can have more responsibilities added dynamically, an alternative to subclassing");
                        DecoratorDriver d = new DecoratorDriver();
                        break;

                    case "facade":
                        Console.WriteLine("\nFACADE METHOD: Paintings can be sold once it passes through the subsystems frame, draft, and type");
                        Facade fa = new Facade();
                        break;

                    case "flyweight":
                        Console.WriteLine("\nFLYWEIGHT METHOD: Support large numbers of fine-grained objects efficiently");
                        Flyweight fly = new Flyweight();
                        break;

                    case "proxy":
                        Console.WriteLine("\nPROXY METHOD: A placeholder proxy accesses the paintings to add colors");
                        Proxy pr = new Proxy();
                        break;

                    case "chain":
                        Console.WriteLine("\nCHAIN OF RESPONSIBILITY METHOD: Avoid coupling appraisal requests by passing the request through handlers");
                        Chain ch = new Chain();
                        break;

                    case "command":
                        Console.WriteLine("\nCOMMAND METHOD: Encapsulating the draw request as an object, parameterizing clients with different requests");
                        CommandPattern cm = new CommandPattern();
                        break;

                    case "interpret":
                        Console.WriteLine("\nINTERPRETER METHOD: Defines a represenation for a color language's grammar along with an interpeter for what color");
                        Interpreter inter = new Interpreter();
                        break;

                    case "iterate":
                        Console.WriteLine("\nITERATOR METHOD: Access a collection of colors sequentially without exposing its underlying representation");
                        IteratorRun ir = new IteratorRun();
                        break;

                    case "mediator":
                        Console.WriteLine("\nMEDIATOR METHOD: The museum encapsulates a set of paintings and how they interact");
                        Console.WriteLine("It promotes loose coupling by keeping them from referring to each other explicitly and vary their interaction independently");
                        Mediator me = new Mediator();
                        break;

                    case "memento":
                        Console.WriteLine("\nMEMENTO METHOD: Capture and externalize the internal state of a painting to restore later without violating encapsulation");
                        MementoRun mr = new MementoRun();
                        break;

                    case "observer":
                        Console.WriteLine("\nOBSERVER METHOD: Define a one-to-many dependency between objects so when one changes state, all dependents are notified and updated");
                        Observer o = new Observer();
                        break;

                    case "state":
                        Console.WriteLine("\nSTATE METHOD: Allow paintings to change their behaviour when the internal amounts of red and blue change, appearing to change its class");
                        StatePattern st = new StatePattern();
                        break;

                    case "strat":
                        Console.WriteLine("\nSTRATEGY METHOD: A family of algorithms can be defined to be encapsulated and interchangeable, varying independently in use.");
                        Strategy str = new Strategy();
                        break;

                    case "temp":
                        Console.WriteLine("\nTEMPLATE METHOD: Define the skeleton of an algorithm where the Frame and PaintingType subclasses can redefine steps without changing the structure");
                        Template tp = new Template();
                        break;

                    case "visit":
                        Console.WriteLine("\nVISITOR METHOD: Defines a new operation without changing the classes of the elements on an object");
                        VisitorRun v = new VisitorRun();
                        break;

                    case "exit":
                        exitFlag = true;
                        break;
                    default:
                        Console.WriteLine("Invalid input!\n");
                        break;
                }
            }
        }
    }
}
