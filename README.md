quark-plasma
============
A space game made with the Irrlicht Engine


#Tools used
We used the Irrlicht library to make this game (http://irrlicht.sourceforge.net/)  
QtCreator for dev on Linux  
Visual Studio 2012 for dev on Windnows

#Credits
Images and textures used are the ones the NASA provides except for the early stages of the dev, where we used random google images for test purposes.


#Build instructions
###Linux
You just have to get the CMake software, irrlicht dev libraries and gcc to compile the game.  
On most linux versions, you can get this by using the package manager like this: (on debian libbullet-dev is only available version >= jessie)
> apt-get install libirrlicht-dev gcc cmake libbullet-dev

Now go in the project directory with your terminal and create the folder where you will compile the game:  
> mkdir build  
> cd build  
> cmake ../.  
> make

Now launch the fresh binary and you can play quark-plasma !  

###Windows
Everything has been prepared for you, so you just have to instal Visual Studio 2012 (Express is ok)  
1. Open the .sln file  
2. Click on launch (or press F5) to play the game !  
Once you did that you can just go on the bin folder and launch the .exe file.
