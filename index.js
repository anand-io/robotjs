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
            	if(!clickedOnce){
                	driver.mouseClick('left');
                    clickedOnce = true;
                    setTimeout(function(){clickedOnce = false;},700);
                }
                else
                	driver.doubleMouseClick('left');
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

mouse.mouseHold = function(type, callback) {

    if (typeof type == 'string') {
    	if(!clickedOnce || type === 'right'){
            clickedOnce = true;
            setTimeout(function(){clickedOnce = false;},700);
        	mouse.mouseDown(type);
        }
        else
        	driver.doubleMouseClick(type);
    	
        if (callback) callback();
    } else {
        mouse.mouseDown();
        if (typeof type == 'function')
            type();
    }
};

mouse.mouseRelease = function(type, callback) {

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
mouse.clickWithCounts=driver.clickwithCount;
mouse.DragTo = function(x, y, flag) {

};

module.exports = mouse;