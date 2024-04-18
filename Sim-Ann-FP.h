#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include<algorithm>
#include<stack>
#include<stdlib.h>
#include<cassert>

#define H "H"
#define V "V"

#define nmoves    10
#define ratio     0.85
#define t0        -1
#define lambdatf  0.005
#define iseed     3
#define P         0.99
#define epsilon   0.001

using namespace std;


typedef map<string, pair<float, float> > area_map;    // area_map maps the name of the module with width and heigh pair 


class node
{
	string name;                       // name of the node
	vector<pair<float, float> > wh;    // vector pair of the width and height combination

	friend class SA;                   // class SA is given permission to access the name and width-height pair of class node
	
	public:
		node(string a, vector<pair<float, float> > b) : name(a), wh(b) {};    // node constructor
};


class SA
{
	area_map am;    
	
	public:
	
	SA(area_map x) : am(x){}    // Consstructor for class SA
	
	void printexp(vector<string> &exp);
	float cost_calc(vector<string> &exp);
	vector<node*> create_tree(vector<string> &exp);
	void stack_tree(node *a, node *b, node *c);
	bool ballot(vector<string> &a);
	bool skewed(vector<string> &a);
	void M1move(vector<string> &a);
	void M2move(vector<string> &a);
	void M3move(vector<string> &a);
	float InitialTemp(vector<string> &a);
	void SimulatedAnnealing(vector<string> &a);
};


/* InitialTemp() function calculates the initial temperature required for the simulated annealing process */
float SA::InitialTemp(vector<string> &npe)
{
	int noofloops = 0;				// Iterator for number of loops
	int uphill_moves = 0;				// Iterator for number of uphill moves
	
	float old_cost = cost_calc(npe);		// Calculates the cost of the initial topology
	float new_cost = 0.0;
	float diff_cost;
	
	float sum_cost = 0.0;
	
	float avg_diff;
	
	float init_temp;
	int ranVar;
	
	while(noofloops < 40)
	{
		ranVar = rand() % 3 + 1;		// Randomly generates a number between 1 to 3
		
		switch(ranVar)				// Based on the random number the respectve move is chosen
		{
		  case 1:
		  {
			M1move(npe);			// Implements M1 move
			break;
		  }
		  
		  case 2:
		  {
			M2move(npe);			// Implements M2 move
			break;
		  }
		  case 3:
		  {
			M3move(npe);			// Implments M3 move
			break;
		  }
		}
		
		new_cost = cost_calc(npe);		// Calculates the cost of new topology

		diff_cost = new_cost - old_cost;	// Calculates the difference between new and old cost
		
		if(diff_cost > 0)			// Checks if the new cost is greater than the old cost
		{
			old_cost = new_cost;		// Old cost is updated with the new cost
			
			sum_cost += diff_cost;		// Sum of the cost differences is calculated
			
			uphill_moves++;			// Number of uphill moves is incremented
		}

		noofloops++;				// Number of loops is incremented
	}
 
	avg_diff = (sum_cost / uphill_moves);		// Calcuates the average cost difference with uphill moves
	
	init_temp = ((t0 * avg_diff) / log(P));		// Initial temperature is calculated. P is the initial probability of the uphill moves
	
	return init_temp;
}


void SA::SimulatedAnnealing(vector<string> &npe)
{
	const int N = nmoves * (int)(am.size());			// Calcuates the total number of uphill moves
	
	vector<string> npeBest = npe;					// Best topology is initialized
	vector<string> npeTemp = npe;					// Temporary topology is initialized
	
	float T0;
	float T;
	
	int total_moves;
	int uphill_moves;
	int reject;
	
	float old_cost, new_cost, diff_cost;
	
	int ranVar;
	
	double dble_ranVar;
	
	T0 = InitialTemp(npeTemp);					// Initial temperature is calculated
	T = T0;								// Temperature is updated with initial temperature
	
	do{
		total_moves = 0;
		uphill_moves = 0;
		reject = 0;
	  
		do{
			old_cost = cost_calc(npeTemp);			// Cost of temporary topology is calculated
			
			ranVar = rand() % 3 + 1;			// Random number beteween 1 to 3 is generated
			
			switch(ranVar)					// Based on the random number respectve move
			{
			  case 1:
			  {
				M1move(npeTemp);			// M1 move is performed on the temporary topology
				break;
			  }
			  case 2:
			  {
				M2move(npeTemp);			// M2 move is performed on the temporary topology
				break;
			  }
			  case 3:
			  {
				M3move(npeTemp);			// M3 move is performed on the temporary topology
				break;
			  }
			}

			total_moves++;					// Total number of moves is incremented
			
			new_cost = cost_calc(npeTemp);			// Cost of temporary topology is calculated
			
			diff_cost = new_cost - old_cost;		// Calcuates the difference between new and old topology
			
			dble_ranVar = (((double) rand()) / (RAND_MAX));		// Randomly generates a number between 0 and 1

			if((diff_cost < 0) || (dble_ranVar < (exp((-1*diff_cost) / T))))	// Checks if cost difference is less than '0' or if random variable is less than exp(-d/T)
			{
				if(diff_cost > 0)				// Checks whether the cost difference is more '0'
				{
					uphill_moves++;				// Increments the number of uphill moves
				}

				npe = npeTemp;					// Topology is updated with temporary topology
				
				if(cost_calc(npe) < cost_calc(npeBest))		// Checks if the cost of initial topology is less than the Best topology
				{
					npeBest = npe;				// The initial topology is assigned to the Best topology
				}
			}
			else
			{
				reject++;					// Number of rejected moves is incremented
			}
		}while((uphill_moves < N) && (total_moves <= (2 * N)));		// Checks if the number of uphill moves is than total uphill moves
										  // and the total number of moves is less than twice the total uphill moves
		T = (T < (lambdatf * T0)) ? (0.1 * T) : (ratio * T); 		// New temperature is calculated
	  
	}while(((reject / total_moves) <= 0.95) && (T >= epsilon));		// Checks if number of rejected moves is less than or equal to 95% of total moves
										  // temperature is greater than epsilon
	npe = npeBest;								// Initial topology is updated with the best topology
}


/* M1move() function swaps the randomly chosen pair in the slicing tree represented by the vector string */
void SA::M1move(vector<string> &npe)
{
	int pos;
	int j = 0;
	int ranPos;

	vector<int> oprandPos;
	
	for(pos = 0; pos < npe.size(); pos++)
	{
		if((npe[pos] != H) && (npe[pos] != V))	// Checks for the position of the operand
		{
			oprandPos.push_back(pos);	// The position of the operand is recorded in the integer vector
			j++;
		}
	}

	ranPos = rand() % (j-1);			// Randomly generates a number which indicates a operand position
	
	iter_swap((npe.begin() + oprandPos[ranPos]), (npe.begin() + oprandPos[ranPos + 1]));	// Swaps the two adjacent operands
}


/* M2move() function complements the randomly chosen operator chain in vector string */
void SA::M2move(vector<string> &npe)
{
	int chainPos;
	vector<int> opratorChain;
	int j = 0;
	int chainOprator, ranPos;

	for(chainPos = 0; (chainPos + 1) < npe.size(); chainPos++)
	{
		if(((npe[chainPos] != H) && (npe[chainPos] != V)) && ((npe[chainPos + 1] == H) || (npe[chainPos + 1] == V))) // Checks for a chain of operators
		{
			opratorChain.push_back(chainPos + 1);		// Updates the postion of the operator chain
			j++;
		}
	}

	ranPos = rand() % j;		// Randomly generates a number which points a operator chain

	chainOprator = opratorChain[ranPos];		// Position number of the operator chain is obtained

	while(chainOprator < (int)npe.size())
	{
		if((npe[chainOprator] == H) || (npe[chainOprator] == V))	// Checks whether the operand is 'H' or 'V'
		{
			if(npe[chainOprator] == H)
			{
				npe[chainOprator] = V;				// Complements the 'H' operator to 'V' operator
			}
			else
			{
				npe[chainOprator] = H;				// Complements the 'V' operator to 'H' operator
			}
			
			chainOprator++;						// Pointer is incremented to point to the next operator in the operator chain
		}
		else
		{
			break;
		}
	}
}


/* M3move() function swaps the randomly chosen adjacent operator and operand pair in the vector string */
void SA::M3move(vector<string> &npe)
{
	int pairPos;
	vector<int> opPair;
	int j = 0;
	int ranPos, opPos;
	
	for(pairPos = 0; pairPos < (npe.size() - 1); pairPos++)
	{
		if(((npe[pairPos] != H) && (npe[pairPos] != V)) && ((npe[pairPos + 1] == H) || (npe[pairPos + 1] == V)))
		{
			opPair.push_back(pairPos);		// Position of the operand-operator pair is obtained
			j++;
		}
	}

	do{
		ranPos = rand() % (j-1);			// Randomly generates a number pointing to the operand-operator pair

		opPos = opPair[ranPos];				// operand-operator pair postion is obtained

		iter_swap((npe.begin() + opPos - 1), (npe.begin() + opPos));		// Swaps the operand and operator
	  
	}while(!(ballot(npe) && skewed(npe)));			// Checks the NPE for balloting property and checks whether it is skewed
}


/* skewed() function checks whehter the slicing tree represented by the vector string is skewed or not */
bool SA::skewed(vector<string> &npe)
{
	int iter;
	
	for(iter = 0; iter < npe.size(); iter++)
	{
		if(npe[iter] == H || npe[iter] == V)		// Checks whether the element is an operator
		{
			if(npe[iter] == npe[iter-1])		// Checks whether the adjacent element is a same operator
			{
				return false;			// If the adjacent operators are the same then the NPE is not skewed
			}
		}
	}
	
	return true;
}


/* ballot() function checks the balloting property for the vector string */
bool SA::ballot(vector<string> &npe)
{
	int iter;
	int oprators = 0, oprands = 0;
	
	for(iter = 0; iter < npe.size(); iter++)
	{
		if((npe[iter] == H) || (npe[iter] == V))
		{
			oprators++;				// Indicates the number of operator in the vector string
		}
		else if((npe[iter] != H) && (npe[iter] != V))
		{
			oprands++;				// Indicates the number of operands in the vector string
		}
	
		if(oprators >= oprands)
		{
			return false;				// If the operators are more than the operands then the balloting property is not satisfied
		}
	  
	}

	return true;
}



/*  create_tree() function creates the sliced tree from the vector string  */
vector<node*> SA::create_tree(vector<string> &a)
{
	vector<node*> tt;
	vector<string>::const_iterator i = a.begin();
	string name;
	node *nd;
	vector<pair<float, float> > wh;
	pair<float, float> wh_temp;
	float wid, hei;
	
	for(; i != a.end(); i++)  
	{
		name = *i;
		
		if((name != H) && (name != V))                                       // If the entry is an operand the 'if' condition is executed 
		{
			//vector<pair<float, float> > wh;
			wh_temp = am[name];                                          // Assigns the width-height combination to the 'wh_temp' pair
			wh.push_back(wh_temp);                                       // Allocates the width-height combination to the vector
						
			wid = wh_temp.first;
			hei = wh_temp.second;
			
			if(wid != hei)                                               // If width is not equal to height, the width-height combination is  
			{                                                              // reversed and allocated to the vector 'wh' as a new entry
				wh_temp = make_pair(wh_temp.second, wh_temp.first);
				wh.push_back(wh_temp);
			}
		
			nd = new node(name, wh);                                     // Creates a new node with given name and width-height vector combinations
			tt.push_back(nd);                                            // Allocates the node to the node vector
		}
		else                                                                 // If the entry is an operand the 'else' condition is evoked
		{
			//vector<pair<float, float> > wh;
			nd = new node(name, wh);                                     // Creates a new node with given name and width-height vector combinations
			tt.push_back(nd);                                            // Allocates the node to the node vector
		}
		
		wh.clear();
	}
  
	return tt;
}


/*  stack_tree() function assigns the relationship between operators and operands  */
/*  The function also assigns all the possible combinations of widths and heights for the operands  */
void SA::stack_tree(node *operand_a, node *operand_b, node *operator_c)
{
	vector<pair<float, float> >::iterator iter1, iter2, iter3, iter4;
	float w1, w2, h1, h2;
	float width, height;
	
	for(iter1 = (operand_a->wh).begin(); iter1 != (operand_a->wh).end(); iter1++)
	{
		w1 = (*iter1).first;								// Allocates the width of the first pair of the operand_a
		h1 = (*iter1).second;								// Allocates the height of the first pair of the operand_a
		
		for(iter2 = (operand_b->wh).begin(); iter2 != (operand_b->wh).end(); iter2++)
		{
			w2 = (*iter2).first;							// Allocates the width of the first pair of the operand_b
			h2 = (*iter2).second;							// Allocates the height of the first pair of the operand_b
			
			if(operator_c->name == H)						// 'if' condition is evoked when the operator is sliced Horizontally
			{		
				width = max(w1, w2);						// Maximum width is allocated for Horizontal slicing
				height = h1 + h2;						// Heights are added for Horizontal slicing
			}
			else									// 'else' condition is evoked when the operator is sliced Vertically
			{
				width = w1 + w2;						// Width are added for Vertical slicing
				height = max(h1, h2);						// Maximum height is allocated for Vertical slicing
			}
			
			pair<float, float> wh = make_pair(width, height);			// The new width-height pair is created
			 
			(operator_c->wh).push_back(wh);						// Width-Height pair is allocated to the Operator
		}
	}

	
	for(iter3 = (operator_c->wh).begin(); iter3 != (operator_c->wh).end(); iter3++)
	{
		w1 = (*iter3).first;								// Allocates the width of the first pair of the operator_c
		h1 = (*iter3).second;								// Allocates the height of the first pair of the operator_c
		
		for(iter4 = (iter3 + 1); iter4 != (operator_c->wh).end(); iter4++)
		{
			w2 = (*iter4).first;							// Allocates the width of the second pair of the operator_c
			h2 = (*iter4).second;							// Allocates the height of the second pair of the operator_c
		
			if((w1 >= w2) && (h1 >= h2))
			{
				iter3 = (operator_c->wh).erase(iter3);				// If w1 is greater than w2 and h1 is equal to h2
				iter3--;							  // or if h1 is greater than h2 and w1 is equal to w2
				break;								    // the pair <w1, h1> is erased
			}
			
			if((w2 >= w1) && (h2 >= h1))
			{	
				iter4 = (operator_c->wh).erase(iter4);				// If w2 is greater than w1 and h2 is equal to h1
				iter4--;							  // or if h2 is greater than h1 and w1 is equal to w2
			}									    // the pair <w2, h2> is erased
		}
	}
}


/*  cost_calc() function calculates the minimum area for the NPE expression  */
float SA::cost_calc(vector<string>& a)
{
	vector<node*> v_nd = create_tree(a);
	stack<node*> stack_nd;
	vector<node*>::iterator i;
	node *nd, *nd1, *nd2, *final_nd;
	vector<pair<float, float> >:: iterator iter;
	
	for(i = v_nd.begin(); i != v_nd.end(); i++) 
	{
		nd = *i;
		
		if((nd->name != H) && (nd->name !=V))   // If the entry is an operand the 'if' condition is evoked
		{
			stack_nd.push(nd);              // Pushes the node to the stack
		}
		else                                    // If the entry is an operator the 'else' condition is evoked
		{
			nd1 = stack_nd.top();           // node nd1 is allocated the top of the stack address
			
			stack_nd.pop();                 // Pops an second operand entry from the the stack
			
			nd2 = stack_nd.top();           // node nd2 is allocated the top of the stack address
			
			stack_nd.pop();                 // Pops an first operand entry from the the stack
			
			stack_tree(nd1, nd2, nd);       // stack_tree() function is called to create a operator-operands combination
			
			stack_nd.push(nd);              // The new operator-operand combination is pushed to the stack
		}
	}
	
	final_nd = stack_nd.top();                                               //  The root node is allocated to the node final_nd
	
	float cost_area = 100000000000.0;					    // Allocates the highest possible area
	
	for(iter = (final_nd->wh).begin(); iter!=(final_nd->wh).end(); iter++)      // The for loop calculates the area for each width-height
	{										// combination of the root node(entire floorplan)
		float area = ((*iter).first) * ((*iter).second); 		    // Computes the are for the current width-height combination
		
		if(area < cost_area)
		{
			cost_area = area;					    // Allocates the minimum area for each iteration
		}
	  
	}
	
	return cost_area;

  
}


/*  printexp() function prints the NPE expression in Post Traversal order  */
void SA::printexp(vector<string> &exp)
{
	vector<string>::const_iterator i = exp.begin();
  
	for(;i != exp.end(); i++)
	{
		cout << *i;
	}
	
	cout << "\n";
}
 
