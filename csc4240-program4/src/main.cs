//
//  Sumit Khanna -- CSC 4240 - Program 4 - Dr. Talber's AI Class
//
//    This program implements ID3 Classification and Testing
//
//     main.cs - main entry point into program
//                  program takes two arguments, a classification and 
//                  a testing file. It creates an ID3 tree with the 
//                  classification data and then attempts to classify
//                  the test data and return an error rate.
//       Depends: Data.cs - Data Structers for Parsing Input files
//                Tree.cs - Actual ID3 tree
using System;
using sum.data;
using sum.tree;


namespace sum
{


	class main
	{

		static DataSet classify;
		static DataSet test;

		//Entry Point
		[STAThread]
		static int Main(string[] args)
		{
			if(args.Length != 2) 
			{ 
				usage(); 
				return 2;
			}
			//Console.WriteLine(new DataSet("sample1.txt"));
			try
			{
				classify = new DataSet(args[0]);
				test = new DataSet(args[1]);
			}
			catch(System.IO.IOException e)
			{ Console.WriteLine(e.Message);	}

			//make tree
			DTree tree = new DTree(classify);
			tree.printTree();
			DTestResults results = tree.testTree(test);
			Console.WriteLine("Correct/Total: " + results.correct + " / " + results.total);
			Console.WriteLine("Error Rate: " + ((double)results.correct/(double)results.total));
			//Console.WriteLine(classify.gain(3));
			//Console.WriteLine(classify.entropyAttr(3,"Weak"));
			//Console.WriteLine(classify.entropy);
			//Console.WriteLine(classify.partitionData(0,"Rain"));
			//Console.WriteLine("Num Attribs: " + classify.numAttributes());
/*
			bool[] marked = new bool[classify.numAttributes()];
			for(int x=0; x < marked.Length; x++) 
			{ marked[x] = false; }

			for(int x=0; x < marked.Length; x++)
			{ 
				uint a = classify.bestGain(marked); 
				marked[a] = true;
				Console.WriteLine(a);
			}
			Console.WriteLine(classify.getMostOccuringClassification());
			
			//Console.WriteLine("A" + classify.gain(2));
			*/
		return 0;
		}

		//usage statement for invalid commandline params
		static void usage() 
		{
			string output = "";
			output += "\ncsc4240-program4.exe  Usage:\n";
			output += "\n\tcsc4240-program4.exe <classification file> <test file>\n\n";
			Console.Write(output);
		}
	}
}
