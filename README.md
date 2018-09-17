# Cloudbank
Cloudbank is built to be a Computer Vision and AI training platform alternative to its inspiration "OpenAI Universe" where AI agents can be trained to complete task within a video game environment that can run on a linux PC. The Computer Vision component is handled using OpenCV (C++) while it is planned for the Machine Learning component to be handled using Python. Gstreamer (https://gstreamer.freedesktop.org/documentation/application-development/introduction/gstreamer.html) is used to capture the video game frame and a bash script is used to send simulated keyboard and mouse inputs to the video the game.

### What you'll need.
1. Linux OS (at least ubuntu 14.04)
2. Gstreamer 1.0
3. OpenCV version 3.4.1 (build with tesseract OCR enabled)
4. c++ 11 or greater compiler (Enable Boost library)
5. python 2.7
6. Steam video game client
7. PlayOnLinux with steam client installed (this is used to run Windows only video games on Linux) 
7. xdotool

### Why opencv C++ and not Python for vision processing ?
The C++ version of OpenCV is much more mature than it's Python counterpart and the languge is faster in terms of performance and enables you to implement some GPU parallel and multithreading processing into the project.

### How is the video game frame captured?
A library named gstreamer is used with the commands contained within a bash script. gstreamer captures the current frame of the game and saves it as 'current_game_frame.jpg' 

Below is a screenshot of gstremer in action:

![alt text](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/Screenshot%20from%202017-08-20%2015:36:49.png)

### How and what data is sent across into python?
Data is sent from C++ to Python using a library called 'Boost.Python'(http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/index.html). What is sent is an identified objects location in the image (x,y coordinates), its feature points and the identified characters/words in the frame and their location points.

![alt text](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/Screenshot%20from%202017-08-20%2017:27:25.png)

#### For the identified regions of interest the data is in the form of:
[[x coordinate, y coordinate],[BoundBox width, BoundBox height, BoundBox top left hand coorner x coordinate , BoundBox top left hand coorner y coordinate], [feature Points]]
.
.
.
#### For the identified text in the game the data is in the form of:
[[<indentified text 1>,x coordinate, y coordinate],[<indentified text 2>,x coordinate, y coordinate],... ]


### How do you send keyboard commands to the video game?
A Python script sends commands to a bash script which in turn uses a tool call xdotool to simulate keyboard commands  (http://www.semicomplete.com/projects/xdotool/) and send them to the window containing the title of the video game. 

Below is a gif of the image processing and object identification being done on the captured frame, the character is currently being moved randomly via simulated keyboard and mouse inputs being sent to the window from the controller
[![IMAGE ALT TEXT HERE](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/projectCloudbankMirrorsEdge.png)](https://www.youtube.com/watch?v=NiK4M-DMZ9U "IMAGE ALT TEXT HERE")
 ![Output sample](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/BoundedBox.gif)

### Instructions
1. Download and extract the repo 
2. Navigate into the downloaded repo and  into follow the path ".../game_vision/gstream_command_to_capture_image" file and modyfy the variable "xname" and assign it to the title of the window currently hosting the video game “xname=<title of window hosting the video game>”  
3. Modify the line "location=/home/sheun/Cloudbank/game_vision/current_game_frame.jpg" absolute path to one that reflects your system.
4. Navigate into the".../Cloudbank/game_controller/send_control_cmds_to_game" file and modyfy the variable "ID" and assign it to the title of the window currently hosting the video game “ID=<title of window 	hosting the video game>”. Within this file modify the xdotool key commands to replicate the control inputs of your game. 
5. Navigate into the ".../Cloudbank/game_controller/controller_random.py" and and modyfy the variable "game_window_title" and assign it to the title of the window currently hosting the video game “game_window_title=<title of window hosting the video game>”. Within this file modify the xdotool key commands to replicate the control inputs of your game. 
6. Start your video game. 
7. Run the python script which will build and run the program. Once built this should activate gstreamer and should start reciveing data and sending keyboard inputs into the game. 


### Source file location for image processing and sending keyboard strokes to the videogame
1. The “game_vision” folder contains the code needed to analyse the game currently being played, frame-by-frame, using OpenCV C++. The ‘game_controller’ directory contains the files needed to control the video game
2. The C++ source files are located in the "Cloudbank/game_vision/src/" directory and the Python file is lacated in the "Cloudbank/game_controller/"directory. 


### Keep in mind 
1. For this to work no other window on your screen should contain the same name as the video game you are playing otherwise the mouse and keyboard inputs would jump between screens. 

2. To avoid problems with gstreamer please set your game screen resolution to no more than 1024x768
      
3. The current setup for Cloudbank is set the run with the video game "Mirrors Edge" running on PlayOnLinux
