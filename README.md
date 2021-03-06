#Deskworld
2D physics simulator built for multi-touch tables, project created as partial demand for bachelor degree in Computer Science at "Universidade de Brasília (UnB)".

* Note about simulating the environment:

This game was developed as part of our thesis for Bachelor in Computer Science. It is not, however, the whole thesis. The thesis consisted of building a hardware from scratch, a table with a multi touch surface, and developing a game that would showcase its capabilities in a fun and innovative way.
It is possible to use the mouse as your touch device, but in order to really test it, you will need to run the simulator included (which we got from the internet, not done by us).
Simply double click the "TuioSimulator.jar" file to open it before running the game, and use it as input by clicking on it and dragging after the game is open. hold Shift key before clicking to make a click and hold, so you can somewhat test the multi touch capabilities (although it would only really show what it could do in a multi touch table, being operated by a large group of people simultaneously).

* About running the game:

Simply run the "Deskworld.exe" file located in the "Deskworld Source" folder. Or, import the project on eclipse for C++, and run it from there.

* How to play the game:

The game tries to simplify UI so it would be visible no matter where one would be around the table playing it. It uses mostly gestures to communicate.
- Controls: Double click on any free space to open the menu. Touch an option to select it. (the controls do not work on drag, just on direct touch). Following are the menu options explained:
-- Dynamic/Static: Mutually exclusive options. On dynamic, object will acquire the default physics value and behave accordingly. On static, objects remain still and are fixed on their position.
-- Freeform: Touch on the screen with one finger and drag it to draw the currently selected shape. The form is made as you are dragging the finger around.
-- Circle, Triangle and Rectangle: Touch on the screen with one finger and drag it to draw the currently selected shape. The place touched will be the center of the shape, and the object will expand and contract size as you move your finger across the screen.
-- Mute: One click stops the music, another plays it again.
-- Divide World: Allows the world to be divided in 2 smaller sub worlds. Each world can have different options for drawing different things simultaneously, and also each world has their own gravity.
-- Eraser: Deletes the form touched. When deleting dividers, will allow objects to pass, but the worlds will remain different, meaning the world division rules still apply, but without a barrier.
-- Gravity: Changes the gravity. Touch on the area you want to change gravity and swipe your finger in the direction you want gravity to go. The farther you swipe, the stronger the gravity will be.
-- RGBA Sliders: Change the object color and transparency. Cannot be slided, must touch on the value desired.

- Double click on any object to open the object menu. This menu was going to have options to change RGBA of the object after creation, as well as editing the physical properties of each object, but given how the objects were being constructed, how the game was performing on the built hardware, and lack of time, this menu does not work.

- Touch an object to hold it. You can touch it with multiple finger in order to hold it more precisely or rotate it. By touching it with a finger and pulling it with another, you can even slingshot your objects, to give it a little momentum.

* About which parts each one did of the game:

Being it our Bachelor's thesis, we both wanted to enjoy it to the fullest, as a really great work experience. As such, we managed to divide work in a way that both of us would mess around with every part of the program, in a manner that would be kind of difficult to divide what each has done. The only part where we did really see a clear division was nearing our project deadline, where I, Danilo, worked mostly trying to fix the menu and inner parts of the game, while my partner, Victor, tried to correct the behaviour of the geometric shapes.
