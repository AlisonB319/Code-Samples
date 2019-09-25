using System;
namespace CPTS321
{
    class Program
    {
        /*
         *  Main do While loop that will run the code until the user presses 4 
        */
        static void Main(string[] args)
        {
            int userOption = 0, userVarValue = 0;
            string userExpression = "", userVarName;
            ExpressionTree userTree = new ExpressionTree(userExpression);
            do
            {
                Console.WriteLine("Menu (current expression = \"{0}\")", userExpression);
                Console.WriteLine("Enter a Value:");
                Console.WriteLine("  1 = Enter a new expression");
                Console.WriteLine("  2 = Set a variable value");
                Console.WriteLine("  3 = Evaluate tree");
                Console.WriteLine("  4 = Quit");
               
                userOption = Convert.ToInt32(Console.ReadLine());

                if (userOption == 1) // Enter a new Expression
                {
                    Console.Write("Enter a new expression: ");
                    userExpression = Console.ReadLine();
                    userTree = new ExpressionTree(userExpression);
                }
                else if (userOption == 2) // Create a new Variable
                {
                    Console.Write("Enter variable name: ");
                    userVarName = Console.ReadLine();
                    Console.Write("Enter variable value: ");
                    userVarValue = Convert.ToInt32(Console.ReadLine());
                    userTree.SetVariable(userVarName, userVarValue);
                }
                else if (userOption == 3) // Evaluate the tree
                {
                    Console.WriteLine(userTree.Evaluate());
                }
                else if (userOption == 4) // Finish
                {
                    Console.WriteLine("Done");
                }
                else
                {
                    Console.WriteLine("// This is a command that the app will ignore");
                }

            } while (userOption != 4);
        }
    }
}
