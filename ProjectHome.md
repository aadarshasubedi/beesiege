The game idea is this. Life was good for the bees and their queen. They lived in their hive making honey and having fun. Until one day a spoiled little teenager threw his cigarette underneath the hive which caught on fire. Now the bees are left with no home and they have to travel through the forest to find a new place to live. But they are going to face a lot of challenges on their way…

The player controls the queen bee and her soldiers are following her at all times. Throughout the forest there are going to be a lot of enemies that will make the player’s life difficult. The queen is not able to attack, because that’s not her purpose in life, so she depends on her soldiers to protect her. Whenever an enemy is nearby the queen (player) will be able to select a number of bees and command them to destroy that enemy. The bees that survive the challenge will return to the queen. Of course many of them will die so a number of power ups is going to be distributed around the forest. When the queen makes it to the new hive the level ends. If the queen dies then it is game over.

Now just to give you an idea of how the game is going to look like, think of Wing Commander. Only replace the spaceship with the queen and the missiles with bees. Of course bees will not be shot at the enemy, they are going to move there at their own speed and attack him.

I am very excited about this project because it features various new stuff. First of all I do not know of any game that has a similar story / goal. Also I do not know of any game that uses this attack mechanism. Also the game features a very interesting animation mechanism. We use Behavioral Animation to move the bees around, which means that every bee or game character has a controller that generates forces and torques which drive the character. These forces and torques vary depening on the behavior that we are implementing. Behaviors include

  * Seek: the object travels to a target at maximun speed
  * Arrival: the object travels to the target while slowing down until it reaches it
  * Wander: the object moves in random directions within a radius
  * Separation: the object is keeping a distance from its surrounding objects
  * Allignment: the object follows the general direction of its neighbors

The nice thing about these individual behaviors is that you can combine them and get more complex behaviors like Flocking where the objects form groups and also have a randomness to their movement like actual bird flocks. Behavioral Animation is not a new idea however what is original in our implementations is that these forces and torques that the controllers generate are given to Ageia’s PhysX which then takes care of the simulation and moves the objects. The effect of all that is very realistic movement.. You actually think that these are actual bees you see on the screen.

Another cool thing in my opinion will be the simplicity of the game. The player only controls the queen and everything else is AI. Of course it is more than that, the player will have to make decisions that will affect his chances of survival, but still the gameplay is very simple and fun.