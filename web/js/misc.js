/*

// example
var node = elt("div", "id=mandelbro",
    elt("canvas", "id=canvas"),
    elt("p", "id=infoPara")
);	

*/

function elt(type) {
    // Create HTML element tree 
    // modified from eloquent javascript
	
	var node = document.createElement(type);
	var i;
	var child;
	var attr;
	for (i = 1; i < arguments.length; i+=1) {
	  child = arguments[i];
	  if (typeof child === "string"){

	  	if ( child.includes("=") ) {
			attr = child.split("=");
	      node.setAttribute(attr[0],attr[1]);
	    } else {
	    	child = document.createTextNode(child);
	      	node.appendChild(child);
	    }

	  } else {
	  	node.appendChild(child);
		}
	}
	return node;
}


function get_parameters_from_url() {

	// usage:
	// use ?var=value&var2=value2 format for url parameter encoding
	// 
	// e.g. file:///Users/nick/everything/test/index.html?a=234&b=234
	//
	// params = get_parameters_from_url();
	// console.log(params);
	//
    // originally from https://html-online.com/articles/get-url-parameters-javascript/

	var url = window.location.href;
	var parameters = {}
    var parts = url.replace(/[?&]+([^=&]+)=([^&]*)/gi, function (m, key, value) {
        parameters[key] = value;
    });
    return parameters;
}



// function update_url_without_refreshing_page(mandelbrot_entity) {
//     var m = mandelbrot_entity;
//     console.log(m)
//     // https://computerrock.com/blog/html5-changing-the-browser-url-without-refreshing-page/
//     window.history.replaceState("object or string", "Title", "?x=" + m.x + "&y=" + m.y + "&zoom=" + m.zoom + "&w=" + m.w + "&h=" + m.h + "&max_iterations=" + m.max_iterations);
// }






// // FORM <=> OBJECT STUFF

// function create_form_from_object(obj)
// {
//     let parent = document.createElement("div");
//     for (key in obj) {
//         // if ( isNaN(obj[key]) ) { console.log(key); continue; }
//         let child = document.createElement("input");
//         child.placeholder = name;
//         child.type = "text";
//         child.name = key;
//         child.value = obj[key];
//         // child.id = key;
//         parent.appendChild(child);
//         let br = document.createElement("br");
//         parent.appendChild(br);
//     }

//     return parent;
// }

// function get_form(form)
// {
//     let obj = {}
//     for (let i=0; i<form.children.length; i+=1 ) { 
//         // if ( isNaN(obj[form.children[i].name]) ) { continue; }
//         obj[form.children[i].name] = form.children[i].value;
//     }
//     return obj;
// }

// function set_form(form, obj)
// {    
//     let keys=Object.keys(obj); 
//     for ( let i=0; i<keys.length; i+=1 ) { 
//         // if ( isNaN(obj[keys[i]]) ) { continue; }
//         form.children[i].value = obj[keys[i]];
//     }
//     return form;
// }