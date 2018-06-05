import cv2
##
# @param object: current analysed frame that will have boundbox drawn onto it
class drawBoxes:
    def __init__(self,frame):
        self.frame = frame
    ##
    # @param objectClassification: what has the object been classified as. This will
    #                               determine the color of its bounded box
    # @param objectInformation: information on object
    def draw_classification_box(self, objectInformation, object_classification):

        line_thickness = 2

        xandWidth = objectInformation[1][2] + objectInformation[1][0]
        yandHeight = objectInformation[1][3] + objectInformation[1][1]

        if (object_classification == "Object we can control"):
            cv2.rectangle(self.frame, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (0, 0, 255), line_thickness)

        elif (object_classification == "unclassified"):  # color blue
            cv2.rectangle(self.frame, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (255, 0, 0), line_thickness)

        elif (object_classification == "resource"): # color green
            cv2.rectangle(self.frame, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight), (0, 255, 0), line_thickness)

        elif (object_classification == "enemy"): #color red
            cv2.rectangle(self.frame, (objectInformation[1][2], objectInformation[1][3]), (xandWidth, yandHeight),(0, 0, 255), line_thickness)

        return self.frame