# Introduction #

Post notes about the changes you made over here. Thank you.


# Log #

**21-Oct-2007** - _Vaios_

I created a repository so please use it.

**24-Oct-2007** - _Vaios_

I am working on creating an XML configuration file, that will contain all of the constants that we will be using. I'll post more on this later.

Also we need to make sure that everybody is working on something. So I'm going to be working on creating a controller that will try to align the queen with the XZ plane. As far as I know Smiral will be working on the scene, creating bounding volumes for the mountains etc. Ruhi there are two things I can think of for you right now. The camera controller, that makes the camera slide on the bounding volumes of the scene or the AI Framework. I think the camera controller is more urgent so would you like to work on that?

**24-Oct-2007** - _Vaios_

I added the [ConfigurationManager](http://beesiege.googlecode.com/svn/trunk/ConfigurationManager.cpp), which reads a configuration file which contains all of the  constant values that we use here and there. The configuration file is an XML file and its schema is configurationSchema.rng. This schema is written in RELAX NG, which is a type of validation language for XML. If you want to modify the XML file or add stuff to it, make sure you make the appropriate changes to the XML schema and validate it using jing. To run jing type the following: `jing configurationSchema.rng configuration.xml`.

Also I added a UML diagram of the classes we are using. It is an HTML file but it works only in Internet Explorer... (sry not my fault :P). So check that out if you want.

That's it for now.

**25-Oct-2007** - _Vaios_

I changed the camera and character controllers so that the force is calculated correctly. Also I changed the way the camera moves. Now it doesn't rotate on its local z axis, but it only "strafes" on the y axis. This way we avoid the problem where the world is rotated.


**26-Oct-2007** - _Vaios_

I added a lot of things now. First of all the user can now select a number of bees by holding down the left mouse button and when the button is released the selected bees will go to a target. When the left button is pressed a counter is increased and when it is released the queen sorts the soldiers according to their distance from a target, using Merge Sort. Then the desired number goes to the target. Also when a bee is selected its color changes to green.

I also added an enemy (Locust). The user can target an enemy and cycle through targets. Only the targets that are close to the queen can be selected. When an enemy is selected its color changes to red. A bee can go to an enemy if the queen commands it to do so, but the mechanism is not complete yet.

Finally (I think), I added a [TextManager](http://beesiege.googlecode.com/svn/trunk/TextManager.cpp) which is used to display text on screen, and I currently use it to display the number of bees selected.

A major problem is performance. For some reason the game is crawling when we add more than ten PhysX objects and I cannot tell why this is happening. I have a strong feeling though that there is something wrong with PhysX...

**28-Oct-2007** - _Vaios_

So the issue with the performance was actually an issue with the camera, which is now fixed. I also changed the way we select soldiers, so now soldiers are selected one by one. Therefore there is no need for Merge Sort (thx Ruhi). Now I really need the FSM framework.

Also I replaced std::lists with NiTPointerLists. I think it's faster.

**28-Oct-2007** - _Vaios_

I added 3D sound. It's not completely ready yet I'm just making sure the framework works fine. It's not bad...

**30-Oct-2007** - _Smiral_

I am working on the scene... Would be testing in the lab around 5 today ... as the nif viewer on my machine is not working.

**31-Oct-2007** - _Smiral_

I have made a scene with surrounding walls as passive physx boxes. Please check it out.

**1-Nov-2007** - _Vaios_

The current status of the game is this: The soldiers follow the queen using a Behavior Combo that consists of Arrival, Separation, Wander and Departure. They also look at where the queen is looking IF the queen is their current target. The user can select a number of bees by holding down the left mouse button, and send the bees to a target when the left button is released. This has to change, because changing the target is not enough. We have to use the FSM's here to make the bees go into attack mode. We'll see how we're gonna do that.

There is 3d sound support but the system is currently inactive. We should play around with sound after all the major parts are implemented. The user can also go into look-around mode, which is currently not working as it should so I'll take care of that. The scene Smiral sent me, the one with the PhysX boundaries is now the scene that we load. The walls work, although they should be placed better so that no object gets inside a mountain.

I just added fog. Fog is present all the time and it is needed because otherwise we need to set the far clipping plane of the camera far away, which is very inefficient. Fog hides that. Also it is essential from a gameplay perspective. Now if the queen goes higher than a certain point, fog increases very much in a smooth way so that the user cannot see almost nothing. This is to prevent the user from going higher than we want him to. Adding fog is very easy and we can work on that to make it look better later.

A last thing I want to say has to do with comments in the code. I started writing comments in a Javadoc way. This is a special format of comments that various tools can use to create HTML documentation of very high quality. All of my code uses Javadoc comments and I created HTML documentation using Doxygen. You can check it out by opening index.html in the help/html folder of the game. I suggest that you write comments for your functions this way, so that everything is consistent. If you don't want to it's fine, I just think it's prettier. To learn how to write Javadoc comments just look at my code and you should have no problem. The only basic thing you have to do is write your comment like this `/** comment */`. Note that Javadoc comments are only for explaining what a function does. Not for explaining lines of code inside the function.

So things to be done:
  * Finish the scene
  * Start using the FSM's in a meaningful way. We should meet to do that
  * Fix the look-around mode
  * Start creating some gameplay elements

We should meet one of these days. Let me know when... Cheers!

**1-Nov-2007** - _Ruhi_

Wow, I can't wait to see the fog! I made the FSM code changes that we discussed this morning. I can meet tomorrow evening after 4:00pm. Saturday morning also works for me. I won't be available on Sunday and Monday.

**1-Nov-2007** - _Vaios_

I fixed the look-around mode, so that the camera now moves to the head of the queen. Now I would rather meet u guys Saturday morning, does that work for you guys?

**1-Nov-2007** - _Smiral_

Saturday morning works fine with me. I will try and finish the scene by then (hoping that Maya doesn't crash on me big time). The fog sounds exciting... Wanna see that soon.

**3-Nov-2007** - _Ruhi_

I've added code to all the state files with the basic logic of transitions from one state to other states. Going from here, I will stitch the FSMMachine with the states so that we can just add a machine to every game character and they should behave according to their respective FSM.

Also, as I see it, many of the current behaviors of the characters will be called through the update function in the state files. But we can should try not to make drastic changes to the working code because that may be too much effort.

I have yet to complete a lot of this, so please have patience :)

We would need new GameCharacter to represent PowerUps.

**4-Nov-2007** - _Smiral_

Guys, am still working on the model.... Its taking quite a long time... I am like 40% done and am planning to be done in a day.

**6-Nov-2007** - _Ruhi_

I modified all the FSMState files to complete the CheckTransitions methods which means that the algo for changing from one state to another now makes sense. How we want the characters to behave in each state will require some more work in both the FSM and the existing Game code.

I have defined the UpdatePerceptions method in AIControl files. Vaios, if you check my comments in these methods, you will know exactly what new getter methods I need in the Bee, Queen and Locust files. They should be small to implement. If you finish those, you can just uncomment my lines of code in my files or let me know and I'll do it.

Once that is done, we will have to sit together to see how and where in the code do we attach the FSMMachines to the characters. I hope it won't be too hard!

Oh, since it's too painful to review code, I wouldn't expect you guys to do that but there may be some errors that I've overlooked and we may have to resolve those during integration.

-Ruhi

**7-Nov-2007** - _Smiral_

Hi,
Finally I have completed the model covered with Physx objects ... Phew...
My final count of number of models I saved in this process is somewhere around 55.

Anyways, its done now... Guys I am mailing out the nif file. Vaios please check it out if the scene works fine.... and if there are any noticeable inaccuracies in making the models. Also the height of physx objects for every mountain is higher than it seems.

We might need to export this scene again from Vaios's comp as my nif exporter does not export the textures. But that can be worked out later.

- Smiral

**11-Nov-2007** - _Vaios_

I made huge changes to the code in order to achieve the following:
  * Game characters should not know what is happenning in the game. They should not be aware of what type of controllers they have or if the user is controlling them.
  * We should code everything keeping in mind that maybe there are a lot of queens in the game and not only one. I pretty much achieved this but it's not there yet. I will not work more on this because of lack of time. However now it should be fairly easy to implement this if we want to.
  * The characters should be component-based. If they have a controller then they can move in the scene. If they have a sound component then that can produce sounds etc. This is the design I'm following from now on. This is implemented through the CharacterAttribute class. A controller is an attribute. A sound is an attribute and so on. A game character has a list of attributes which can be used to add functionality to them.

This means that for example Health is an attribute. Some characters might have health some might not. This could be anything, it could be armor for example or special powers. The only thing we need to do is create something that inherits from CharacterAttribute and add it to the Characters attribute list. The attributes will have an update function so the only thing we have to do to make the attributes work would be to call their update functions. I'm not totally sure about this design approach yet, but I'm definitely using attributes. I'll post the code once I'm sure about the changes.

Cheers.


**20-Nov-2007** - _Ruhi_

Here is what we have discussed about the gameplay so far. I think we should not deviate too much now and just pick what should be done from here.

### Character modifications ###

**Types of Bees:**
  1. Healers - these bees will heal the wounded bees if they are close enough
  1. Honey bees - they collect nectar from the flowers
  1. Soldier bees 1 - they attack the enemy
  1. Soldier bees 2 - they are bigger and stronger soldier bees

**Types of Enemies:**
  1. Locust - short-sighted, they attack the closest target
  1. Dragonfly - they are on the lookout for the Queen bee
  1. Other enemies - maybe they eat up the honey, so they should be killed

### Queen Functions ###
  1. The queen has to be close to the target in order to launch an attack
  1. The strength of the soldier bees is inversely proportional to their distance from the queen -
> smaller distance = higher confidence = less health lost = more damage done

> very large distance  = low confidence = lose health quickly = less damage done

### Attack mechanism: ###
  1. Right-click - Select the soldier bees
  1. Right-release - Attack the target with separation (default behavior)
  1. Left-click - If target selected, add cohesion to attacking group

### New State: ###
**Auto-attack** - If an enemy is too close, the soldier bees close to the queen that are not    already engaged in another attack will start attacking this enemy.

### Resource control: ###
  1. Flower beds - honey bees collect nectar here. More the nectar created, higher the capacity to spawn new bees
  1. Queue new bees which are created when there is enough honey
  1. Enemy bases - Each housing an enemy boss. Kill the boss = destroy the base. Each base spawns enemies depending on the health of the respective boss.

Now, who will explain this to Lane :D?

### Extra functions: ###
  1. Autosave / Autoload when the queen dies
  1. Sound
  1. User Interface
  1. Score system ?


**29-Nov-2007** - _Vaios_

I modified the attack mechanism so that the user selects bees by holding the right mouse button and attacks by releasing it. Also when the attack starts the group is separated, but when the left mouse button is down it has cohesion. This works as expected so that's good. I will start working on the enemy bases now.

Added simple enemy bases. Also fixed the problem with the HUGE NiMemory-Overview.xml file. After endless hours of hacking I managed to found a way to choose whether this file is going to be generated or not, by a simple #define statement. So make sure you include NiAppMain.cpp in your project and if you want to see if you have memory leaks simply uncomment the line that says #define LOG\_MEMORY\_TRACKING. If you don't want those xml files to be generated then comment the line again. I noticed that the game runs MUCH smoother without these files being written in the background...

**30-Nov-2007** - _Vaios_

Added armor that makes health reduce slower when its bigger. Armor is bigger when queen is close, but when the queen is far the armor is negative which makes health actually reduce over time. I also added a billboard that shows health and it is displayed on top of every game character. Green means full health, red means no health. It's there for debugging purposes however this might give you an idea of how we could do health bars...

**2-Dec-2007** - _Vaios_

Added StateLocustAttack and modified other things all over. Also added some more data in the configuration file. Now the Locusts can attack their closest opponents and inflict damage on them. Also the bees can now die. Well now there is actually a fight going on in the game and it is actually kinda fun :)

**4-Dec-2007** - _Vaios_

Added sound. Since I could not find any appropriate sounds for the things that are going on in the game I recorded the sounds myself and changed the pitch to make them sound cartoonish! Lol!!! I even made the bzzzzzz sounds... It was really funny... Sound is enabled by default. To disable it comment the line: #define ENABLE\_SOUND in ResourceManager.cpp . Have fun...

**8-Dec-2007** - _Smiral_

Added Flowers to the scene. Just go a bit ahead with the bee and u will see the first bunck of flowers. Also the bee was able to go thru the base of the environment so fixed that too..

btw Vaios the bzzz sounds .... it doesn't seem tat its recorded by u ... did u tweak them after recording .. .they r just amazing....

**9-Dec-2007** - _Vaios_

Integrated UI and flowers and fixed most of the UI bugs. I also added a TargetClosestFlowers function, which makes the queen automatically target the closest flower bed, every 5 frames. I thought that maybe it is too complicated for the user to select flower beds too, so now it happens automatically. I also changed the keys a little bit, so '2' spawns bees and Space targets enemies.

Yes Smiral I processed the sounds a little bit, basically I simple increased their pitch. Aren't I an amazing sound actor??? :P

**10-Dec-2007** - _Vaios_

I fixed CreateUISystem so now you don't have to place your project inside the Samples folder.

Also added healer bees (HealerBee) and FSMHealerAIControl. You can create healers by pressing '3'. The healers just follow the queen and heal nearby allies for 10 seconds. After the 10 seconds the die. I use the bee model for the healers so we might need to change that.

**11-Dec-2007** - _Vaios_

Added honey bees and their states (FSMHoneyBeeAIControl, StateHoneyBeeGather). I also implemented e mechanism for sending honey bees to flowers to collect honey. First to spawn honey bees you press '1'. To collect honey you first have to go close to a flower. The flower will be targeted automatically if you re close enough. When the flower is highlighted you hold Shift + right click, to select honey bees. If you release the right click while Shift is down or if you simply release Shift, the honey bees will go to the flower and collect honey. Once they are done they will return to the queen and go back to a follow state. When they reach the queen they will give her the honey they collected.

I didn't have enough time to fully test the system for bugs, but it seems to be working fine. So again we need a model for the honey bees. Also we need one or a few models for the bosses. One will work I guess.

The remaining systems that we have to implement are:
  1. Bosses
  1. Position the bases **IN PROGRESS**
  1. Fix the spawn enemy function so that it spawns enemies at a good rate
  1. Queuing bees     - **DONE**
  1. Add a win state (!)
  1. Dragonflies      - **DONE**

If i forget something please add it to the list above.

**11-Dec-2007** - _Ruhi_

We also need to add a scoring mechanism? Or do we?


1) I have moved the UI code to new UIManager files

2) The bees can now be spawned using the UI buttons

3) I've started working on the queuing mechanism. This will change the instantaneous
spawing that we have right now. How and when do we take the elements out of the queue? Time based?

I need to use the function which refreshes the render every frame in order to show the pictures of the queued bees correctly. which is this function exactly inside GameApp?

4) I tried working with NiUIImage and NiUIImageButton classes to avoid using separate polygons for images but the above UI elements do not take any random pictures, only some Gamebryo fixed UI textures using a standard enum...very disappointing.

Finally, I will work on the honey bee and boss models one of these days. So you can use any dummy right now. We'll have something by Friday.

Yes, the honey collection by the bees is working fine and looks good. However, i see here that the healer bee models disappear after a fixed amount of time. What happens?

**12-Dec-2007** - _Vaios_

Added dragonflies and their states. Dragonflies attack the queen only when she is in proximity.

**12-Dec-2007** - _Smiral_

Changed the model for locust... to be in the direction of X-Axis and increased the size.
Working on the code for getting the enemybases in place.. but it has some error. Will continue doing that in the night.

**12-Dec-2007** - Ruhi

The queuing mechanism is in place!! So now you can queue your bees in any order and their little pictures will show up in the box to the left :). As the bee at the head of the queue completes its wait time, the picture will disappear and the bee will pop onto the screen.

I have randomly chosen 5 seconds creation time for honey and soldier bees and 10 seconds for the healer bee. You can easily change this in the UIManager.cpp file. There are two limits on the creation of bees - maximum length of queue and minimum resource level. I have checked for the queue length but haven't tied it to the resource. Again this is very easy. Just add a clause to the if statement where i check for queue length in UIManager.

if((gameMgr->GetGameApp()->beeTypesQueue.GetSize() < maxQueueSize) and (blah blah...))