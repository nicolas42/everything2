/*
https://products.wolframalpha.com/api/libraries/javascript/

APP NAME: test
APPID: RLX65E-KAUTW5RVLE
USAGE TYPE: Personal/Non-commercial Only


npm install https://products.wolframalpha.com/api/libraries/javascript/wolfram-alpha-api-1.0.0-rc.1.tgz

*/



var WolframAlphaAPI = require('wolfram-alpha-api');
var waApi = WolframAlphaAPI('RLX65E-KAUTW5RVLE');

waApi.getShort('2+2').then(console.log, console.error);


waApi.getFull('sin x').then(console.log).catch(console.error);
// { success: true, error: false, numpods: 13, datatypes: '', ...

waApi.getFull('F9TVlu5AmVzL').then(console.log).catch(console.error);
// { success: false, error: false, numpods: 0, datatypes: '', ...

waApi.getFull('sin(x)').then((queryresult) => {
  const pods = queryresult.pods;
  const output = pods.map((pod) => {
    const subpodContent = pod.subpods.map(subpod =>
      `  <img src="${subpod.img.src}" alt="${subpod.img.alt}">`
    ).join('\n');
    return `<h2>${pod.title}</h2>\n${subpodContent}`;
  }).join('\n');
  console.log(output);
}).catch(console.error);


async function sth(){

    var a = await waApi.getFull({
        input: 'pikachu',
        includepodid: 'Statistics:PokemonData',
        format: 'plaintext',
    }).then((queryresult) => {
        console.log(queryresult.pods[0].subpods[0].plaintext)
        return queryresult.pods[0].subpods[0].plaintext
    }).catch(console.error)

    return a;
}

a = sth();




