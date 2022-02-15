// sudo npm install -g typescript
// type checking. "compile time" error checking
var dude = { name: 'bob', say_something: function () { console.log('ahoihoi'); } };
console.log(dude);
dude.say_something();
var im = { w: 10, h: 10, rgba: [] };
for (var i = 0; i < im.w * im.h; i += 1) {
    im.rgba.push((1 * i << 24) + (2 * i << 16) + (3 * i << 8) + (4 * i << 0));
}
console.log(im);
