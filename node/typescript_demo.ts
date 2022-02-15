// sudo npm install -g typescript

// tsc typescript_demo.ts; node typescript_demo.js

// An interface is a structure used solely for type-checking.
// There's also classes which are more complicated
interface SomePerson {
    name: string;
    // Optional properties, marked with a "?"
    age?: number;
    // And of course functions
    say_something(): void;
}

// type checking. "compile time" error checking
let dude : SomePerson = { name: 'bob', say_something: ()=>{console.log('ahoihoi')} };

console.log(dude)
dude.say_something()

interface Image {
    w: number; 
    h: number; 
    rgba: number[];
}

let im : Image = { w: 10, h: 10, rgba: [] }

for (let i=0; i<im.w*im.h; i+=1){
    im.rgba.push( (1*i << 24) + (2*i << 16) + (3*i << 8) + (4*i << 0) )
}
console.log(im);