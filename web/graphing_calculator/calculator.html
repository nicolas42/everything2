<DIV id="calculator" style="width: 400px; height: 400px; ">
    <p class="title">Calculator</p>
    <textarea></textarea>
    <p class="output"></p>
</DIV>


<STYLE>

body { margin: auto; width: 800px; height: 100%; }

/* calculator stuff */
/* #calculator { width: 400px; height: 400px; } */
#calculator > * { font-weight: 100; font-family: sans-serif; font: 16px sans-serif; }
#calculator { display: flex; flex-direction: column; } 
#calculator > textarea { flex-grow: 1; /* default 0 */ }

* { box-sizing: border-box; padding: 5px; border: 1px solid #eeeeee; margin: 5px;  }
</STYLE>    

<SCRIPT>

    function better_eval(code)
    {
        // evaluated code or return an error
        try {
            result = eval(code); 
        } catch (e) {
            if (e instanceof SyntaxError) {
                result = e.message;
            } 
            else {
                throw e;
            }
        }
        return result;
    }
    
    // import Math library    
    Object.getOwnPropertyNames(Math).forEach(function (fn) { 
        let execution_string = "window." + fn + "=" + "Math." + fn + ";"
        console.log(execution_string);
        Function(execution_string)();
    });

    let textarea = calculator.querySelector("textarea");
    let output = calculator.querySelector(".output");
    let title = calculator.querySelector(".title");

    textarea.value = `a=1;b=4;c=-21; x= ( -b + sqrt(b^2-4*a*c) ) / (2*a); y=a*x^2+b*x+c; `

    textarea.onkeyup = function(e) {
        let code = textarea.value.replace(/\^/g, "**")
        let result = better_eval(code);
        output.innerHTML = "= " + JSON.stringify(result); // result.toString();
    }

    document.body.onload = function(){ textarea.focus() }

</SCRIPT>













<!-- 
// calculator.style.width = "400px";
// calculator.style.height = "400px";

// [ calculator, title, textarea, output ].forEach(function(el){
//     // el.style.boxSizing = "border-box";
//     el.style.fontWeight = "100";
//     el.style.fontFamily = "sans-serif";
//     el.style.width = "100%";
//     el.style.fontSize = "16px";
//     el.style.fontFamily = "sans-serif";
//     el.style.borderSize = "1px";
//     el.style.borderColor = "#eeeeee";
// });

// textarea.style.height = "45%";
// output.style.height = "45%";

 -->
