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

            AbCell cell1 = spreadsheet.GetCell(1, 1);
            cell1.Text = "Hello World";

            AbCell cell2 = spreadsheet.GetCell(3, 3);
            cell2.Text = "=B1";

            Assert.AreEqual(cell1.Text, cell2.Value);
        }

        [Test]
        public void ExpressionCells()
        {
            SpreadSheet spreadsheet = new SpreadSheet(50, 26);
            AbCell cell1 = spreadsheet.GetCell(1, 1); // B1
            cell1.Text = "15";

            AbCell cell2 = spreadsheet.GetCell(40, 14); //N 40
            cell2.Text = "10";

            AbCell cell3 = spreadsheet.GetCell(1, 1);
            cell3.Text = "B1+N40";

            Assert.AreEqual(cell3.Text, "25");





        }
    }
}