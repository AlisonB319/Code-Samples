namespace CPTS321
{
    using System.Collections.Generic;

    /*
    * The MinusNode will evaluate any expression that contains the minus symbol
    */
    internal class MinusNode : OperatorNode
    {
        public MinusNode()
            : base('-')
        {
            this.precidence = 1;
        }

        public override double Evaluate(Dictionary<string, double> dict)
        {
            return this.Left.Evaluate(dict) - this.Right.Evaluate(dict);
        }
    }
}
