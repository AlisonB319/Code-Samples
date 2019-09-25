/*
 *Alison Burgess
 * CS 350
 * HW4
 * 11509437
*/

namespace Cpts321
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;
    using System.ComponentModel;
    using System.Xml.Linq;
    using System.Xml;
    using System.Xml.Serialization;
    using System.Xml.Schema;


    /*
     * Class that defines an individual Cell
     * Contains the cells rowInde, columnIndex, and value
    */
    public abstract class AbCell : INotifyPropertyChanged
    {
        protected int rowIndex;
        protected int columnIndex;
        protected string _text = "";
        protected string _value = "";
        
        protected uint BGcolor = 0xFFFFFFFF;

        public event PropertyChangedEventHandler PropertyChanged;

        public void INotifyPropertyChanged(string propertyName)
        // Function determins if the properties have changed, and assign it an Event Argument
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        public AbCell()
        // Empty Constructor for AbCell so that the overlaoded Cell class can create a cell
        {

        }

        public AbCell(int rowI, int columnI)
        // Ab cell constructor that sets the row index and column index
        {
            rowIndex = rowI;
            columnIndex = columnI;
            BGcolor = 0xFFFFFFFF;
        }

        public int getRowIndex
        // Getter that returns the Row Index as an Interger
        {
            get { return rowIndex; }
        }

        public int getColumnIndex
        // Getter that returns the Column Index as an Integer
        {
            get { return columnIndex; }
        }

        public string Text
        // Getter and setter for the text variable. The Text attribute stores the contents of the cell
        {
            get { return _text; }

            set
            {
                if (_text != value)
                {
                    _text = value;
                    PropertyChanged(this, new PropertyChangedEventArgs("Text"));
                }
            }

        }

        public uint Color
        // getter and setter for the BG color variable;
        {
            get { return BGcolor; }

            set
            {
                if (BGcolor != value)
                {
                    BGcolor = value;
                    PropertyChanged(this, new PropertyChangedEventArgs("Color"));
                }
            }
        }

        public string Value
        // Getter and setter for the value attribute. Only the spread sheet class can set the value
        {
            get { return _value; }
            internal set // only the spread sheet class can set 
            {
                if (_value != value)
                {
                    _value = value;
                    PropertyChanged(this, new PropertyChangedEventArgs("Value"));
                }
            }
        }
    }
    

    // cell that allows it to be instanced
    public class Cell : AbCell
    {
        public Cell(int rows, int col, string text)
        {
            rowIndex = rows;
            columnIndex = col;
            _text = text;
            _value = Value;
        }
    }
}