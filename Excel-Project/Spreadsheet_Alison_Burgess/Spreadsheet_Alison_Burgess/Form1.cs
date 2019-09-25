/*
 *Alison Burgess
 * CS 350
 * HW4
 * 11509437
*/

namespace Spreadsheet_Alison_Burgess
{
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.IO;
    using System.Windows.Forms;
    using Cpts321;
    using CPTS321;

    // Function that handles the Form of the SpreadSheet 
    public partial class Form1 : Form
    {
        SpreadSheet Sheet = new SpreadSheet(50, 26);
        public Form1()
        {
            InitializeComponent();

            dataGridView1.CellBeginEdit += new DataGridViewCellCancelEventHandler(dataGridView1_CellBeginEdit);
            dataGridView1.CellEndEdit += new DataGridViewCellEventHandler(dataGridView1_CellEndEdit);
        }
        
        private void OnCellPropertyChanged(object sender, PropertyChangedEventArgs e)
        // Function returns the value of a cell if the Property Name is "Value"
        {
            AbCell cell = sender as AbCell;
            if (cell != null && e.PropertyName == "Value")
            {
                dataGridView1.Rows[cell.getRowIndex].Cells[cell.getColumnIndex].Value = cell.Value;
            }
            else if (cell != null && e.PropertyName == "Color")
            {
                int tempCol = (int)cell.Color;
                Color col = Color.FromArgb(tempCol);
                dataGridView1[cell.getRowIndex, cell.getColumnIndex].Style.BackColor = col;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {           
            Sheet.CellPropertyChanged += OnCellPropertyChanged; // cell change event

            dataGridView1.ColumnCount = 26;
            int ColumnIndex = 0;

            // Creating the columns
            for (char tempc = 'A'; tempc <= 90; tempc++)
            {
                dataGridView1.Columns[ColumnIndex].Name = tempc.ToString();
                ColumnIndex++;
            }

            // Creating the rows
            for (int i = 1; i <= 50; i++)
            {
                dataGridView1.Rows.Add();
                dataGridView1.Rows[i - 1].HeaderCell.Value = (i).ToString();
            }
            // adjusts the dataGridView so that the row labels are fully displayed
            dataGridView1.AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders);
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        // These are the two functions that will save the new data of cells if they are changed
        private void dataGridView1_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            dataGridView1.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = this.Sheet.GetCell(e.RowIndex, e.ColumnIndex).Text;
        }

        private void dataGridView1_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            DataGridView dgv = sender as DataGridView;

            var currCell = Sheet.GetCell(e.RowIndex, e.ColumnIndex);
            if (dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value != null)
            {
                this.Sheet.AddUndo(currCell, "Value");
                currCell.Text = dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString();
            }
            else
            {
                currCell.Text = "";
            }
            dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = currCell.Value;
        }


        private void changeBackgroundColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Int32 selectedCellCount = dataGridView1.GetCellCount(DataGridViewElementStates.Selected);
            ColorDialog MyDialog = new ColorDialog();

            if (MyDialog.ShowDialog() == DialogResult.OK)
            {
                foreach (DataGridViewCell cell in dataGridView1.SelectedCells)
                {
                    uint cellCol = (uint)MyDialog.Color.ToArgb();
                    AbCell indivCell = Sheet.GetCell(cell.ColumnIndex, cell.RowIndex);
                    this.Sheet.AddUndo(indivCell, "Color");
                    indivCell.Color = cellCol;
                }
            }
            
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            

        }

        // Makes sure that the right Label is in the tool strip menu
        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Sheet.UndoIsNotEmpty())
            {
                undoTextChangeToolStripMenuItem.Enabled = true;
                if (Sheet.peekUndo() == "Value")
                {
                    undoTextChangeToolStripMenuItem.Text = "Undo Text Change";
                }
                else
                {
                    undoTextChangeToolStripMenuItem.Text = "Undo Cell Color Change";
                }
            }
            else
            {
                undoTextChangeToolStripMenuItem.Enabled = false;
            }
            if (Sheet.RedoIsNotEmpty())
            {
                redoToolStripMenuItem.Enabled = true;
                if (Sheet.peekRedo() == "Value")
                {
                    redoToolStripMenuItem.Text = "Redo Text Change";
                }
                else
                {
                    redoToolStripMenuItem.Text = "Redo Cell Color Change";
                }
            }
            else
            {
                redoToolStripMenuItem.Enabled = false;
            }
        }

        // Undo and Redo button clicks
        private void undoTextChangeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Sheet.Undo();
        }

        private void redoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Sheet.Redo();
        }

        // code that executes after choosing to save a file
        private void saveFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "XML-File | *.xml";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {

                FileStream toSave = new FileStream(saveFileDialog.FileName, FileMode.Create);

                Sheet.SaveSpreadSheet(toSave);

                toSave.Dispose();
            }
        }

        // code that executes after choosing to load a file
        private void loadFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                FileStream toOpen = new FileStream(openFileDialog.FileName, FileMode.Open);
                Sheet.LoadSpreadSheet(toOpen);
            }
        }
    }
}