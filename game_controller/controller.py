import subprocess
import os
import time
import random
from random import randint
import main

#main.vision()
keypoints = main.vision()
print keypoints [3]
executable = os.path.join("/home/sheun/Gaming_Project/game_controller", 'send_control_cmds_to_game')
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
b ='Transistor'

while True:
    a = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    while a == b:
        p = subprocess.Popen(
             [executable, "Move", random.choice(up), random.choice(down), random.choice(left), random.choice(right),
              random.choice(Select_attack), random.choice(Press_space), str(randint(0, 1400)), str(randint(0, 1400)),
              random.choice(R_click), random.choice(mouse_clickL), random.choice(mouse_clickR)])
        time.sleep(1)
        a = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

