CRR Final Project
Bailey Manzer
03/16/21

Significant Changes:

  - Most of the changes I made throughout the code base were fairly simple. When I 
    started working on the project the code base for FRUPAL lacked consistent formatting
    and styling, likely due to the fact that there were originally 5 people working on 
    the project with no style guide. I was able to go through the code fix the variances
    in the formatting. One of the changes I made, for example, was the placement of open    
    curly braces. In some parts of the code the open curly braces were on a new line
    after a function name, and in some parts they were on the same line. I elected to
    put all of the opening curly braces on the same line as the function name in order
    to reduce the over all length of the files. In my opinion, the change did not 
    sacrifice readability. 
  - Another change that I made was to eliminate pieces of code that were unused. For 
    example, after I had edited the Map.h and Map.cpp files I went to work on the 
    World.h and World.cpp files and noticed that there were many similarities. After 
    checking the dependencies of all of the files in the program I realized that the Map 
    files were not even being used. Throughout the code base I was also able to 
    eliminate functions that were unfinished/unused. 


Problems I recognized, but didn't have the time to fix:

File: split.cpp
  - drawTerrain function is very very long. Could be broken up into multiple smaller
    functions. There are 2 long switch statements that are very long. Furthermore, the
    switch statements compare inteeger values when discussing items and terrain types.
    These types should probably be encapsulated in their own enums/class. One switch 
    statement could be eliminated by making a printTerrain function in the grovnik 
    class.
  - There are many integer values throughout the file that dictate where certain
    information should be printed throughout the program. This issue could be fixed by 
    creating constants that store certain screen positions. This would increase 
    readability because everytime a print statement is read in the code we could know 
    exactly where it will end up in the window. 

File: object.h
  - member variables of the Grovnik class should be made private, but were left public 
    for ease of implementation.
File: main.cpp
  - Move player function too long and takes too many arguments. Should have a player 
    class that encapsulates all of the arguments.
  - There is a switch statement on terrain type again in this file. Again, instead of 
    comparing int values there should be a dedicated terrain type.
  - There is a TODO for a section of code that is incomplete. This should be finished. 



Overall, this project (and class) taught me the importance of code styling, clarity,
and readability. There were so many pieced of the frupal code base that needed to be 
updated. None of the code had consistent formatting and there were a large number of 
useless comments that detracted from the meaning of the code. The original project 
would have definitely benefited from a consistent style guide. A large portion of the
project should be completely redesigned. If I had more time I would restructure all of
the code pertaining to the terrain type. This issue alone created an unwieldly number
of nearly identicle switch statements. I would also work on reducing the size of all of
the functions throughout the code base. Some functions were over 100 lines and could definitely be rewritten as multiple functions. Doing so would also ensure that each 
function is doing strictly one thing at one level of abstraction. 

I didn't get nearly as much done as I wanted to on this project. My time management
this term hasn't been great. This is what I could do with the time I alloted.
