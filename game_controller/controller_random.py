import os
import sys

#follow path tp directry that holds the OpenCV shared library
lib_path = os.path.abspath(os.path.join('..', 'game_vision', 'Debug'))

sys.path.append(lib_path)
import random
import subprocess

run_capture = subprocess.Popen(["../game_vision/gstream_command_to_capture_image", "&"])
# execute the make folder so that a shared vision analysis library  and wat for the library to be built first
BuildSharedLibrary = subprocess.call(['make', '-j4'], cwd="../game_vision")
import opencv

#path to bash file which send the keyboard and mouse clicks to the videoagame
executableControlFile = os.path.join("./", 'send_control_cmds_to_game')

#controls
activate_controller = ["start", "stop"]
up= ["w", ""]
down= ["s", ""]
right= ["d", ""]
left = ["a", ""]
downAction = ["Shift_L", ""]
Press_space= ["space", ""]
walk = ["Control_L", ""]
turn90degrees = ["q", ""]
Mouse_x = 0
Mouse_y = 0
mouse_clickL = ["ClickMouseL", ""]
mouse_clickR = ["ClickMouseR", ""]

object_classification_type = ["enemy", "unclassified", "resource", "Object we can control" ]

# VideoGame title
game_window_title = "Default - Wine desktop"

opencv.ProcessGameFrame()

#focus on window hosting the video game
subprocess.call(["wmctrl", "-a", "Default - Wine desktop"])
name_of_window_currently_in_focus = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

run_controller = subprocess.Popen(['bash', executableControlFile])

run_program = 1
while run_program:
    name_of_window_currently_in_focus = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

    while name_of_window_currently_in_focus == game_window_title:
                result = opencv.ProcessGameFrame()
                #for i in range(0, len(result)):
                #    print result[i]
                print result[1]
                run_controller = subprocess.Popen(['bash', executableControlFile, activate_controller[0], random.choice(up), random.choice(down), random.choice(left), random.choice(right),
                     random.choice(downAction), random.choice(Press_space), random.choice(walk), random.choice(turn90degrees), str(random.randint(0, 1024)), str(random.randint(0, 768)),
                     random.choice(mouse_clickL), random.choice(mouse_clickR)])

                name_of_window_currently_in_focus = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())


    #if window has lost focus then re-focus and pause the game
    subprocess.call(["wmctrl", "-a", "Default - Wine desktop"])
    name_of_window_currently_in_focus = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    if name_of_window_currently_in_focus == game_window_title:
        run_controller = subprocess.call(['bash', executableControlFile, activate_controller[1]])
        run_capture.terminate()
        run_capture.wait()
    run_program = 0