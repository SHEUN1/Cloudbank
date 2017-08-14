import subprocess
import os
import time
import random
from random import randint


# execute the make folder so that a shared vision analysis library  and wat for the library to be built first
#cleanSharedLibrary = subprocess.Popen(['make' 'clean'], cwd="../game_vision")
#cleanSharedLibrary.wait()
BuildSharedLibrary = subprocess.Popen(['make', '-j4'], cwd="../game_vision")
BuildSharedLibrary.wait()
import main
#main.vision() #the funtion with in the OpenCV C++ part of the code where the image processing takes place
keypoints = main.vision()
print keypoints [0]
#print keypoints [16]
#print len(keypoints)
#for i in range(0, len(keypoints)):
#    print keypoints[0] == keypoints[i]

#path to bash file which send the keyboard and mouse clicks to the videoagame
executableControlFile = os.path.join("./", 'send_control_cmds_to_game')
#controls
up= ["Up", ""]
down= ["Down", ""]
right= ["Right", ""]
left= ["Left", ""]
Select_attack = ['1', '2', '3', '4']
Press_space= ["space", ""]
R_click= ["R", ""]
Mouse_x = 0
Mouse_y = 0
mouse_clickL = ["ClickMouseL2", ""]
mouse_clickR = ["ClickMouseR2", ""]
#name of the VideoGame
GameEnvironment ='Transistor'
# Currently part of a test but send out random keyboard and mouse click and posistions clicks
while True:
    GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    while GetGameEnvironmentWindow == GameEnvironment:
        sendControl = subprocess.Popen(
             [executableControlFile, "Move", random.choice(up), random.choice(down), random.choice(left), random.choice(right),
              random.choice(Select_attack), random.choice(Press_space), str(randint(0, 1400)), str(randint(0, 1400)),
              random.choice(R_click), random.choice(mouse_clickL), random.choice(mouse_clickR)])
        time.sleep(1)
        GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

