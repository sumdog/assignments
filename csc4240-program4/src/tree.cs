//
//  Sumit Khanna -- CSC 4240 - Program 4 - Dr. Talber's AI Class
//
//		tree.cs - Holds the actual ID3 tree
//   depends on Data.cs to sample data
using System;
using sum.data;

namespace sum.tree
{

	public struct DTestResults
	{
		public uint correct, total;
	}

	public class DTree
	{
		private DNode root;

		public DTree(DataSet classify)
		{
			bool[] marked = new bool[classify.numAttributes()];
			root = new DNode(classify,ref marked, "");
			
		}

		public void printTree() { root.printTree(0); }

		public DTestResults testTree(DataSet test)
		{
			int count = 0;
			for(uint x=0; x < test.numRows(); x++)
			{ count += (testRow(test.getRow(x))) ? 1 : 0; }
			DTestResults retval = new DTestResults();
			retval.correct = (uint) count;
			retval.total = test.numRows();
			return retval;
		}

		private bool testRow(DataRow row)
		{ return searchTree(root,row); }

		private bool searchTree(DNode n, DataRow row)
		{
			if(n.classification != null)
			{return row.checkClass(n.classification);}
			else
			{
				string a = row.getAttribute(n.attribute);
				for(uint x = 0; x < n.children.Length; x++)
				{
					if(n.children[x].path.Equals(a))
					{ return searchTree(n.children[x],row);}
				}
			}
			//Console.WriteLine("Am I here");
			return false; //should never get here
		}

	}

	class DNode
	{
		public uint attribute;
		public bool attr_assigned;

		public string classification,path;

		public DNode[] children;

		public DNode(DataSet classify, ref bool[] marked, string path)
		{
			//Console.WriteLine(markedString(marked));
			classification = null; //only gets set on leaf node
			attr_assigned = false; //unassigned
			this.path = path;

			//if the tree is perfectly classified (entropy == 0) 
			// or if we're out of attributes, return the most occuring one
			if(classify.entropy == 0 || allMarked(ref marked)) 
			{ classification = classify.getMostOccuringClassification();}
			else 
			{
				attribute = classify.bestGain(marked);
				attr_assigned = true;
				children = new DNode[classify.getAttributes(attribute).Length];
				//Console.WriteLine("Attrib: " + attribute + " Children: " + classify.getAttributes(attribute).Length);
				for(uint x=0; x < children.Length; x++)
				{
					marked[attribute] = true;
					string tmp = classify.getAttributes(attribute)[x];
					children[x] = new DNode(classify.partitionData(attribute,tmp),ref marked,tmp);
				}
			}

		}

		public string getPathToNode()
		{ return path; }

		private string markedString(bool[] marked)
		{
			string retval = "";
			for(int x=0; x < marked.Length; x++)
			{ retval += (marked[x]) ? "T," : "F,"; }
			return retval;
		}

		private bool allMarked(ref bool[] marked)
		{
			foreach(bool b in marked)
			{ if(!b) { return false; } }
			return true;
		}

		public void printTree(int depth)
		{
			//add spaces
			for(int x=0; x<depth; x++)
			{ Console.Write(" "); }

			Console.Write("<node> Attribute: ");
			if(attr_assigned) { Console.Write(attribute); } 
			else { Console.Write("-");}
			Console.Write(" Path: " + path + " Classification: " + classification +"\n");
			if(children != null)
			{
				for(int x=0; x < children.Length; x++)
				{ children[x].printTree(depth+1); }
			}
		}
	}


}

