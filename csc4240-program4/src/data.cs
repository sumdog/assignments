//
//  Sumit Khanna -- CSC 4240 - Program 4 - Dr. Talber's AI Class
//
//		data.cs - contains the data structers for holding the 
//                sample data information
using System;
using System.IO;
using System.Collections;

namespace sum.data 
{

	//single row of data from input file
	public class DataRow
	{
		private string[] data;
		public string correctclass;

		public DataRow(String a, AttributeSet attrset, ClassificationSet classset) 
		{
			string[] split = a.Split(',');
			data = new string[split.Length-1];

			for(uint x=0; x < split.Length-1; x++) 
			{ 
				data[x] = split[x];
				attrset.addAttribute(x,split[x]);
			}
			correctclass = split[split.Length-1];
			classset.addClassification(correctclass);
		}

		public bool hasAttribute(uint index, string attr)
		{ return data[index].Equals(attr); }

		public string getAttribute(uint index)
		{ return data[index]; }

		public bool checkClass(string s) { return s.Equals(correctclass); }

		public string originalString()
		{
			string retval = "";
			for(uint x=0; x < data.Length; x++)
			{ retval += data[x]+","; }
			retval += correctclass;
			return retval;
		}

		public override string ToString() 
		{
			string retval = "";
			retval += "Attributes: ";
			for(uint x=0; x<data.Length; x++)
			{ retval += data[x] + ','; }
			retval += "\nCorrect Class: " + correctclass;
			return retval;
		}
	}

	//class that keeps track of which discrete values apply to each attribute
	// (contiains an array of Attributes)
	public class AttributeSet 
	{
		private Attributes[] attrs;

		public AttributeSet(uint num_attributes)
		{
			attrs = new Attributes[num_attributes];
			for(uint x=0; x < attrs.Length; x++)
			{ attrs[x] = new Attributes(); }
							  
		}

		//overloaded operator for simplicity
		public Attributes this[uint index] { get {return attrs[index];} }

		public int occurance(uint aidx, string attr)
		{
			return attrs[aidx].numAttrib(attr);
		}

		public uint getLength() 
		{ return (uint) attrs.Length; }

		public void addAttribute(uint index, string attr)
		{ attrs[index].addAttribute(attr); }

		public override string ToString()
		{
			string retval = "";
			for(uint x=0; x < attrs.Length; x++)
			{
				retval += "Possible Values for Attribute: " + x + "\n";
				retval += attrs[x] + "\n";
			}
			return retval;
		}

	}

	public class Attributes : AbstractSet
	{
		public Attributes() : base() {}
		public void addAttribute(string s) { add(s); }
		public int numAttrib(string s) { return numElement(s); }
	}

	public class ClassificationSet : AbstractSet
	{
		

		public ClassificationSet() : base() {}

		public void addClassification(string s) 
		{ add(s); }

		public int numClass(string s)
		{ return numElement(s); }
	}
	
	public abstract class AbstractSet
	{
		private string[] attrs;
		private uint size, capacity;
		private Hashtable numclass;

		public AbstractSet()
		{
			size = 0;
			capacity = 10;
			attrs = new string[capacity];
			numclass = new Hashtable();
		}

		protected int numElement(string s)
		{ return (int) numclass[s]; }

		public override string ToString()
		{
			string retval = "";
			for(uint x=0; x<size; x++)
			{ retval += attrs[x] + " "; }
			return retval;
		}

		//these two functions provide easy access to this object
		// using the [] operators and the size property
		// Note: all fields are readonly (no set functions)
		public string this[uint index] { get {return attrs[index];} }
		public uint length { get {return size;} }

		protected void add(string s)
		{
			if(size == capacity)
			{ growArrayByTen(); }
			if(!exists(s)) 
			{ attrs[size++] = s; }

			if(! numclass.ContainsKey(s) )
			{ numclass.Add(s,1); }
			else
			{ numclass[s] = ((int)numclass[s]) + 1;}
		}

		private bool exists(String s)
		{
			bool retval = false;
			for(uint x=0; x < size; x++)
			{ 
				if(attrs[x].Equals(s)) { retval = true; }
			}
			return retval;
		}

		private void growArrayByTen()
		{
			string[] temp = new string[attrs.Length+10];
			for(uint x=0; x < attrs.Length; x++)
			{ temp[x] = attrs[x]; }
			capacity = (uint) temp.Length;
			attrs = temp;
		}
	}

	//master class which holds all data rows, attributeset and classificationset
	public class DataSet
	{
		private AttributeSet attribs;

		private ClassificationSet classes;

		private DataRow[] rows;
		private uint capacity,size;
		//private bool[] marked;

		public DataSet(String filename)
		{
			rows = new DataRow[10];
			capacity = 10;
			size = 0;

			StreamReader reader = new StreamReader(filename);
			String input = reader.ReadLine();
			
			attribs = new AttributeSet((uint) input.Split(',').Length-1);
			classes= new ClassificationSet();

			//marked = new bool[attribs.getLength()];
			//for(uint x=0; x < marked.Length; x++)
			//{ marked[x] = false; }

			while(input != null) 
			{
				if(size == capacity) { growRowsByTen();}
				rows[size++] = new DataRow(input, attribs, classes);
				input = reader.ReadLine();
			}
		}

		public uint numAttributes()
		{ return attribs.getLength(); }

		public DataSet(uint attrs)
		{
			rows = new DataRow[10];
			capacity = 10;
			size = 0;

			attribs = new AttributeSet(attrs);
			classes = new ClassificationSet();

			//this.marked = marked;
			//this.marked[attrs] = true; //mark this 
		}

		public void addRow(String s)
		{
			if(size == capacity) { growRowsByTen(); }
			rows[size++] = new DataRow(s, attribs, classes );
		}

		public uint numRows() { return size; }
		public DataRow getRow(uint u) { return rows[u]; }
/*
		public bool allMarked()
		{
			for(uint x=0; x < marked.Length; x++)
			{ if(marked[x] == false) {return false;} }
			return true;
		}
		public bool isMarked(uint i)
		{ return marked[i]; }
*/
		public string[] getAttributes(uint aidx)
		{
			string[] retval = new string[attribs[aidx].length];
			for(uint x=0; x < retval.Length; x++)
			{ retval[x] = attribs[aidx][x]; }
			return retval;
		}

		public DataSet partitionData(uint aidx, string v)
		{
			DataSet retval = new DataSet(attribs.getLength());
			for(uint x=0; x < size; x++)
			{
				if(rows[x].hasAttribute(aidx,v))
				{ retval.addRow(rows[x].originalString()); }
			}
            return retval;
		}

		//gets the number of rows which have the attribute value of attr
		//for attribute number aindex and which contain the correct
		//classification goal
		private uint getElements(uint aindex, string attr, string goal)
		{
			uint count = 0;
			for(uint x=0; x < size; x++)
			{
				if(rows[x].hasAttribute(aindex,attr) && rows[x].checkClass(goal))
				{count++;}
			}
			return count;
		}

		public string getMostOccuringClassification()
		{
			Hashtable counters = new Hashtable();

			for(uint x=0; x < classes.length; x++)
			{
				if(!counters.Contains(classes[x]))
				{ counters.Add(classes[x],1); }
				else
				{ 
					int a = (int) counters[classes[x]];
					counters[classes[x]] = a++;
				}
			}
			
			IDictionaryEnumerator e = counters.GetEnumerator();
			string gstr = "";
			int gint = 0;
			while(e.MoveNext())
			{
				if( ((int)e.Entry.Value) > gint )
				{ 
					gint = ((int)e.Entry.Value);
					gstr = ((string)e.Entry.Key);
				}
			}
			return gstr;
		}

		public uint bestGain(bool[] marked)
		{
			double bestval = -1;
			uint bestidx = 0;
			for(uint x=0; x < attribs.getLength(); x++)
			{
				if(!marked[x] && gain(x) > bestval)
				{ 
					bestval = gain(x);
					bestidx = x;
				}
			}
			//Console.WriteLine("Best Attribute: " + bestidx + " Gain: " + bestval);
			return bestidx;
		}

		public double gain(uint aidx)
		{
			double f = entropy;
			for(uint x=0; x < attribs[aidx].length; x++)
			{
				f += entropyAttr(aidx,attribs[aidx][x]) * -1 * ((double) attribs.occurance(aidx,attribs[aidx][x]) / (double) size);
				//Console.WriteLine("num1: " + entropyAttr(aidx,attribs[aidx][x]));
				//Console.WriteLine("num2: " + attribs.occurance(aidx,attribs[aidx][x]));
				//Console.WriteLine("num3: " + size);
				//Console.WriteLine("Gain--:" + f);
			}
			return f;
		}

		public double entropyAttr(uint aidx, string attr)
		{
			double f = 0;
			for(uint x=0; x < classes.length; x++)
			{
				double m = (double) getElements(aidx,attr,classes[x]);
				double n = (double) attribs.occurance(aidx,attr);
				if(m != 0)
				{ f += (-m/n)*Math.Log((m/n),2); }
				//Console.WriteLine("M: " + m + " N: " + n + "F: " + f);
			}
			return f;
		}
		
		public double entropy 
		{
			get 
			{
				double f = 0;
				for(uint x=0; x < classes.length; x++)
				{
					double ratio = (double) classes.numClass(classes[x]) / (double) size;
					f += (-1 * ratio) * Math.Log(ratio,2);
					//Console.WriteLine(f);
				}
				return f;
			}
		}

		public override string ToString()
		{
			string retval = "";
			for(uint x=0; x < size; x++)
			{ 
				retval += "Row " + x + ":\n";
				retval += rows[x] + "\n";
			}
			retval += "\n" + attribs;
			retval += "\nPossible Classifications: ";
			retval += classes;
			return retval;
		}

		private void growRowsByTen()
		{
			DataRow[] temp = new DataRow[capacity+10];
			for(uint x=0; x < rows.Length; x++)
			{ temp[x] = rows[x]; }
			capacity = (uint) temp.Length;
			rows = temp;
		}

	}

}