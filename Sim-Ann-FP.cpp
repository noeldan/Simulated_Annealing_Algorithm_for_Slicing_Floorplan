#include "Sim-Ann-FP.h"

#define inputfile

//#define seed_multiple

int main()
{
	string file_str;
	ifstream input_file;
	area_map am;
	SA* sa;
	vector<string> npe, npe1, npe2;
	char* temp[3];
	char file_cont[100];
	float area, ratio1;

	float tree_area;
	
	cout << "\nEnter input File = ";
	
	#ifdef inputfile
	
	cin >> file_str;						// Obtains the input filename
	input_file.open(file_str.c_str());				// Opens the input file
	
	#endif
	
	#ifndef inputfile
	
	cout << " input_file.txt" << endl;
	input_file.open("input_file.txt");
	
	#endif
	
	if(input_file.is_open())
	{
		while(!input_file.eof())				// Checks for End of file
		{
			input_file.getline(file_cont, 100);

			temp[0] = strtok(file_cont, " ,\t");		// Obtains the name
		
			if(temp[0])
			{
				temp[1] = strtok(NULL, " ,\t");		// Obtains the Area
				temp[2] = strtok(NULL, " ,\t");		// Obtains the Ratio
			
				area = atof(temp[1]);			// assigns the Area of the node
				ratio1 = atof(temp[2]);			// assigns the Ratio of the node
				
				am[temp[0]] = make_pair(sqrt(area * ratio1), sqrt(area / ratio1));	// Converts (Area, Ratio) to (width, height)
			}
		}
		input_file.close();					// Closes input file
	}
	
	sa = new SA(am);						// Allocates a new class SA for operations
	
	cout << "\n";
	
	#ifndef seed_multiple
	srand(iseed);
	#endif
	
	/************************ Topology 1 ************************/
	
	area_map::const_iterator i = am.begin();
	
	npe.push_back(i->first);					// Begins the Creation of Topology
	i++;								// 12V3V4V5V6V7V8V9VaVbVcVdVeVfVgViVjVkVlV
	
	npe.push_back(i->first);
	i++;
	
	for(;i != am.end(); i++)
	{
		npe.push_back(V);
		npe.push_back(i->first);
	}

	npe.push_back(V);						// Topology-1 created
	
	cout << endl;
	cout << "********************************Topology 1********************************" << endl << endl;
		
	cout << "Initial Topology-1 :- ";
	sa->printexp(npe);						// Prints Topology-1
	
	tree_area = sa->cost_calc(npe);					// Calculates Inital area of Topology-1
	
	cout << "Inital Area - " << tree_area << endl << endl << endl;	// Prints area Topology-1 
	
	cout << "Simulated Annealing Process" << endl;
	cout << "----------------------------" << endl;
	
	#ifdef seed_multiple 
	srand(iseed);
	#endif	
	
	sa->SimulatedAnnealing(npe);					// Performs Simulated Annealing on Topology 1
	
	cout << "Optimized Topology-1 :- ";
	sa->printexp(npe);						// Prints the Optimized Topology-1
	
	tree_area = sa->cost_calc(npe);					// Calculates optimized area of Topology-1
	
	cout << "Optimized Area - " << tree_area << endl << endl;	// Prints Optimized area Topology-1 
	
	cout << "**************************************************************************" << endl << endl;

	
	
	
	/************************ Topology 2 ************************/
	
	i = am.begin();
	
	npe1.push_back(i->first);					// Begins the Creation of Topology
	i++;								// 12H3H4H5H6H7H8H9HaHbHcHdHeHfHgHiHjHkHlH
	
	npe1.push_back(i->first);
	i++;
	
	for(;i != am.end(); i++)
	{
		npe1.push_back(H);
		npe1.push_back(i->first);
	}

	npe1.push_back(H);						// Topology-2 created
	
	cout << "********************************Topology 2********************************" << endl << endl;
	
	cout << "Topology-2 :- ";
	sa->printexp(npe1);						// Prints Topology 2
	
	tree_area = sa->cost_calc(npe1);				// Calculates area of Topology-2
	
	cout << "Area - " << tree_area << "\n\n\n";			// Prints area Topology-2
	
	cout << "Simulated Annealing Process" << endl;
	cout << "----------------------------" << endl;
	
	#ifdef seed_multiple
	srand(iseed);
	#endif
	
	sa->SimulatedAnnealing(npe1);					// Performs Simulated Annealing on Topology 2
	
	cout << "Optimized Topology-2 :- ";
	sa->printexp(npe1);						// Prints Optimized Topology-2
	
	tree_area = sa->cost_calc(npe1);				// Calculates Optimized area of Topology-2
	
	cout << "Optimized Area - " << tree_area << endl << endl;	// Prints Optimized area Topology-2 
	
	cout << "**************************************************************************" << endl << endl;
	
	
	
	
	/************************ Topology 3 ************************/
	
	static const string exp[] = {"2", "1", "3", "5", "4", "6", "H", "7", "V", "H", "V", "a", "8", "V", "9", "H", "c", "V", "H", "g", "H", "i", "b", "d", "H", "k", "V", "H", "f", "e", "H", "V", "l", "H", "V", "j", "H", "V", "H"};
	
	npe2.assign(exp, exp + ((sizeof(exp)) / (sizeof(exp[0]))));	// Topology - 213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH is created
	
	cout << "********************************Topology 3********************************" << endl << endl;
	//cout << "-------------------------------------------------------------" << endl << endl;
	
	cout << "Topology3  :- ";
	sa->printexp(npe2);						// Prints Topology 3
	
	tree_area = sa->cost_calc(npe2);				// Calculates area of Topology-3
	
	cout << "Area - " << tree_area << "\n\n\n";			// Prints area Topology-3
	
	cout << "Simulated Annealing Process" << endl;
	cout << "----------------------------" << endl;
	
	#ifdef seed_multiple
	srand(iseed);
	#endif
	
	sa->SimulatedAnnealing(npe2);					// Performs Simulated Annealing on Topology 3
	
	cout << "Optimized Topology-3 :- ";
	sa->printexp(npe2);						// Prints Optimized Topology-3
	
	tree_area = sa->cost_calc(npe2);				// Calculates Optimized area of Topology-3
	
	cout << "Optimized Area - " << tree_area << endl << endl;	// Prints area Topology-3 
	
	cout << "**************************************************************************" << endl << endl;
	
	return 0;
}
