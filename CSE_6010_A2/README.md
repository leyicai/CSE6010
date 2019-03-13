Author          : Leyi Cai
Created         : 09/14/2018
Last Modified   : 09/27/2018

Affiliation          : Georgia Institute of Technology


Description
-------------
There are two program in this project.
1. The first program is to generates graph. It generates grid with size of K * K filled with randamly "colored" nodes with the probability P. The graph that consist of these "colored" nodes would be stored in adjacency lists and written into file.

2. The second program is to analyze the graph. It read graph file and analyzes the statistics of components in the graph, then write the analysis into a file.


Installation
------------

To install the first program, simply run

    gcc graphgen.c graph.c -std=c99 -o graphgen

To install the secon program, simply run

    gcc components.c graph.c -std=c99 -o components
Note: The -std=c99 flag is required on some C compilers
to allow variable declarations at arbitrary locations in
a function.

Execution
-----------

Assuming the your first executable is called "graphgen", run it using

    ./graphgen K P topology.txt

Note: K is the size of grid; P is the probability of "colored" nodes; `topology.txt` is the output file that contains the infomation of generated graph.

For example, if you need to genrate a graph with size of 10*10 and probability 0.4, you can run it using

    ./graphgen 10 0.4 topology.txt

Assuming your second executable is called "components",
run it using

    ./components topology.txt output.txt

Note: `topology.txt` is the graph file that generates by "graphgen"; `output.txt` is the file that you tend to store the analysis of your graph.

