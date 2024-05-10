#!/bin/bash

# Change directory to the location of my_add
cd ~/Desktop/Programming/University/OS_C_prog/MAMAN_11/my_add/
# Run make_file_add to compile your program
./make_file_add
# Move back to the previous directory
cd -

# Change directory to the location of my_suffix
cd ~/Desktop/Programming/University/OS_C_prog/MAMAN_11/my_suffix/
# Run make_file_suffix to compile your program
./make_file_suffix
# Move back to the previous directory
cd -

# Run a new Alacritty terminal session and execute a bash shell inside the Docker container
alacritty -e sh -c '
# Send the my_add and my_suffix directories to the Docker container
sudo docker cp ~/Desktop/Programming/University/OS_C_prog/MAMAN_11/my_add/ University_dock:/root/
sudo docker cp ~/Desktop/Programming/University/OS_C_prog/MAMAN_11/my_suffix/ University_dock:/root/
# Enter the Docker container
sudo docker exec -it University_dock /bin/bash
'
