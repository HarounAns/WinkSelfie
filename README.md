# WinkSelfie
Hands-free Photo Capture with Face/Wink Detection. The project uses OpenCV to scan users face, detects wink, and uses camera to capture a selfie. This functionality allows a user to first smile, and then wink, in order to take a hands-free self-portrait.  My program uses the OpenCV VideoCapture class to capture a video stream from a laptop’s camera. At any given time, your program should keep a queue of the last 100 frames. Most videos are 10-30 frames per second, so this is roughly 3-10 seconds of video in the queue. 

In each frame, the program uses OpenCV face detection functionality to find faces. Then inside each face, it finds the eyes. The program keeps track of how many eyes are visible in any face. If exactly one eye is visible in a face, it is considered a wink. When a wink is detected (in any face) at frame t, the program saves the frame at that time t. 

# Secret of the Universe
The program reveals the answer to all of the Universe’s Secrets if everyone in the room closes their eyes.  It then will remove the secrets from the computer screen when someone opens their eyes. This level of eye detection is something very new and advanced to opencv so don’t try to look it up, because there isn’t enough material online yet regarding this matter (there may not be any material at all)! This advanced eye detection will know if someone’s eyes in the room are open (regardless if they are on screen) or if somebody is peeking, and will swiftly close the secrets if it detects anyone doing so.  Try your luck trying to trick the machine to get ahold of the Universe’s Secrets, but I’ve done a great job, and can (almost) guarantee that you’ll never be able to get em. Instructions to enter extra credit mode are in comments of line 97 and 98.
