# Jons-Rubiks-Cube-Timer
This is my Rubik's cube timer Idea. After using planty of timers, I've decided that I wanted to make something that generates algorithms, stores times accurately, can graph your progress, and allows you to practice algorithms in an efficient way using those same graphs.

To run the program, make sure you go to the "Jons-Rubiks-Cube-Timer" Folder from the repo, and run ./build_and_run.sh in the terminal. App currently only works on mac and linux, it should work on windows.

# How Do I use this app?
So when you open up the build_and_run file, you are presented with a home screen. You can press any button and you are sent to the main menu.

In the main menu, you can choose between scrambler, data visualizer (not working yet), algorithm practice, and timer (not working yet. 

# Warnings:
Do not mess around too much with your data files as there is currently no way for the parsers i created to validate missing data (in most places). Try to follow the format for all data and if worst comes to worst you can reach out for the data default format so you can re-format your data appropriately.
# Scrambler

When you open the scrambler, you are presented with a scramble and an option to press any button. These scrambles are 20 long, equally random, and competition legal. 

# Data Visualizer

Data visualizer is a tool written in python to visualize and graph your session data and show you a trend line, you can also compare multiple sessions at once. Time is graphed in chronological order and is ranked in seconds. You do have to have data in ordrer to make the graph visualization worth using.

# Algorithm Practice

In algorithm practice there are four different sub-options

Oll
-
Navigate through OLL algorithm categories, display the sub-algorithm with its photo, then show you how to get there from a solved state.
Once you've gotten there from a solved state and you continue, this will start a timer. Your times for each oll algorithm will be saved into its respective file, this creates data for all of your solves. If you messed up a solve, you can take it back by hitting "u" to undo.

Pll
-
Pll will navigate through PLL algorithm categories, display the sub-algorithm with its photo, then show you how to get there from a solved state.
Once you've gotten there from a solved state and you continue, this will start a timer. Your times for each oll algorithm will be saved into its respective file, this creates data for all of your solves. Works the same as OLL

Data Editor
-
There will be two options, (e) edit and (d) delete time data. These will open up your specific time files in order for you to make changes to your data and clean it up if need be. (this can also be done from your file system and a text editor as this is just in a txt file)

# Timer

The timer has similar functionality to the algorithm practice section, but is more fine-tuned for tracking your solves accurately and making sure that all details are tracked. You are able to use inspection time, track the starting orientation of the solve, and most importantly edit/change data on the fly according to your wants and needs.
