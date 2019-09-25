namespace CPTS321
{
    using System.Collections.Generic;

    /*
    * The MultiplyNode will evaluate any expression that contains the multiply symbol
    */
    internal class MultiplyNode : OperatorNode
    {
        public MultiplyNode()
            : base('*')
        {
            this.precidence = 2;
        }

        public override double Evaluate(Dictionary<string, double> dict)
        {
            return this.Left.Evaluate(dict) * this.Right.Evaluate(dict);
        }
    }
}
