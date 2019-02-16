# CSCI4448
This repository is for all assignments from CSCI4448.

## HW1
To run this you can just use the makefile and then run the produced executable (called hw1).

## HW2
To run this you can just run the file main.py (using Python 3). Because Python has no private variables, all variables that were intended to be private were prefixed with an underscore, and instead of getters and setters, I used Python's properties. I also made some of the properties nontrivial, for example, setting the rectangle's corners asserts that the upper left and lower right corners are valid. Another change I made was using a list of points (with an assert to check that the length was 3) in Triangle instead of 3 separate points. I also used Python's tuples instead of a Point class. These changes make the code more simple and more robust.

## HW3
To run this, just run the makefile in HW3 and then run the produced executable (called hw3).
