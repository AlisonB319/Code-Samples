////using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CPTS321;
using System.IO;
using System.Xml;
using System.Xml.Linq;
using System;

namespace Cpts321
{
    /*
     * Spreadsshet class that creates all the cells the spreadsheet needs.  
    */
    public class SpreadSheet
    {
        protected AbCell[,] spreadsheet; // 2d array 
        private int numRow, numCol;
        public event PropertyChangedEventHandler CellPropertyChanged;
        private Dictionary<AbCell, HashSet<AbCell>> dependentCellDic;
        private List<AbCell> activeCells = new List<AbCell>();
        private Stack<UndoRedoCmd> UndoStack = new Stack<UndoRedoCmd>();
        private Stack<UndoRedoCmd> RedoStack = new Stack<UndoRedoCmd>();
        public UndoRedoCmd UndoCmd = new UndoRedoCmd();

        public SpreadSheet(int nRows, int nCols)
        // Constrctor that creates all the cells that the spreadsheet needs
        {
            numRow = nRows;
            numCol = nCols;
            spreadsheet = new Cell[nRows, nCols];
            dependentCellDic = new Dictionary<AbCell, HashSet<AbCell>>();

            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    spreadsheet[i, j] = new Cell(i, j, "");
                    spreadsheet[i, j].Value = ""; // Set all the values of the spreadsheet to empty string 
                    spreadsheet[i, j].PropertyChanged += OnPropertyChanged;
                }
            }
        }
        public AbCell GetCell(int rowIndex, int columnIndex)
        // The function returns a cell at a specifc index on the spreadsheet
        {
            if (rowIndex > spreadsheet.GetLength(0) || columnIndex > spreadsheet.GetLength(1))
                return null;
            else
                return spreadsheet[rowIndex, columnIndex];
        }

        public int ColumnCount
        // Getter that returns the total number of columns
        {
            get { return numCol; }
        }

        public int RowCount
        // Getter that returns the total number or rows
        {
            get { return numRow; }
        }


        /*
         * This function allows us to store which functions are considered "used"
         * Meaning that their contents are not the empty string. This lets us search
         * through a list of used cells in order to compare if they contain a substring
         * so that the EvaluateCellFormula can be called on a changed cell dynamically
       */
        private bool UpdateListStatus(AbCell cell)
        {
            if (!activeCells.Contains(cell))
            {
                // add cell to the active cell list
                activeCells.Add(cell);
                return false;
            }
            // remove from the list if it becomes inactive
            if (cell.Text == string.Empty && cell.Color == 0xffffffff)
            {
                activeCells.Remove(cell);
                return false;
            }
            return true;
        }

        // Converts a cell's row and index into a variable string ie A1 = (0,0)
        private string CoordinatesToString(AbCell cell)
        {
            int row = cell.getRowIndex + 1;
            int column = cell.getColumnIndex;

            string stringRow = row.ToString();
            char stringCol = Convert.ToChar(column + 'A');
            string coordinate = stringCol + stringRow;
            return coordinate;
        }

        // Pass in the cell to return A1
        private string StringToCoordinate(AbCell cell)
        {
            string coor = "";
            coor += this.IntToChar(cell.getColumnIndex);
            coor += (cell.getRowIndex + 1).ToString();
            return coor;

        }

        // Converts an Interger to a Char
        private char IntToChar(int letter)
        {
            return Convert.ToChar(letter + 'A');
        }

        // Returns the Column number
        private int StringToColumn(string coord)
        {
            // coord = "A1"
            int index = 0;
            for (int i = 0; i < coord.Length; i++)
            {
                char c = coord[i];
                if (char.IsNumber(c))
                {
                    index = i;
                    break;
                }
            }
            string column = coord.Substring(0, index);
            char colChar = column[0];
            int tempint = CharToInt(colChar);
            return tempint;
        }

        // Returns a string row to a number
        private int StringToRow(string coord)
        {
            int index = 0;
            for (int i = 0; i < coord.Length; i++)
            {
                char c = coord[i];
                if (char.IsNumber(c))
                {
                    index = i;
                    break;
                }
            }

            string row = coord.Substring(index, coord.Length - 1);
            int temprow = Int32.Parse(row) -1;
            return temprow;
        }

        // Converts a Char to an int
        private int ChartoInt(char letter)
        {
            int num = 0;
            num = Convert.ToInt32(letter) - 'A';
            return num;
        }

        // Removes the current cell from the dependencies 
        private void RemoteCellDependencies(AbCell cell)
        {
            if (dependentCellDic.ContainsKey(cell))
            {
                dependentCellDic[cell].Clear();
            }
            dependentCellDic.Remove(cell);
        }

        // returns true if there is no circular ref 
        private bool CheckRefCycle(AbCell root, AbCell cell)
        {

            if (!dependentCellDic.ContainsKey(cell))
            {
                return true;
            }
            bool result = true;

            foreach (AbCell Ab in dependentCellDic[cell])
            {
                if  (ReferenceEquals(Ab, root))
                {
                    return false;
                }
                result = result && CheckRefCycle(root, Ab);
            }
            return result;
        }

        // Does a quick check before letting the cell go into the Eval Formula
        private void DetermineCellValue(AbCell cell)
        {
            if (cell.Text.Length == 0)
            {
                cell.Value = "";
            }
            if (cell.Text.Length >= 1)
            {
                try
                {
                    EvaulateCellFormula(cell);
                }
                catch
                {
                    cell.Value = "!(bad refrence)";
                }
            }
        }

        private void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        // Function that determines what needs to happen if the Text field of a cell is changed
        // If the cell is changing its string contents, then it is simply overrided with the new contents
        // If the cell is changing to a '=' (equally another cell) than its contents become replaced with the contents of 
        // the cell that it is equal to.
        {
            AbCell cell = sender as AbCell;

            UpdateListStatus((AbCell)sender);

            if (e.PropertyName == "Text")
            {
                RemoteCellDependencies(cell);
                DetermineCellValue(cell);
            }
            else if (e.PropertyName == "Value")
            {
                Waterfall(cell);
                CellPropertyChanged?.Invoke(sender, new PropertyChangedEventArgs("Value"));
            }
            else if (e.PropertyName == "Color")
            {
                CellPropertyChanged?.Invoke(sender, new PropertyChangedEventArgs("Color"));
            }
        }

        // This does a check to see if there is a Self Reference, I also do another check in the Evaluate Function
        private void Waterfall(AbCell cell)
        {
            if (CheckRefCycle(cell, cell))
            {
                if (dependentCellDic.Keys.Count > 0)
                {
                    foreach (AbCell key in dependentCellDic.Keys)
                    {
                        if (dependentCellDic[key].Contains(cell))
                        {
                            DetermineCellValue(key);
                        }
                    }
                }
            }
            else
            {
                cell.Value = "!(bad refrence)";
            }
        }

        // function to determine if it is a valid cell
        private bool ValidCell(AbCell cell, ExpressionTree tree)
        {
            string cellText = cell.Text;

            string cellName = StringToCoordinate(cell);
            string Expression = cell.Text;

            foreach (char letter in Expression) // make sure that each cell refrence in the expression is uppercase
            { 
                if ((Char.IsLetter(letter)) && (!(Char.IsUpper(letter)))) // Make sure it is a char and that the char is uppercase
                {
                    return false;
                }
            }

            char let = cellText[0];

            if (tree.GetVariableNames().Contains(cellName) == true)
            {
                return false;
            }

            if (cellName.Length > 4) { // =Z50 string can be max 4 characters long
                return false;
            }
           
            return true;
        }


        // The cell begins with a '=' meaning it is a formualt. 
        // This function will evaulate the formula
        private void EvaulateCellFormula(AbCell cell)
        {
            string expressionOG = cell.Text.ToString();
            string expression = expressionOG.Substring(1); // expression without the '=' sign
            char[] delimiterChars = { '+', '-', '*', '/', '=' };
            bool createTree = false;
            int tempint;
            bool cirFound = false;

            // check to see if the expression contains an operator
            foreach (char ch in expressionOG)
            {
                if (delimiterChars.Contains(ch))
                {
                    createTree = true;
                    break;
                }
                createTree = false;
            }

            if (expressionOG[0] != '=')
            {
                expression = cell.Text.ToString();
                createTree = true;
            }

            if (createTree)
            {
                ExpressionTree newTree = new ExpressionTree(expression);
                var varTree = newTree.GetVariableNames();
                if (ValidCell(cell, newTree))
                {
                    try
                    {
                        foreach (var entry in varTree)
                        {
                            for (int i = 0; i < entry.Length; i++)
                            {
                                if (Char.IsLetter(entry[i]) && Char.IsDigit(entry[i + 1]))
                                {
                                    int[] indices = RefToIndiciesInLinkedCells(entry);
                                    var CurCell = GetCell(indices[0], indices[1]);

                                    if (CheckCirc(cell, CurCell))
                                    {
                                        throw new Exception("Cell Ref Error");
                                    }
                                }
                            }
                        }

                        foreach (string entry in varTree)
                        {
                            int newCol = CharToInt(entry[0]);
                            int newRow = Convert.ToInt32(entry.Substring(1)) - 1;

                            int[] indices = RefToIndiciesInLinkedCells(entry);

                            var CurCell = GetCell(indices[0], indices[1]);

                            if (!dependentCellDic.ContainsKey(cell)) //adds a key
                            {
                                dependentCellDic.Add(cell, new HashSet<AbCell>());
                            }
                            dependentCellDic[cell].Add(CurCell); // Cell relies on this cell


                            try
                            {
                                tempint = Convert.ToInt32(CurCell.Value); // only included here to catch the try block if the cell contains a string
                                bool pass = Double.TryParse(CurCell.Value, out double result);
                                if (pass && !cirFound)
                                {
                                    tempint = Convert.ToInt32(CurCell.Value);
                                    newTree.SetVariable(entry, Convert.ToInt32(tempint));
                                }
                                else if(cirFound)
                                {
                                    newTree.SetVariable(entry, 0.0);
                                }
                                else
                                {
                                    newTree.SetVariable(entry, 0.0);
                                }
                            }
                            catch // if the cell contains a string instead of a number
                            {
                                cell.Value = "0";
                                break;
                            }
                        }
                        cell.Value = newTree.Evaluate().ToString();
                    }
                    catch
                    {
                        throw new Exception("Could Not EVAL"); 
                    }
                }
                else
                {
                    cell.Value = "!(bad refrence)";
                }
            }
        }

        // Returns a cell location
        private int[] RefToIndiciesInLinkedCells(string cellName)
        {
            int[] indices = new int[spreadsheet.Rank]; // all values are default 0
            int i = 0, lettRep = 0;
            char currChar = char.ToUpper(cellName[0]);
            string alphabet = "A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z";
            for (i = 0; i < cellName.Length; ++i)
            {
                if (currChar != cellName[i])
                {
                    break; //Col header changed
                }
                ++lettRep;
            }
            try
            {
                indices[0] = int.Parse(cellName.Substring(i));
            }
            catch
            {
                throw new ArgumentException("Error invalid column header");
            }
            indices[0] -= 1;
            string[] sAlph = alphabet.Split(new char[] { ',' });
            string alph = string.Join("", sAlph, 0, sAlph.Length);
            indices[1] = (alph.Length * --lettRep) + alph.IndexOf(currChar);
            return indices;

        }

        // Two more function to do another Circular Ref check because I am not sure the other one was completly working
        private bool CheckCirc(AbCell root, AbCell cell)
        {
            var hash = new HashSet<AbCell>();
            hash.Add(root);

            return CirRefHelp(cell, hash);
        }

        private bool CirRefHelp(AbCell cell, HashSet<AbCell> currChain)
        {
            if (currChain.Contains(cell))
                return true;
            if (dependentCellDic.ContainsKey(cell) && dependentCellDic[cell].Count > 0)
            {
                currChain.Add(cell);
                foreach (var cellRef in dependentCellDic[cell])
                {
                    if (CirRefHelp(cellRef, new HashSet<AbCell>(currChain)))
                    {
                        return true;
                    }
                }
            }
            return false; 
        }

        // Cekcs if the stacks are empty so that the buttons can be enabled or disabled
        public bool RedoIsNotEmpty()
        {
            if (RedoStack.Count != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public bool UndoIsNotEmpty()
        {
            if (UndoStack.Count != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // Determining what the lable should be for the buttons 
        public string peekUndo()
        {
            return UndoStack.Peek().BVTT;
        }
        public string peekRedo()
        {
            return RedoStack.Peek().BVTT;
        }

        public void AddUndo(AbCell cell, string text)
        {
            this.UndoStack.Push(new UndoRedoCmd(cell, text));
        }
        // Pushes the commands to the proper stack
        public void Undo()
        {
            if (UndoStack.Count != 0)
            {
                UndoRedoCmd cmd = UndoStack.Pop();
                RedoStack.Push(cmd.RestoreContents(this));
            }
        }

        public void Redo()
        {
            if (RedoStack.Count != 0)
            {
                UndoRedoCmd cmd = RedoStack.Pop();
                UndoStack.Push(cmd.RestoreContents(this));
            }
        }

        private int CharToInt(char letter)
        {
            int num = 0;
            num = Convert.ToInt32(letter) - 'A';
            return num;
        }

        // Simple method to clear the spreadsheet and put everything as default values
        private void ClearSpreadSheet()
        {
            RedoStack.Clear();
            UndoStack.Clear();

            foreach (AbCell ab in spreadsheet)
            {
                ab.Text = "";
                ab.Color = 0xFFFFFFFF;
            }
        }

        // Code that saves the information of a new spreadsheet
        public void SaveSpreadSheet(Stream outfile)
        {
            XmlWriter writer = XmlWriter.Create(outfile);

            // Create the starting tag
            writer.WriteStartElement("spreadsheet");

            foreach (AbCell cell in activeCells)
            {
                writer.WriteStartElement("cell");
                writer.WriteAttributeString("name", this.CoordinatesToString(cell));
                writer.WriteElementString("text", cell.Text);
                writer.WriteElementString("color", cell.Color.ToString());
                writer.WriteEndElement();
            }

            writer.WriteEndElement();

            writer.Close();
        }

        // code that loads the contents of an xml file
        public void LoadSpreadSheet(Stream infile)
        {
            this.ClearSpreadSheet();
            XDocument reader = XDocument.Load(infile);

            foreach (XElement tag in reader.Root.Elements("cell"))
            {
                int Column = StringToColumn(tag.Attribute("name").Value);
                int Row = StringToRow(tag.Attribute("name").Value);

                AbCell cell = GetCell(Row, Column);
                UpdateListStatus(cell);

                cell.Text = tag.Element("text").Value;
                string tempSColor = tag.Element("color").Value;
                uint tempIColor = (uint)Int64.Parse(tempSColor);
                cell.Color = tempIColor;
            }
        }
    }
}
