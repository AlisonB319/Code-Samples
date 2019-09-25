namespace CPTS321
{
    using System.Collections.Generic;

    /*
     * Baic Node class. Only has the Evaluate that other nodes will inherited
     */
    abstract class BaseNode
    {
        public abstract double Evaluate(Dictionary<string, double> dict);
    }
}
