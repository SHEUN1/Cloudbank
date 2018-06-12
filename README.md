# Cloudbank
Cloudbank is built to be a Computer Vision and AI training platform alternative to its inspiration "OpenAI Universe" where AI agents can be trained to complete task within a video game environment on Steam (http://store.steampowered.com/). The Computer Vision part is handled using OpenCV 3 (C++) while it is planned for the Machine Learning part to be handled using Tensorflow (Python). Gstreamer (https://gstreamer.freedesktop.org/documentation/application-development/introduction/gstreamer.html) will be used to capture the image frame and a bash script will be used to send simulated keyboard and mouse clicks to the Steam window currently playing the game.

### What you'll need.
1. Linux OS (at least ubuntu 14.04)
2. Gstreamer 1.0
3. OpenCV version 3.4.1 (recommended to build with opencl enabled)
4. c++ 11
5. python 2.7
6. Steam video game client 
7. xdotool
9. a GPU 

### Why opencv C++ and not Python for vision processing ?
The C++ version of OpenCV is much more mature than it's Python counterpart and, in my experience, is often faster in terms of performance and enables you to implement some GPU parallel processing into the Computer Vision part of the this project.

### How is the video game frame captured?
A library named gstreamer was used with the below arguments in a bash script:

gnome-terminal -x gst-launch-1.0 ximagesrc xname=Transistor use-damage=0 ! tee name=t ! queue ! videoconvert ! autovideosink t. ! queue ! videoconvert ! jpegenc ! multifilesink location=/home/sheun/Cloudbank/game_vision/current_game_frame.jpg 

This captures the current frame of the game and saves it as 'current_game_frame.jpg' 

Below is a screenshot of gstremer in action:

![alt text](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/Screenshot%20from%202017-08-20%2015:36:49.png)

### How do you send data across and what?
Data is sent from C++ to Python using a library called 'Boost.Python'(http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/index.html). What is sent is an identified objects location in the image (x,y coordinates), its feature points and the identified characters/words in the frame and their location points.

![alt text](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/Screenshot%20from%202017-08-20%2017:27:25.png)

[[151, 73],[26, 30, 947, 553], [[56.31380081176758, 48.36287307739258, 4.163553237915039, 327.9974365234375, 0.01612447015941143, 10682624],...]]

#### Meaning of data
([151, 73] - represents object coordinates. [26, 30, 947, 553] -boundedbox points of object .[56.31380081176758, 48.36287307739258, 4.163553237915039, 327.9974365234375, 0.01612447015941143, 10682624],...] - represents a list of keypoint feature vectors of object 

.
.
.

[[[50, 230], [151, 224], [285, 224], [122, 243], ...], ['r', 'PROCESS', 'TERMINATED', 'Location', 'Data', 'Unavailable', 'f4U,,', 'Next', 'User', ...']]
#### Meaning of data
([[50, 230], [151, 224], [285, 224], [122, 243], ...] - represents list of x and y coordinates of identified words/chracters. ['r', 'PROCESS', 'TERMINATED', 'Location', 'Data', 'Unavailable', 'f4U,,', 'Next', 'User', ...'] - list of identified chracters/words/numbers on the current frame)

### How do you send keyboard commands to the video game?
A Python script sends commands to a bash script which in turn uses a tool call xdotool to simulate keyboard commands  (http://www.semicomplete.com/projects/xdotool/) and send them to the window containing the name of the Steam game you currently want to test on. 


Below is a gif of the image processing and object identification being done on the captured frame, the character is currently being moved randomly via simulated keyboard and mouse inputs being sent to the window from the controller
[![IMAGE ALT TEXT HERE](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/projectCloudbank.png)](https://www.youtube.com/watch?v=hRo3HSo-eYM "IMAGE ALT TEXT HERE")
 ![Output sample](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/BoundedBox.gif)

###instructions
1. make sure that you have the following installed
	*'xdatool'
	*'gstreamer 1.0' 
	* Steam video game client
	* A videogame that can be played on an ubuntu environment (Default game for this repo is the videogame: transistor)
2. Download the repo unto your system and unzip it into your chosen directory
3. Go into the downloaded repo and  into follow the path ".../game_vision/gstream_command_to_capture_image" file and modyfy the “xname=Transistor” into the tile of your video game that appears in the game window title for example: xname=<name of window displaying the game> and modify the line "location=/home/sheun/Cloudbank/game_vision/current_game_frame.jpg" absolute path to one that reflects your system.
4. Go to ".../Cloudbank/game_controller/send_control_cmds_to_game" file and replace all references to “Transistor” with the name of whatever your video game is called. (Modify key commands in the file according to your chosen game) 
5. Go to ".../Cloudbank/game_controller/controller_random.py" and once again replace all references to “Transistor” with the name of whatever your chosen window is called  (Modify key commands in the file according to your chosen game)
6. Start your Steam game. 
7. Run the python script which will build and run the platform. Once built this should activate gstremer and should start reciveing data and sending keyboard inputs into the game. 


### source file location for image processing and sending keyboard strokes to the videogame ?
1. The “game_vision” folder contains the code needed to analyse the game currently being played, frame-by-frame, using OpenCV C++. The ‘game_controller’ directory contains the files needed to control the video game
2. The OpenCv source files are located in the "Cloudbank/game_vision/src/" directory and the python controller file is lacated in the "Cloudbank/game_controller/"directory. 


### Keep in mind 
1. For this to work no other window on your screen should contain the same name as the video game you are playing otherwise the mouse and keyboard inputs would jump between screens. 

2. To avoid problems with gstreamer please set your game screen resolution to no more than 1024x768

### Curious about development environment?
4. The IDE’s used during development were 'Eclipes C++' and 'Pycharm' community edition. You can use Eclipes by simply setting the Eclipse workspace to the project folder.
      

