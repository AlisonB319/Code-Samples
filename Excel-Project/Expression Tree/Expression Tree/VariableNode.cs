using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPTS321
{
    /*
     * The Variable Node holds the Name of a variable that is used as the Key in the dictionary.
     * The Evaluate function uses the dictionary to return the correct value
     */
    internal class VariableNode : BaseNode
    {
        public string Name { get; set; }


        
        public override double Evaluate(Dictionary<string, double> dict)
        {
            return dict[Name];
        }
    }
}
