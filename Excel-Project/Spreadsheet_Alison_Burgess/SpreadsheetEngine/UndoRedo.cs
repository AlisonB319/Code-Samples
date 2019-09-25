using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cpts321
{
    // This class handles the saving and restoring of the values of cell
    // It can be a string, a value, or a background color
    public class UndoRedoCmd
    {
        string BVT; // Background Value Text 
        string TVtoSave; // Text Value to Save
        uint ColortoSave; // Background Color to Save

        int Row;
        int Col;

        public string BVTT
        {
            get
            {
                return BVT;
            }
        }

        public UndoRedoCmd()
        {

        }

        // Saves the cell contents
        public UndoRedoCmd(AbCell cell, string bvt)
        {
            Row = cell.getRowIndex;
            Col = cell.getColumnIndex;

            if (bvt == "Value")
            {
                BVT = "Value";
                if (cell.Text == "" || cell.Value == null)
                {
                    TVtoSave = "";
                }
                else if (cell.Text.StartsWith("="))
                {
                    TVtoSave = cell.Value;
                }
                else
                {
                    TVtoSave = cell.Text;
                }
            }
            else if (bvt == "Color")
            {
                BVT = "Color";
                ColortoSave = cell.Color;
            }
            else
            {
                TVtoSave = cell.Value;
            }
        }

        // Restores the value or background color that the cell used to be
        public UndoRedoCmd RestoreContents(SpreadSheet spread)
        {
            AbCell cell = spread.GetCell(Row, Col);

            UndoRedoCmd backwards = new UndoRedoCmd();
            backwards.Row = Row;
            backwards.Col = Col;
            backwards.BVT = BVT;

            if (BVT == "Value")
            {
                if (cell.Text != null && cell.Text != "")
                {
                     backwards.TVtoSave = cell.Text;
                }
                else
                {
                    backwards.TVtoSave = "";
                }
                cell.Text = this.TVtoSave;
                cell.Value = this.TVtoSave;
            }
            else if (BVT == "Color")
            {
                backwards.ColortoSave = cell.Color;
                cell.Color = this.ColortoSave;
            }
            else
            {
                throw new Exception("BVT not implemented");
            }
            return backwards;
        }
    }
}
