namespace CPTS321
{
    using System.Collections.Generic;

    internal class PlusNode : OperatorNode
    {
        /*
        * The PlusNode will evaluate any expression that contains the plus symbol
        */
        public PlusNode()
            : base('+')
        {
            this.precidence = 1;
        }

        public override double Evaluate(Dictionary<string, double> dict)
        {
            return this.Left.Evaluate(dict) + this.Right.Evaluate(dict);
        }
    }
}
