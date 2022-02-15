
var http = require('http');
var fs = require('fs');
var path = require('path');



const WolframAlphaAPI = require('wolfram-alpha-api');
const waApi = WolframAlphaAPI('RLX65E-KAUTW5RVLE');


function doit(query)
{
  return waApi.getFull({
    input: 'pikachu',
    includepodid: 'Statistics:PokemonData',
    format: 'plaintext',
  }).then((queryresult) => {

    console.log(queryresult.pods[0].subpods[0].plaintext)
    return queryresult.pods[0].subpods[0].plaintext

  }).catch((x)=>{ console.error(x)});

}

async function serve_pikachu(request, response)
{
    console.log("ZOMGOMGOMGOMG\n");
    response.writeHead(200, {
        'Content-Type': 'text/html'
    });
  
    console.log(request.headers.referer)
    // 2. Write the announced text to the body of the page
    var pikachu_stats = await doit(query);
    response.write('<h1>Pika pika</h1>\n');
    response.write('<pre>\n');
    response.write(pikachu_stats);
    response.write('</pre>\n');
  
  
    var data = fs.readFileSync('z.html');
    response.write(data);
  
    // 3. Tell the server that all of the response headers and body have been sent
    response.end();
}


async function server_function(request, response) {

    console.log('request starting...');

    var filePath = '.' + request.url;

    // get rid of url encodings
    // like ?var1=value&var2=value2 ... 
    filePath = filePath.split('?')[0]
    console.log(filePath)
    
    if (filePath == './pikachu'){
        serve_pikachu(request, response);
        return;
    }


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




