import time
import subprocess
import os, sys
#follow path tp directry that holds the OpenCV shared library
lib_path = os.path.abspath(os.path.join('..', 'game_vision', 'Debug'))
sys.path.append(lib_path)
import time
import random
from random import randint
import numpy as np
import cv2

# execute the make folder so that a shared vision analysis library  and wat for the library to be built first
BuildSharedLibrary = subprocess.Popen(['make', '-j6'], cwd="../game_vision")
BuildSharedLibrary.wait()
#import our OpenCV c++ library
import opencv

# draw a box of a certain colour around an object that will visually indicate what type of object it is.
def drawclassificationBox (img, objectInformation, object_classification, boundboxframePath ):


    xandWidth = objectInformation[1][2] + objectInformation[1][0]
    yandHeight = objectInformation[1][3] + objectInformation[1][1]

    if (object_classification == 'Object we can control'):
        cv2.rectangle(img, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (0, 0, 255),
                      3)
    if (object_classification == 'enemy'):# color red
        cv2.rectangle(img, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (255,0, 0),
                      3)

    elif (object_classification == 'resource'):
        cv2.rectangle(img, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (0, 255, 0),
                      3)

    elif (object_classification == 'unclassified'):
        cv2.rectangle(img, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (128,128,128),
                      3)

    cv2.imwrite(boundboxframePath, img)

    return None

#path to bash file which send the keyboard and mouse clicks to the videoagame
executableControlFile = os.path.join("./", 'send_control_cmds_to_game')

# reward and punishment measure
Reward = 0

#controls
up= ["Up", ""]
down= ["Down", ""]
right= ["Right", ""]
left= ["Left", ""]
Select_attack = ['1', '2', '3', '4']
Press_space= ["space", ""]
R_click= ["R", ""]
#mouse initial coordinates
Mouse_x = 0
Mouse_y = 0
# mouse left click
mouse_clickL = ["ClickMouseL2", ""]
# mouse right click
mouse_clickR = ["ClickMouseR2", ""]
#name of the VideoGame
GameEnvironment ='Transistor'
# frameNumber that will indicate what image frame we are analysing
frameNumber = 0
#we will only record upto a certain number of frames
maxFrameNumberSize = 500
maxNumberOfStatesToRecord = 100
# types of objects
types_of_object = ['enemy', 'resource', 'unclassified', 'Object we can control']

RecordOfStates = []
# Currently part of a test so only random keyboard and mouse clicks sent alond side and mouse posistion
while True:
    GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    while GetGameEnvironmentWindow == GameEnvironment:
        StatesToRecord = 0
        # record how much time it takes to analyse and retrive data from the image farme using our opencv library
        t0 = time.time()
        # open.vision() the function with in the OpenCV C++ part of the code where the image processing takes place
        objectInformation = opencv.vision()
        t1 = time.time()
        words_in_frame =  objectInformation[len(objectInformation)-1][1]

        RecordOfStates[StatesToRecord] = objectInformation
        StatesToRecord+1
        if (StatesToRecord==100):
            {
                StatesToRecord = 0

            }
        if ('RETRY' in words_in_frame):
            {
                Reward-100
                #Theory
                # save the last 100 frames and build a therory about what must hapen that would cause the
                # ai agent to lose points. SAve this theory and compare it to other therorise when you lose a reward
                # we then pick the common traits between the thoeries and use it to strenghten future heories

                BuildTherom(RecordOfStates);
            }
        elif ('PROCESS' in words_in_frame and 'TERMINATED' in words_in_frame ):
            {
                Reward+100
                # Theory
                # save the last 100 frames and build a therory about what must hapen that would cause the
                # ai agent to gain points. SAve this theory and compare it to other therorise when you gain a reward
                # we then pick the common traits between the thoeries and use it to strenghten future heories
                BuildTherom(RecordOfStates);
            }


        #the path to a image of the current frame being analysed on which we can freely draw a visual representation (boundedBox) of our analyses
        imageToDrawBoundedBoxClassification = 'Image%d.jpg' % (frameNumber)
        boundboxframe = os.path.abspath(os.path.join('..', 'game_vision', 'cloudbank_images', 'Frame', imageToDrawBoundedBoxClassification))
        img = cv2.imread(boundboxframe)
        for i in range(0, len(objectInformation)-1):
            #classify each object (currently random)
            object_classification = random.choice(types_of_object)
            #draw a box around the object and save it to a folder
            drawclassificationBox(img, objectInformation[i], object_classification, boundboxframe)
        frameNumber = frameNumber+1
        if (frameNumber == maxFrameNumberSize):
            frameNumber = 0
            
        print 'time taken to retrieve data: ', t1 - t0

        #send control to the game
        sendControl = subprocess.Popen(
             [executableControlFile, "Move", random.choice(up), random.choice(down), random.choice(left), random.choice(right),
              random.choice(Select_attack), random.choice(Press_space), str(randint(0, 1400)), str(randint(0, 1400)),
              random.choice(R_click), random.choice(mouse_clickL), random.choice(mouse_clickR)])

        GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

