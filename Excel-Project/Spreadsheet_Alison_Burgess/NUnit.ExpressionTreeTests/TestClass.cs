using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CPTS321;

namespace NUnit.Tests1
{
    [TestFixture]
    public class TestClass
    {
        [Test]
        public void Addition()
        {
            ExpressionTree testTree = new ExpressionTree("12+2");
            Assert.AreEqual(testTree.Evaluate(), 14);

            ExpressionTree testTree1 = new ExpressionTree("0+0");
            Assert.AreEqual(testTree1.Evaluate(), 0);

            ExpressionTree testTree2 = new ExpressionTree("5+0");
            Assert.AreEqual(testTree2.Evaluate(), 5);

            ExpressionTree testTree3 = new ExpressionTree("5+0+1");
            Assert.AreEqual(testTree3.Evaluate(), 6);

            ExpressionTree testTree4 = new ExpressionTree("(5+10)+4");
            Assert.AreEqual(testTree4.Evaluate(), 19);

            ExpressionTree testTree5 = new ExpressionTree("4+(5+1)+2");
            Assert.AreEqual(testTree5.Evaluate(), 12);

            ExpressionTree testTree6 = new ExpressionTree("4*(5+1)+2");
            Assert.AreEqual(testTree6.Evaluate(), 26);

        }
        [Test]
        public void Subtraction()
        {
            ExpressionTree testTree = new ExpressionTree("12-2");
            Assert.AreEqual(testTree.Evaluate(), 10);

            ExpressionTree testTree1 = new ExpressionTree("0-0");
            Assert.AreEqual(testTree1.Evaluate(), 0.0);

            ExpressionTree testTree2 = new ExpressionTree("0-5");
            Assert.AreEqual(testTree2.Evaluate(), -5);

            ExpressionTree testTree3 = new ExpressionTree("0-5-1");
            Assert.AreEqual(testTree3.Evaluate(), -6);

            ExpressionTree testTree4 = new ExpressionTree("10*(5-1)");
            Assert.AreEqual(testTree4.Evaluate(), 40);
        }
        [Test]
        public void Multiply()
        {
            ExpressionTree testTree = new ExpressionTree("12*2");
            Assert.AreEqual(testTree.Evaluate(), 24);

            ExpressionTree testTree1 = new ExpressionTree("0*0");
            Assert.AreEqual(testTree1.Evaluate(), 0);

            ExpressionTree testTree2 = new ExpressionTree("0*5");
            Assert.AreEqual(testTree2.Evaluate(), 0);

            ExpressionTree testTree3 = new ExpressionTree("12*2*2");
            Assert.AreEqual(testTree3.Evaluate(), 48);

            ExpressionTree testTree4 = new ExpressionTree("100*(10-2)/20");
            Assert.AreEqual(testTree4.Evaluate(), 40);

            ExpressionTree testTree5 = new ExpressionTree("(10+2)*(8+10)+((2))");
            Assert.AreEqual(testTree5.Evaluate(), 218);
        }
        [Test]
        public void Divide()
        {
            ExpressionTree testTree = new ExpressionTree("12/2");
            Assert.AreEqual(testTree.Evaluate(), 6);

            ExpressionTree testTree1 = new ExpressionTree("0/0");
            Assert.AreEqual(testTree1.Evaluate(), 0);

            ExpressionTree testTree2 = new ExpressionTree("5/0");
            Assert.AreEqual(testTree2.Evaluate(), 0);

            ExpressionTree testTree3 = new ExpressionTree("12/2/2");
            Assert.AreEqual(testTree3.Evaluate(), 3);

            ExpressionTree testTree4 = new ExpressionTree("(12/6)+(100/10)");
            Assert.AreEqual(testTree4.Evaluate(), 12);
        }
        [Test]
        public void Variables()
        {
            ExpressionTree testTree = new ExpressionTree("A+B");
            testTree.SetVariable("A", 2);
            testTree.SetVariable("B", 5);
            Assert.AreEqual(testTree.Evaluate(), 7);

            ExpressionTree testTree2 = new ExpressionTree("A1*B");
            testTree2.SetVariable("A1", 12);
            testTree2.SetVariable("B", 10);
            Assert.AreEqual(testTree2.Evaluate(), 120);

            ExpressionTree testTree3 = new ExpressionTree("7-C");
            testTree3.SetVariable("C", 10);
            Assert.AreEqual(testTree3.Evaluate(), -3);

            ExpressionTree testTree4 = new ExpressionTree("a+b+c");
            testTree4.SetVariable("a", 1);
            testTree4.SetVariable("b", 2);
            testTree4.SetVariable("c", 3);
            Assert.AreEqual(testTree4.Evaluate(), 6);

            ExpressionTree testTree5 = new ExpressionTree("(A3+B4)*C5");
            testTree5.SetVariable("A3", 5);
            testTree5.SetVariable("B4", 2);
            testTree5.SetVariable("C5", 3);
            Assert.AreEqual(testTree5.Evaluate(), 21);

        }

        [Test]
        public void Expressions()
        {
            ExpressionTree testTree1 = new ExpressionTree("(((((1+2)))))");
            Assert.AreEqual(testTree1.Evaluate(), 3);

            ExpressionTree testTree2 = new ExpressionTree("(1+2+3)-2");
            Assert.AreEqual(testTree2.Evaluate(), 4);

            ExpressionTree testTree3 = new ExpressionTree("(((3+2))*1)");
            Assert.AreEqual(testTree3.Evaluate(), 5);

            ExpressionTree testTree4 = new ExpressionTree("3+2*10/5");
            Assert.AreEqual(testTree4.Evaluate(), 7);
        }
    }
}
