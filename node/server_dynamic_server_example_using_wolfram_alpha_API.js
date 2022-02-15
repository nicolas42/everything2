const http = require('http');
const fs = require('fs');

const WolframAlphaAPI = require('wolfram-alpha-api');
const waApi = WolframAlphaAPI('RLX65E-KAUTW5RVLE');


function get_pikachu_stats_from_wolfram_alpha()
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

const server_function = async function (request, response) {
  // 1. Tell the browser everything is OK (Status code 200), and the data is in plain text
  response.writeHead(200, {
      'Content-Type': 'text/html'
  });

  console.log(request.headers.referer)
  // 2. Write the announced text to the body of the page
  var pikachu_stats = await get_pikachu_stats_from_wolfram_alpha();
  response.write('<h1>Pika pika</h1>\n');
  response.write('<pre>\n');
  response.write(pikachu_stats);
  response.write('</pre>\n');


  var data = fs.readFileSync('z.html');
  response.write(data);

  // 3. Tell the server that all of the response headers and body have been sent
  response.end();
}

const server = http.createServer(server_function);
server.listen(8080);






