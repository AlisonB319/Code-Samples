namespace CPTS321
{
    using System.Collections.Generic;

    /*
     *  Constant Node is a node that only holds a double as a value
     */
    internal class ConstantNode : BaseNode
    {
        public double Value { get; set; } // Getter and Setter for the Value of a constant Node

        public override double Evaluate(Dictionary<string, double> dict) // Returns the value of the node
        {
            return Value;
        }
    }
}
