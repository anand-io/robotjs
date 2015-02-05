var driver = require('./build/Release/robotjs.node');
var clickedOnce = false;

var mouse = {};

mouse.click = function(type, callback) {
    if (type === undefined) {
        driver.mouseClick();
        if (callback) callback();
    } else {
        switch (type) {
            case 'left':
            	if(!clickedOnce)
                	driver.mouseClick('left');
                else
                	driver.doubleMouseClick('left');
            	clickedOnce = true;
            	setTimeout(function(){clickedOnce = false;},700);
                if (callback) callback();
                break;
            case 'right':
                driver.mouseClick('right');
                if (callback) callback();
                break;
        }

    }
};

mouse.moveMouse = driver.moveMouse;
mouse.getPosition = driver.getMousePos;
mouse.getMousePos = driver.getMousePos;

// NOTE: x,y are pixels here.
mouse.move = function(x, y) {
    driver.moveMouse(x, y);
};

mouse.keyTap = function(ch) {
    driver.keyTap(ch);
};

mouse.typeString = function(str) {
    var car = str.split("");
    car.forEach(function(ch) {
        setTimeout(function() {
            driver.keyTap(ch);
        }, 30);
    });
};

mouse.mouseDown = driver.mouseDown;
mouse.mouseUp = driver.mouseUp;

mouse.onmousedown = function(type, callback) {

    if (typeof type == 'string') {
        mouse.mouseDown(type);
        if (callback) callback();
    } else {
        mouse.mouseDown();
        if (typeof type == 'function')
            type();
    }
};

mouse.onmouseup = function(type, callback) {

    if (typeof type == 'string') {
        mouse.mouseUp(type);
        if (callback) callback();
    } else {
        mouse.mouseUp();
        if (typeof type == 'function')
            type();
    }
};

mouse.scroll = driver.scroll;
mouse.moveMouseSmooth = driver.moveMouseSmooth;

mouse.DragTo = function(x, y, flag) {

};

module.exports = mouse;