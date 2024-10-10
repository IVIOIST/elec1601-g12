# Robot
## Overview
## Todo
### 16/09/2024
- refine the logic of the robot in intersections
    - the robot should 'look' left and right before deciding on which way  to turn instead of defaulting to left
- refine the logic of the robot when in a dead end
    - currently the robot is stuck in a loop between veering left and right 
      at a dead end, maybe we can implement logic where if its stuck in the loop it will reverse until it no longer does
- tweak the sensitivity of the distance threshold
    - currently in a straight line, the robot will wiggle, this may be because the sensitivity of the distance threshold is too low causing it to lose track of the walls
### 23/09/2024
