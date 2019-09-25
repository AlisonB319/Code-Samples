// <copyright file="ExpressionTree.cs" company="Ivan Montoya">
// Copyright (c) Ivan Montoya. All rights reserved.
// </copyright>

namespace CPTS321
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class ExpressionTree
    {
        private BaseNode root;
        private Dictionary<string, double> variables = new Dictionary<string, double>();

        /// <summary>
        /// Initializes a new instance of the <see cref="ExpressionTree"/> class.
        /// Constructor that takes in a string as an argument.
        /// </summary>
        /// <param name="expression">Expression to construct the tree.</param>
        public ExpressionTree(string expression)
        {
            // Clears out the dictinary when a new expression is made
            //variables.Clear();
            List<string> expression2 = infixToPostfix(expression);

            Compile2(expression2);

            this.Expression = expression;
        }

        public string Expression { get; set; }

        /// <summary>
        /// Set the value of a variable.
        /// </summary>
        /// <param name="variableName">Name of the variable.</param>
        /// <param name="variableValue">Value to be associated with the variable.</param>
        public void SetVariable(string variableName, double variableValue)
        {
            if (variables.ContainsKey(variableName))
            {
                variables[variableName] = variableValue;
            }
            else
            {
                this.variables.Add(variableName, variableValue);
            }
            
        }

        /// <summary>
        /// Public method that evaluates the expression tree.
        /// </summary>
        /// <returns>Value of the expression.</returns>
        public double Evaluate()
        {
            return this.Evaluate(this.root);
        }

        // This function takes an infix expression and changes it to postfix
        private List<string> infixToPostfix(string exp)
        {
            List<string> result = new List<string>();
            char[] delimiterChars = { '(', ')', '+', '-', '*', '/' };
            Stack<string> vals = new Stack<string>();
            
            for (int i = 0; i < exp.Length; i++){
                // Current token is a number, push it to stack for numbers
                if (Char.IsDigit(exp[i]))
                {
                    StringBuilder sbuf = new StringBuilder();
                    while (i < exp.Length && Char.IsDigit(exp[i]))
                    {
                        sbuf.Append(exp[i++]);
                    }

                    result.Add(sbuf.ToString());
                    i--;
                }
                // if the scanned character is an '(' push it to the stack
                else if (exp[i] == '(')
                {
                    vals.Push(exp[i].ToString());
                }
                // if the scanned character is an ')' pop and output forn the stack until '(' is encountered
                else if (exp[i] == ')')
                {
                    while (vals.Count > 0 && vals.Peek() != '('.ToString())
                    {
                        result.Add((vals.Pop()));
                    }
                    if (vals.Count > 0 && vals.Peek() != '('.ToString())
                    {
                        return null;
                    }
                    else
                    {
                        vals.Pop();
                    }
                }
                else if (Char.IsLetter(exp[i]))
                {
                    StringBuilder sbuf = new StringBuilder();
                    while (i < exp.Length && !ExpressionTreeFactory.IsValidOperator(exp[i]) && (exp[i] != '(') && (exp[i] != ')') && (exp[i] != ' '))
                    {
                        sbuf.Append(exp[i++]);
                    }
                    result.Add(sbuf.ToString());
                    i--;
                }
                else // operator is encountered
                {
                    while(vals.Count > 0)
                    {
                        OperatorNode temp = ExpressionTreeFactory.CreateOperatorNode(exp[i]);
                        OperatorNode temp2 = ExpressionTreeFactory.CreateOperatorNode(vals.Peek()[0]);

                        if (temp2 == null || temp.precidence > temp2.precidence)
                        {
                            break;
                        }
                        result.Add((vals.Pop()).ToString());
                    }
                    vals.Push(exp[i].ToString());
                }
            }

            while(vals.Count > 0){
                result.Add(vals.Pop());
            }
            return result;
        }

        //  This function takes the postfix expression and puts it in a stack of operators
        //  It then calls MakeTree on the created root
        private BaseNode Compile2(List<string> expression)
        {
            Stack<BaseNode> stack = new Stack<BaseNode>();
            foreach(string val in expression)
            {
                // determine wherther num, var, or operator 
                // create nodes and then push them on the stack

                if (ExpressionTreeFactory.IsValidOperator(val[0])) // Operator Node
                {
                    OperatorNode temp = ExpressionTreeFactory.CreateOperatorNode(val[0]);
                    stack.Push(temp);
                }
                else if (char.IsDigit(val[0])) // Constant Node
                {
                    ConstantNode temp = new ConstantNode();
                    double num = Convert.ToDouble(val);
                    temp.Value = num;
                    stack.Push(temp);
                }
                else // Variable Node
                {
                    VariableNode temp = new VariableNode();
                    temp.Name = val;
                    if (!variables.ContainsKey(val))
                    {
                        variables.Add(val, 0);
                    }
                    stack.Push(temp);
                }
            }

            if (stack.Count != 0)
            {
                this.root = stack.Peek();
                return CreateTree(stack, stack.Pop());
            }
            return null;

        }
         
        // This creates the tree that is needed in order for the expression to be evaluated
        private BaseNode CreateTree(Stack<BaseNode> stack, BaseNode curNode)
        {
            if (stack.Count == 0)
            {
                return curNode;
            }
            if (curNode is OperatorNode)
            {
                ((OperatorNode)curNode).Right = CreateTree(stack, stack.Pop());
                ((OperatorNode)curNode).Left = CreateTree(stack, stack.Pop());
            }
            return curNode;
        }

        public bool IsValueType<T>(T obj)
        {
            return typeof(T).IsValueType;
        }

        public List<string> GetVariableNames()
        {
            return this.variables.Keys.ToList<string>();
        }

        private double Evaluate(BaseNode theNode)
        {
            if (root == null)
            {
                return 0;
            }
            else
            {
                return root.Evaluate(variables); // You have to pass in the dictionary for the Variable Nodes
            }

        }
    }
}
