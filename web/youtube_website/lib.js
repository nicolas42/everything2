// save a text file
function save_text_file(filename, text) {
    var pom = document.createElement('a');
    pom.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
    pom.setAttribute('download', filename);

    if (document.createEvent) {
        var event = document.createEvent('MouseEvents');
        event.initEvent('click', true, true);
        pom.dispatchEvent(event);
    }
    else {
        pom.click();
    }
}

// edit a webpage directly then save it as a file
// document.body.contentEditable = 'true';
// save_text_file("omg.html", document.body.innerHTML);


function get_filename_extension(filename)
{
    return filename.split('.').pop();
}

function stringify(sth)
{
    return JSON.stringify(sth, function(key, val) { return val.toFixed ? Number(val.toFixed(10)) : val; }) // sets numbers to fixed length
}

// alternative to eval
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/eval
function eval(obj){
    return Function('"use strict";return (' + obj + ')')();
}
