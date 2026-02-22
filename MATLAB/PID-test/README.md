# PID test files
Files for first PID test with pressure.

### Deploy code to arduino
To run test first open "PID Controller/PID_controller_.slx" and click "Build, Deploy and start" with the Arduino plugged in.

### Open UI
Then to monitor signals and tune PIDs run "tune_and_read.m" (ensure COM number is correct), the UI should open showing the pressure signal and the duty cycles being sent to each valve.
To tune parameters all values must be filled and the send button must be pressed.

### Save data
To save data fill in the file name and click save, this will save the data in the "Test Data" folder. Data will be saved from the point of the last save or from the point of the app starting.
All data from opening to closing the app will be auto saved as "auto_saved_data.mat".
