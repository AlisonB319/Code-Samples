using System;
using System.Collections.Generic;

namespace CPTS321
{
    /*
     * The Expression Tree factory handles which function to call based on the symbol the Operator Node contains
     */
    internal class ExpressionTreeFactory
    {
        private static Dictionary<char, Type> operators = new Dictionary<char, Type>
        {
            {'-', typeof(MinusNode)},
            {'+', typeof(PlusNode)},
            {'*', typeof(MultiplyNode)},
            {'/', typeof(DivideNode)},
        };

        // Calls the proper function based on the Operator Node type
        public static OperatorNode CreateOperatorNode(char op)
        {
            if (operators.ContainsKey(op))
            {
                object operatorNodeObject = System.Activator.CreateInstance(operators[op]);
                if (operatorNodeObject is OperatorNode)
                {
                    return (OperatorNode)operatorNodeObject;
                }
            }
            return null;
        }

        public static bool IsValidOperator(char op)
        {
            if (operators.ContainsKey(op)) { 
                    return true;
            }
            return false;
        }

        

}
}
