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
  
![sample 1](https://pp.userapi.com/c639418/v639418165/391f7/2CzFR2aDW1E.jpg)  
  
Each number on the map corresponds to a point in space:  
  
* The horizontal position corresponds to its axis,  
* The vertical position corresponds to its ordinate,  
* The value corresponds to its altitude.  
  

All these points must be connected by lines. For this, I used the Bresenham's line algorithm, which allows me to calculate all the pixels that must be color-coded to form a line between two points in space.
(img 2)  
  
And now it is time for magic, which was achieved with the rotation matrix. Multiplying the rotation matrices around different axes, I got a universal matrix that allowed me to efficiently and quickly calculate/recalculate all points in space. Here is some examples:  
(img 3+)  
  
Some additional features, like real time recalculating/redrawing result image using the keyboard control. Here is some examples:  
(gif 1+)  
 
