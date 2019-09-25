namespace CPTS321
{
    /*
     * The Operator Node stores the symbol of the operator as well as the values contained to the left and to the right of the operator
     */
    internal abstract class OperatorNode : BaseNode
    {
        public OperatorNode(char c)
        {
            this.Operator = c;
            this.Left = this.Right = null;
        }

        public char Operator { get; set; }

        public BaseNode Left { get; set; }

        public BaseNode Right { get; set; }

        public int precidence { get; set; }

        

        //public abstract double Evaluate(BaseNode theNode);
    }
}
