# DAM-CPU
CPU setup of Xavier and Xavier NX


# Arduino Setup
- add the OpenCR board per the robotis documentation
- copy the damm_msgs folder into the libraries folder for the Arduino folder (usually in My Documents folder)
- the settings change sketch is for the an intermediary between PS4 remote and the opencr board
 - the complete control sketch will have the OpenCr board listen directly to the PS4 without needing to launch an intermediary 

# Xavier
- Jetpack 4.2.3
-- last one with OpenCV3 for max Melodic compatibility
- Runs the Jackal_bringup package which runs ROS at bootp

# Xavier NX
- Jetpack 4.4DP
 This is used to provide control of the robot remotely. Any linux machine could work.
 - DeepstreamSDK installed to imporve streaming performance
 ROS Melodic
