var http = require('http');
var fs = require('fs');
var path = require('path');




async function server_function(request, response) {
    console.log('request starting...');

    var filePath = '.' + request.url;

    // get rid of url encodings
    // like ?var1=value&var2=value2 ... 
    filePath = filePath.split('?')[0]
    console.log(filePath)


    if (filePath == './')
        filePath = './index.html';

    var extname = path.extname(filePath);
    console.log(extname)
    var contentType = 'text/html';
    switch (extname) {
        case '.js':
            contentType = 'text/javascript';
            break;
        case '.css':
            contentType = 'text/css';
            break;
        case '.json':
            contentType = 'application/json';
            break;
        case '.png':
            contentType = 'image/png';
            break;      
        case '.jpg':
            contentType = 'image/jpg';
            break;
        case '.wav':
            contentType = 'audio/wav';
            break;
    }

    fs.readFile(filePath, function(error, content) {
        if (error) {
            if(error.code == 'ENOENT'){
                fs.readFile('./404.html', function(error, content) {
                    response.writeHead(200, { 'Content-Type': contentType });
                    response.end(content, 'utf-8');
                });
            }
            else {
                response.writeHead(500);
                response.end('Sorry, check with the site admin for error: '+error.code+' ..\n');
                response.end(); 
            }
        }
        else {
            response.writeHead(200, { 'Content-Type': contentType });
            response.end(content, 'utf-8');
        }
    });

}


const server = http.createServer(server_function);
server.listen(8080);




