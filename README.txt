----------------------
BASIC INFORMATION
----------------------
TowerDefence_v0.8
Tower Defence game, Terrain Analysis, Influence Maps, Adaptive Genetic Algorithm

This game is part of my MSc project, i release it openly to help people who are 
searching for examples such as influence maps, genetic algorithms and cocos2dx engine.
Programming wise, it has an okey object oriented structure but the memory handling 
is not that good as it was rushed. I have made this game in 2 weeks and then i have spent
1,5 months implementing the AI and debugging. The ASTAR algorithm is based 
on https://github.com/chenquanjun/Cocos2dx-AStarUsingTileMap/tree/master/proj.ios_mac
The GA and influence maps have been designed and implemented by me from scratch. In 
this directory you will also find some screenshots of my report with some UML diagrams,
if you need any help, feel free to contact me! 

-----------------------
USAGE & GUIDE
-----------------------
*ESCAPE BUTTON : Menu.
*Click once ON + and then click on sand to place tower.
*Left click to drag the camera.
*Move camera W A S D.
-----------------------
KNOWN BUGS & NOTES
-----------------------
NOTES:
*OPEN TYPE NOT OPTIMISED.
BUGS:
*GA (PROFILE 3), occasionally crashes when a player wins or loses and the game is on simulation mode.
-----------------------
TODO
-----------------------
*PORT TO WINDOWS.
*MORE FRIENDLY GUI.
*GUI classes clearing
*Properly release memory at parts (do make sure you release all pointers from the GA class, and delete any 
memory held by pointers on each class' destructor. )
