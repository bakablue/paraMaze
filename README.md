ParaMaze
========

A maze parallelized with two algorithms:
* Maze-solving Cellular Automaton that works only on perfect mazes
* Path-solving Cellular Automaton that works on every mazes

This program is combined with a gui in Qt.

States of the maze
------------------

* Free: free cell
* Wall
* Start: Start of the maze
* End: End of the maze
* Path: Represent the path of the maze

Steps of the programs
---------------------
* Simple parsing of a map constitued of
** On the first line: the width and the height
** THe rest of the file represents the maze
* Constitution of the map of the program
* Launch of the gui
* Resolution of the maze

Option of the program
---------------------
There will be several options:
* One to choose between to parallelize or not our program
* One to activate the gui
* One to display every map during the resolution of the map (cout)
* One to choose between the algorithm for perfect maze or the other
