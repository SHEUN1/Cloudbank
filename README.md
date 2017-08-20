# Cloudbank
Cloud bank is built to be a Computer Vision and AI training platform alternative to its inspiration OpenAI universe where AI agents can be trained to complete task within a video game environment. The Computer Vision part is handled using OpenCV 3 (C++) while it is planned for the Machine Learning part to be handled using Tensorflow (Python) . Gstreamer (https://gstreamer.freedesktop.org/documentation/application-development/introduction/gstreamer.html) will be used to capture the image frame and a bash script will be used to send the keyboard and mouse clicks to the Steam Window currently playing the game. 

Why opencv cplusplus and not python?
The C++ version of OpenCV is much more mature than it's Python counterpart and, in my experience, is often faster in terms of performance. Also, it is planned in the future to implement some GPU parallel processing into the Computer Vision part of the this project which so far can only be done in the C++ version.

How is the video game frame captured
A library named gstreamer was used with the below arguments in a bash script:

gnome-terminal -x gst-launch-1.0 ximagesrc xname=Transistor use-damage=0 ! tee name=t ! queue ! videoconvert ! autovideosink t. ! queue ! videoconvert ! jpegenc ! multifilesink location=/home/sheun/Gaming_Project/game_vision/current_game_frame.jpg 

Below is a screenshot of gstremer in action:

![alt text](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/Screenshot%20from%202017-08-20%2015:36:49.png)


How do you send data across and what?
Data is sent from C++ to Python using a library called Python boost. What is sent is an identified objects location in the image (x,y coordinates), there feature points and the identified characters/words in the frame and their location points. 

[[151, 73], [[56.31380081176758, 48.36287307739258, 4.163553237915039, 327.9974365234375, 0.01612447015941143, 10682624],...]
[[106, 65], []]
[[151, 73], [[56.31380081176758, 48.36287307739258, 4.163553237915039, …]
[[[50, 230], [151, 224], [285, 224], [122, 243], ...], ['r', 'PROCESS', 'TERMINATED', 'Location', 'Data', 'Unavailable', 'f4U,,', 'Next', 'User', ...']]

How do you send keyboard commands to the video game?
A Python script sends commands to a bash script which in turn uses a tool call xdotool to simulate keyboard commands  (http://www.semicomplete.com/projects/xdotool/) and send them to the window containing the name of the Steam Game you currently want to test on. 


Below is a gif of the image processing and object identification being done on the captured frame, the character is currently being moved randomly via simulated keyboard and mouse inputs  being sent to the window 
 ![Output sample](https://github.com/SHEUN1/Cloudbank/blob/master/README_IMAGES/BoundedBox.gif)

How to use it
The ‘game_controller’ directory contains the files needed to control the video game and has been tested on 1 game so far: "Transistor" by supergiant games although in theory can be used for any game in linux by simply modifying the name of the window currently hosting the videogame.
The “game_vision” folder contains the code needed to analyse the game currently being played frame by frame using OpenCV c++.
The IDE’s used were eclipes C++ and pycharm
Set the eclipse workspace to the project folder and build your project (I currently used the watershed technique to process the image and segment objects) 
Go to the /game_vision/gstream_command_to_capture_image file and modyfy the “xname=Transistor” into whatever your Steam game is called.  i.e. xname=<name of window displaying the game>
Go to .../Cloudbank/game_controller/send_control_cmds_to_game file and replace all references to “Transistor” with the name of whatever your Steam game is called. (Modify key commands in the file according to your chosen game)
Go to .../Cloudbank/game_controller/controller.py and once again replace all references to “Transistor” with the name of whatever your chosen window is called  (Modify key commands in the file according to your chosen game)
Start your Steam game. 
Run python scripts this should build the shared opencv shared library. Once built this should activate the gstremer and should start reciveing data from the from the current image frame. 


Problems so far
For this to work no other window on your screen should contain the same name as the video game you are playing otherwise no mouse and keyboard inputs would jump between screens

As expected, the image processing speeds down the framerate considerably due to the fact that the processing is gone on mainly  on the CPU hence the need for GPU parallelisation. 
   
      

