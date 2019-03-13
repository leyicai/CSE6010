Author          : Leyi Cai
Created         : August 23, 2018
Last Modified   : August 29, 2018

Affiliation          : Georgia Institute of Technology


Description
-------------

This program defines a two-dimensional matrix with m rows, and n columns that is filled with randomly
generated 1’s and 0’s. The probability of a '1' is p and the probability of a '0' is 1-p. 

The matrix is modified to satisfied the following rules:
 - For row i, if there is a ‘1’ in any cell of the original matrix then all cells in the entire row
should be set to 1. 
 - For column j, if there is a ‘1’ in any cell of the original matrix then all cells in the entire
column should be set to 1. 


Installation
------------

To install, simply run

    gcc 1A.c


Execution
-----------

Assuming your executable is called "a", run it using

    ./a.out


