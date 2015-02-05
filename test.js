var robot  = require('../robotjs');

robot.click('left');
robot.mouseDown('left');

robot.moveMouseSmooth(400,400);

robot.mouseUp('left');