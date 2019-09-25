namespace CPTS321
{
    using System.Collections.Generic;

     /*
     * The DivideNode will evaluate any expression that contains the division symbol
     */
    internal class DivideNode : OperatorNode
    {
        public DivideNode()
            : base('/')
        {
            this.precidence = 2;
        }

        public override double Evaluate(Dictionary<string, double> dict)
        {
            if (this.Right.Evaluate(dict) == 0) // Check to make sure you are not dividing by 0
            {
                return 0;
            }
            return this.Left.Evaluate(dict) / this.Right.Evaluate(dict);
        }
    }
}
