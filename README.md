# Fun-Features

# Project Details:
In this C++ project using the SFML graphics library, I am creating an application which showcases various different important and fundamental game development topics and concepts I am currently learning in my University game development class. In the class I am learning OpenGL, however, by myself I have been learning SFML due to it being easier to grasp imo. So I am taking the concepts learnt in class and using SFML to express them.

# Build Instructions:
To build the application, go to directory containing the projects source code. Run make in the terminal, you should see a bunch of object files being created and linked into an executable called 'game'. To run, simply type ./game.

# Extra Information:
I hope you enjoy the project, it is rather simple at the momemt but I plan to expand it over time as it goes on. And who knows, as times goes on it may become a full fledged game some day. I also plan to switch to Cmake sometime in the near future as my build tool but for now the makefile works.

# Current Features:
- Player game object that moves according to the mouse
- Enemy game object's that spawn at random points throughout the screen with an attempt to eliminate any spawning overlap.
- Collision detection between Player and Enemy Objects

# Planned Features:
1. Implement Enemy wandering mechanics to follow towards player if within a given distance
2. Implement Window Border collision to prevent leaving game window
3. Implement game music and collision sounds
4. Create proper textures and sprites for background, player, and enemies
5. Implement collectibles for the player to collect
6. Implement powerups of some sort based on the collectibles
7. Create a UI showcasing collected items, health, upgradables.
8. Implement a pause menu with an options menu to change audio settings.
