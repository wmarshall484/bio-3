Final project for bioinformatics:

Compile the project by typing make. 

The program it created will build either a UPGMA tree or a
NeighborJoining tree depending on the parameters with which you run
the program.

./main 0 inputGrid.grid

will make a UPGMA tree from the file inputGrid.grid

./main 1 inputGrid.grid

will make a NeigborJoining tree from the file inputGrid.grid

The write-up for Project3 is found in BioProject3.pdf

The trees are outputted as the following example:

 id=0 AAAA
      intern id=4 l=0 r=1 l=0.75 r=1.25
 id=1 BBBB
		intern id=6 l=4 r=5 l=0.125 r=0.125
 id=2 CCCC
      intern id=5 l=2 r=3 l=1.25 r=0.75
 id=3 DDDD

Each line with a string such as "AAAA" is a leaf node, and the string
is the identifier for that leaf node. Each line with "intern" is an
internal node. Each internal node has four or five attributes: "id" is
the unique id of that node, "l" is the id of the left child, "r" is
the id of the right child, "lw" is the left weight of the node, "rw"
is the right weight of the node, and "h" is the height of the
node. The hight attribute is ommitted for NeighborJoining trees.