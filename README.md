## Subject
**Mandatory part** - 2d representation of 3d coordinates in isometric projection. This is enough for the successful project validation.  
**Bonus part** - my imagination. Here is a list of bonuses, that I added to my project:  
* Rotating the map in all 3 axes. Bonus, which includes all types of projections, like parallel, iso, conic etc.  
* Real time parameters changing ( such as angle of tilt and rotate ) using the keyboard, with fast recalculating and smooth redrawing scene.
* Color and gradient support.  
* The ability to read up to 9 files with maps in the same time, and switch between them in real time ( like tabs ).  

**Allowed libraries:**  
`math` ( includes the most common mathematical functions ),  
`miniLibX` ( x-window interface library ).  
**Allowed functions:**  
`open`, `read`, `write`, `close`, `malloc`, `free`, `perror`, `strerror`, `exit`.
## Details
This project is about creating a simplified graphic “wireframe” representation of a relief landscape linking various points
(x, y, z) via segments. The coordinates of this landscape are stored in a file passed as
a parameter to program. Here is an simple example:
![img 1](https://pp.userapi.com/c639418/v639418165/394d6/G1w82tAq22Y.jpg)  
  
Each number on the map corresponds to a point in space:  
  
* The horizontal position corresponds to its axis,  
* The vertical position corresponds to its ordinate,  
* The value corresponds to its altitude.  
  

All these points must be connected by lines. For this, I used the Bresenham's line algorithm, which allows me to calculate all the pixels that must be color-coded to form a line between two points in space.
![img 2](https://pp.userapi.com/c639418/v639418165/394e0/mOG2fy8P7Og.jpg)  
  
And now it is time for magic, which was achieved with the rotation matrix. Multiplying the rotation matrices around different axes, I got a universal matrix that allowed me to efficiently and quickly calculate/recalculate all points in space. Here is some examples:  
## Map: 42
![img 3](https://pp.userapi.com/c639418/v639418165/394ea/NviXSJ7YRK8.jpg)
## Map: mars
![img 4](https://pp.userapi.com/c639418/v639418165/394f8/dZucbzH7Pvg.jpg)
The same map, but a little closer look:  
![img 4.1](https://pp.userapi.com/c639418/v639418165/39835/KQAT4hjFbyQ.jpg)
## Map: pyramide
![img 5](https://pp.userapi.com/c639418/v639418165/39776/muj6JcxfEXY.jpg)
Let's add some color and gradient:
## Map: t1
![img 6](https://pp.userapi.com/c639418/v639418165/3983f/AmOhUtbdXL4.jpg)
## Map: julia
![img 7](https://pp.userapi.com/c639418/v639418165/39878/die6jioFOzE.jpg)
Some additional features, like real time recalculating/redrawing result image using the keyboard control. Here is some examples:  
![gif 1](https://github.com/kandreyc/additionalthing/blob/master/04.gif)
![gif 2](https://github.com/kandreyc/additionalthing/blob/master/07.gif?raw=true)
 
