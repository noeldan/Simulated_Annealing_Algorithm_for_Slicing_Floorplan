Simulated Annealing Algorithm for Slicing Floorplan

First Part
-----------
Programming assignment: Here you are required to program a part of the simulated annealing algorithm for slicing floorplan. The algorithm is described in detail in the textbook (page 121), and is also discussed in class. This routine will be used in future assignments to develop the entire algorithm.

a. Implement the slicing tree sizing algorithm, which takes a floorplan topology and a list of possible shapes for each module and computes the optimal area for the floorplan using the algorithm discussed in class and also in Example 3.4 in the textbook. In order for this procedure to be used in the simulated annealing, use normalized polish expression to describe the topology in the input. 

Name your routine as cost() that takes a NPE as its input.

Input Formats: The input file consists of:

1. Names, areas and aspect ratios of the modules. They are of the form:
1)  13.60 0.52
2)  3.69 0.30
3)  16.71 0.50
4)  1.87 0.35
5)  5.29 1.15

The i-th row provides information of module i, for all i = 1, 2… n.
It consists of (Ni, Ai, Ri) where Ni is the module name, Ai is the area of module i and Ri is the aspect ratio of module i. For example, module 2 has area 3.69 and an aspect ratio of 0.3.

Instructions on submission:

1. PLEASE USE INPUT FILE “input_file.txt” AS AN INPUT FOR YOUR PROGRAM

2. Output: Please output the topology (NPE) and the cost of the floorplan (area).

3. For the given input file, in your main() program, invoke the cost() routine with the following topologies within your code, printing the topology and area each time.
a. 12V3V4V……kVlV
b. 12H3H4H…….kHlH
c. 213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH

This assignment will be graded on the following criteria
a) Correct execution - we will test your area for 3a, 3b, 3c.
b) Code commenting - will be awarded for properly commenting the code.
c) Working code – These points will be awarded for a completed program that works and outputs the area and topology.


Second Part
------------
Programming assignment: Here you are required to program the entire simulated annealing algorithm for slicing floorplan. The algorithm is described in detail in the textbook (page 121), and is also discussed in class. To develop this algorithm, you will use the cost() routine developed in First Part.

a. Use the cost() algorithm as the subroutine to evaluate a given topology, implement the simulated annealing algorithm to find a good floorplan for a given set of modules. The objective function is the area of the floorplan (Cost = Area). For this assignment, we will not consider the wire length for optimization. Also, all the modules will be hard modules with free orientations.

Input Formats:
- - - - - - - - - - - -
The input consists of two parts:
1. Parameters (these will be hard coded in your code).
2. Names, areas and aspect ratios of the modules – This will be in the same format as input_file.txt used for First Part.

More detailed description of parameters.
1. Parameters
They are of the following form:
.2.0     (* chipratio *)
.10      (* nmoves *)
.0.85    (* ratio *)
.-1      (* t0 *)
.0.005   (* lambdatf *)
.3       (* iseed *)
.6       (* n *)
.0.99    (* P *)
.0.001   (* epsilon *)

chipratio: Final chip ratio must be between 1/chipratio and chipratio; chipratio must be greater than 1.0

nmoves: Number of attempt moves per temperature iteration. Use 10 as the default value. Larger values of nmoves in general produce better results. The total execution time of the program grows linearly with respect to nmoves.

Ratio: Ratio for decreasing temperatures. Use 0.85 as the default value. Larger values of ratios in general produce better results and have much longer execution time.

t0: Initial temperature. If the input t0 is negative (e.g. -1), the program will compute an initial temperature (in this case you will need to add a negative sign to make the initial temperature positive); otherwise the program will use the input positive t0 as the initial temperature. Default value is -1.

lambdatf: The program will change ratio to 0.1 when temperature falls below lambdatf * t0. After ratio is set to 0.1, the program in general will terminate very quickly.

iseed: Seed for random number generator.

n: Number of modules (this will depend on your input file).

P: Initial probability of accepting uphill moves

Instructions on submission:
1. PLEASE USE INPUT FILE “input_file.txt” AS AN INPUT FOR YOUR PROGRAM (we will however test your program with other input files as well)
2. Output: Please output the initial topology, initial cost, and the final optimized topology and the final cost in your program (after annealing). Do not print out topology or cost in intermediate iterations.
3. The program should include all the three topologies given in First Part.
This assignment will be graded on the following criteria
a) Correct execution - we will test your programs for different test files.
b) Code commenting - will be awarded for properly commenting the code.
c) Solution quality – We will check the performance of the annealer from the quality of the final floorplan.
