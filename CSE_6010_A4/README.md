Author          : Leyi Cai
Affiliation          : Georgia Institute of Technology


Description
-------------
This program is used to compute matrix multiplication in a parallel way using OpenMP. Two versions of parallel code are included, static mapping and dynamic mapping.

Installation
------------

To install the first program, simply run

    gcc main.c -std=c99 -o a4 -fopenmp


Execution
-----------

Assuming the your executable is called "a4", run it using

    ./a4
Note: If you want to modify the matrix size or the number of threads, please change the `#define` lines in `main.c`.