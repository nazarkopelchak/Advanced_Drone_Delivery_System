# 3081W Homework4 Advanced Drone Delivery System

## Overview

  Advanced Drone Delivery System introduces the battery concept to the Drone Delivery System. The Delivery Drone is created with its own battery. Using its battery, it can perform (user created) robot deliveries. The Delivery Drone has different battery consumption properties, depending on whether the drone is carrying a robot or not. Advanced Drone Delivery System also creates a Charging Drone (UFO) which is responsible for making sure the Delivery Drone has enough energy to complete its deliveries. Another addition to this simulation is a Charging Station. This station serves as a starting position for the Charging Drone. In addition, the Charging Station is also responsible for recharging the Charging Drone after it completes its task. Charging Drone has a more capable battery than the Delivery Drone, which guarantees that it successfully arrives to a Derivery Drone position, recharges the drone using its own battery and returns back to the Charging Station.

## What will you need to run the simulation

1. Access to Ubuntu or CSE Lab machine.
2. Git installed.
3. Access to the Internet and Web Browser of your choice.

### Install Git on your personal machine

- Navigate [here](https://git-scm.com/) to install Git.
  - Note. If you are using CSE Lab Machine, you do not to install Git. It is already installed.

### Retrieve the project material from GitHub

- Open a desired folder to store the project in.
- Open a terminal inside of that folder.
- Type the command provided below to retrieve the material.
  - Note. You will need an UMN username and password to be able to pull from this GitHub repository.

```bash
% git clone https://github.umn.edu/KOPEL039/Homework4.git
```
- After git clone command is done running, go to "Homework4/project" directory.
  - To go to "Homework4/project" directory, execute the following command in the same terminal.

```bash
% cd Homework4/project/
```
## Run the simulation

- Open a new terminal in the project folder or use the same one from previous steps.
- Type in these following commands in the terminal to compile the project.
  - Note. "make -j" will take some time to be executed.

```bash
% make clean
```

```bash
% make -j
```

- After "make -j" is done executing, run the command provided below to run the simulation.
  - IMPORTANT NOTE. DO NOT close the terminal after executing the command below, since it will shut down the server.

```bash
% ./build/bin/transit_service 8081 apps/transit_service/web/
```

- The simulation is now live. You can access it by following the links below.
  - Navigate to [http://127.0.0.1:8081/schedule.html](http://127.0.0.1:8081/schedule.html) and you should see a a page to schedule the trips.
  - Navigate to [http://127.0.0.1:8081/](http://127.0.0.1:8081/) and you should see a visualization.
  - To view the entities, click on the right top of the visualization page (not the schedule page) and choose the entity to view such as Charging Drone, Delivery Drone or (robot name) that you give in the schedule page.
  

## Requirements for the Homework #4

### All the team member names and x500s
 - Nazar Kopelchak || kopel039
 - Kirstin Stanley || stan0534
 - Riley Nelson    || nel01257
 - Lucas Kivi      || kivix019
### Here is the path to access our project: /Homework4/project
### Sprint retrospective
  - What went well
    - Communication and organization went smooth as everyone was consistenly available on discord and always attended meetings.
    - We also pivoted well as we modified features and adjusted UML and documentation accordingly.
  - What didn't go well
    - It took some time for our team to decide on our final product.
    - We were bit scatter brained in our initial design.
  - What could be done next time
    - Need to spend more time on requirements and ideas for the project
    - We could have done some more thorough planning for our features. This could include UML models to hold ourselves accountable and on task.

