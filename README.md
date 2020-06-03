# GL_TASK_2
GlobalLogic Task2 repos (system loadability chart application) 

availible now:
1) Opportunities
+ Save data from specific period
+ Change what data will save
+ Pause counters
2) Windows part
+ CPU utilization
+ RAM/VRAM utilization
+ NETWORK utilization 
3) Linux part
+ CPU utilization

work in progress:
1) Oportunities
- Save data to specific catalogue
- correct Makefiles win/linux
3) Linux part
- RAM/VRAM utilization (Some problems)
- NETWORK utilization (Need testing)

// It will be reviewed below

Needed pkgs:

qt5-default
qtdeclarative5-dev
libqt5charts5-dev
qml-module-qtcharts

For Linux building:
Enter these console commands if GL_Task_2 folder:
qmake
make
./GL_Task_2

For Windows building:
Enter these console commands if GL_Task_2 folder:
qmake
make
./GL_Task_2.exe

File saving into build folder into data.txt file
