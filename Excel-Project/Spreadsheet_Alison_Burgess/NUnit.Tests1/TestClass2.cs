/*
 *Alison Burgess
 * CS 350
 * HW4
 * 11509437
*/

namespace NUnit.Tests1
{
    using NUnit.Framework;
    using Cpts321;

    [TestFixture]
    public class TestClass
    {
        [Test]
        public void CellCreated()
        {
            // Create first cell
            AbCell cell = new Cell(0, 0, "This is a Test Cell");
            Assert.NotNull(cell);
            Assert.AreEqual(cell.Text, "This is a Test Cell");
            Assert.AreEqual(cell.getColumnIndex, 0);
            Assert.AreEqual(cell.getRowIndex, 0);

            // Create last cell
            AbCell cell2 = new Cell(50, 26, "This is another Test Cell");
            Assert.NotNull(cell2);
            Assert.AreEqual(cell2.Text, "This is another Test Cell");
            Assert.AreEqual(cell2.getRowIndex, 50);
            Assert.AreEqual(cell2.getColumnIndex, 26);

            // Make sure invalid cell is not created
            AbCell cell3 = new Cell(30, 13, "This is a middle cell");
            Assert.NotNull(cell3);
            Assert.AreEqual(cell3.getRowIndex, 30);
            Assert.AreEqual(cell3.getColumnIndex, 13);
        }

        [Test]
        public void SpreadSheetCreated()
        {
            // testing creating a spreadsheet 
            SpreadSheet ss = new SpreadSheet(50, 26);
            Assert.AreEqual(ss.RowCount, 50);
            Assert.AreEqual(ss.ColumnCount, 26);

            // testing accessing a cell from the spreadsheet
            AbCell testCell = ss.GetCell(10, 15);
            testCell.Text = "New Cell Contents";
            Assert.NotNull(testCell);
            Assert.AreEqual(ss.GetCell(10, 15), testCell);
            Assert.AreEqual(testCell.Text, "New Cell Contents");
        }

        [Test]
        public void ChangeCell()
        {
            // Testing that a cells contents can be overrided by another cell
            SpreadSheet spreadsheet = new SpreadSheet(50, 26);
            AbCell cell1 = spreadsheet.GetCell(0, 1);
            cell1.Text = "Yellow";
            AbCell cell2 = spreadsheet.GetCell(3, 3);
            cell2.Text = "=B1";

            Assert.AreEqual(cell1.Text, cell2.Value);
        }

        [Test]
        public void ExpressionCells()
        {
            // Can evaluate a cell
            SpreadSheet spreadsheet = new SpreadSheet(50, 26);
            AbCell cell1 = spreadsheet.GetCell(0, 0); // A1
            cell1.Text = "10";
            AbCell cell2 = spreadsheet.GetCell(0, 1); // B1
            cell2.Text = "105";
            AbCell cell3 = spreadsheet.GetCell(3, 5); // E5
            cell3.Text = "=A1+B1";

            Assert.AreEqual(cell3.Value, "115");

            // Cell dynamically changes
            cell2.Text = "10";
            Assert.AreEqual(cell3.Value, "20");



            SpreadSheet spreadsheet2 = new SpreadSheet(50, 26);
            AbCell cell4 = spreadsheet2.GetCell(13, 13); // N14
            cell4.Text = "5000";
            AbCell cell5 = spreadsheet2.GetCell(0, 1); // B1
            cell5.Text = "15";
            AbCell cell6 = spreadsheet2.GetCell(3, 5); // E5
            cell6.Text = "=N14+B1";

            Assert.AreEqual(cell6.Value, "5015");

            // Cell dynamically changes
            cell4.Text = "13";
            Assert.AreEqual(cell6.Value, "28");



            SpreadSheet spreadsheet3 = new SpreadSheet(50, 26);
            AbCell cell7 = spreadsheet2.GetCell(49, 25); // Z50
            cell7.Text = "100";
            AbCell cell8 = spreadsheet2.GetCell(0, 1); // B1
            cell8.Text = "10";
            AbCell cell9 = spreadsheet2.GetCell(0, 0); // B1
            cell9.Text = "4";
            AbCell cell10 = spreadsheet2.GetCell(3, 5); // E5
            cell10.Text = "=(Z50/B1)*B1+4";

            Assert.AreEqual(cell10.Value, "104");
        }
        [Test]
        public void SetBackgroundColor()
        {
            // checking that the Color of variable can be set
            SpreadSheet spreadsheet = new SpreadSheet(50, 26);
            AbCell cell = spreadsheet.GetCell(0, 0); // A0
            cell.Color = 0x00FF00;
            Assert.AreEqual(cell.Color, 0x00FF00);

            AbCell cell2 = spreadsheet.GetCell(0, 5); 
            cell2.Color = 0xF95770;
            Assert.AreEqual(cell2.Color, 0xF95770);
        }

        [Test]
        public void UndoRedo()
        {
            // checking that undo and redo can work for both a value and a color
            SpreadSheet spreadsheet = new SpreadSheet(50, 26);
            AbCell cell = spreadsheet.GetCell(0, 0);

            spreadsheet.AddUndo(cell, "Value");
            cell.Text = "Hello";
            spreadsheet.Undo();
            Assert.AreEqual(cell.Text, "");
            spreadsheet.Redo();
            Assert.AreEqual(cell.Text, "Hello");


            SpreadSheet spreadsheet2 = new SpreadSheet(50, 26);
            AbCell cell2 = spreadsheet2.GetCell(0, 0);

            spreadsheet2.AddUndo(cell2, "Color");
            cell2.Color = 0xF95770;
            spreadsheet2.Undo();
            Assert.AreEqual(cell2.Color, 0xFFFFFFFF);
            spreadsheet2.Redo();
            Assert.AreEqual(cell2.Color, 0xF95770);
        }
    }
}