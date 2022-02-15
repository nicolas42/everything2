
// How to resize canvas
// https://stackoverflow.com/questions/4938346/canvas-width-and-height-in-html5

var conway = function(options){

        // "use strict"
    function evolve(canvas, aliveColor, deadColor) {

        // The alpha channel is used to keep track of the number of neighbours

        var image = canvas.getContext("2d").getImageData(0, 0, canvas.width, canvas.height);

        var neighbours;
        var shouldLive; // 1 = live, 0 = die
        var stride = 4;

        // Set all neighbour values to zero
        for (var y = 1; y < canvas.height - 1; y = y + 1) {
            for (var x = 1; x < canvas.width - 1; x = x + 1) {
                var pos = y * canvas.width * 4 + x * 4;

                image.data[pos + 3] = 0; 	// pos + 3 refers to the alpha channel of the pixel
            }
        }

        function isAlive(imageData){
            return image.data[pos + 0] === aliveColor[0] && image.data[pos + 1] === aliveColor[1] && image.data[pos + 2] === aliveColor[2];
        }    

        // Update Neighbors of surrounding cells
        // Add one to the neighbours of all of the surrounding cells
        // (3x3 square around the current cell) if the current cell is alive
        for (y = 1; y < canvas.height - 1; y = y + 1) {
            for (x = 1; x < canvas.width - 1; x = x + 1) {
                pos = y * canvas.width * 4 + x * 4;

                if (isAlive(image.data)) { // currCell.isAlive

                    image.data[pos + 3 - (canvas.width - 1) * stride] += 1;
                    image.data[pos + 3 - (canvas.width) * stride] += 1;
                    image.data[pos + 3 - (canvas.width + 1) * stride] += 1;
                    image.data[pos + 3 - 1 * stride] += 1;
                    // position of the current cell
                    image.data[pos + 3 + 1 * stride] += 1;
                    image.data[pos + 3 + (canvas.width - 1) * stride] += 1;
                    image.data[pos + 3 + (canvas.width) * stride] += 1;
                    image.data[pos + 3 + (canvas.width + 1) * stride] += 1;
                }
            }
        }

        // Update who's alive and who's dead
        for (y = 1; y < canvas.height - 1; y = y + 1) {
            for (x = 1; x < canvas.width - 1; x = x + 1) {
                pos = y * canvas.width * 4 + x * 4;
                neighbours = image.data[pos + 3];
                shouldLive = 0; // determines whether cell lives or dies

                if (isAlive(image.data)) { // currCell.isAlive
                    if (neighbours < 2) {
                        shouldLive = 0; // false
                    } else if ((neighbours === 2) || (neighbours === 3)) {
                        shouldLive = 1; // true
                    } else if (neighbours > 3) {
                        shouldLive = 0; // false
                    }
                } else {
                    if (neighbours === 3) {
                        shouldLive = 1; // true
                    }
                }
                if (shouldLive === 1) {
                    image.data[pos + 0] = aliveColor[0];
                    image.data[pos + 1] = aliveColor[1];
                    image.data[pos + 2] = aliveColor[2];
                    image.data[pos + 3] = aliveColor[3];
                } else {
                    image.data[pos + 0] = deadColor[0];
                    image.data[pos + 1] = deadColor[1];
                    image.data[pos + 2] = deadColor[2];
                    image.data[pos + 3] = deadColor[3];
                }
            }
        }

        canvas.getContext("2d").putImageData(image, 0, 0);
    }


    function drawRandomPoints(canvas, aliveColor, deadColor){

        // Draw initial random points to fill 10% of the usable space
        var ctx = canvas.getContext("2d");
        var rgbaDeadColor = 'rgba(' + deadColor[0] + ',' + deadColor[1] + ',' + deadColor[2] + ',' + deadColor[3] + ')';
        var rgbaAliveColor = 'rgba(' + aliveColor[0] + ',' + aliveColor[1] + ',' + aliveColor[2] + ',' + aliveColor[3] + ')';
        // console.log(rgbaAliveColor, rgbaDeadColor); // debug
        ctx.fillStyle = rgbaDeadColor // needs this format apparently
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        for (var i = 0; i < 0.1 * canvas.width * canvas.height; i += 1) {
            var x = Math.round(Math.random() * (canvas.width - 1));
            var y = Math.round(Math.random() * (canvas.height - 1));
            ctx.fillStyle = rgbaAliveColor;
            ctx.fillRect(x, y, 1, 1);
        }
    }


    // Hex <-> Bytes
    // from crypto-js
    // https://stackoverflow.com/questions/14603205/how-to-convert-hex-string-into-a-bytes-array-and-a-bytes-array-in-the-hex-strin

    // Convert a hex string to a byte array
    function hexToBytes(hex) {
        console.log(hex);
        for (var bytes = [], c = 0; c < hex.length; c += 2)
        bytes.push(parseInt(hex.substr(c, 2), 16));
        return bytes;
    }

    // Convert a byte array to a hex string
    function bytesToHex(bytes) {
        for (var hex = [], i = 0; i < bytes.length; i++) {
            var current = bytes[i] < 0 ? bytes[i] + 256 : bytes[i];
            hex.push((current >>> 4).toString(16));
            hex.push((current & 0xF).toString(16));
        }
        return hex.join("");
    }


    var defaults = {
        canvas: document.querySelector("canvas"),
        // querySelector: "canvas",
        height: 200,
        width: 200,
        aliveColor: "0000FFFF", //[0, 0, 255, 255], 
        deadColor: "FFFFFFFF", //[255, 255, 255, 255], 
        delay: 200
    };

    let a = Object.assign({}, defaults, options);

    // a.canvas = document.querySelector(a.querySelector);
    a.canvas.width = a.width;
    a.canvas.height = a.height;

    a.aliveColor = hexToBytes(a.aliveColor);
    a.deadColor = hexToBytes(a.deadColor);
    if (a.aliveColor.length === 3){ a.aliveColor.push(255); }
    if (a.deadColor.length === 3){ a.deadColor.push(255); }

    drawRandomPoints(a.canvas, a.aliveColor, a.deadColor);


    // clearInterval(timerID); //pause;

    var timerID = setInterval(
        ()=>{evolve(a.canvas, a.aliveColor, a.deadColor)}, 
        a.delay
    ); // play;

    return timerID;
};


