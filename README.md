# tof_range_finder
arduino sketch for sparkfun tof range finder
- copy the content of this repository to your arduino sketches folder
- connect tof range finder to an arduino board as shown in https://learn.sparkfun.com/tutorials/vl6180-hookup-guide in section "Using the VL6180 Sensor
- connect the arduino to your computer
- open arduino IDE, go to File > Sketches > tof_range_finder and press upload
- in a terminal run
    rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0
    (make sure the name of the port is correct)
- in a new terminal run
    rostopic echo tof_range_finder
- see distance measurement readings (in mm) published
