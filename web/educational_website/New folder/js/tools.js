function showHide(id){
	// show hide block element
	// REQUIRES that <el>.style.display be initialized to
	// "none" or "block" to work properly

	it = document.querySelector(id);
	if (it.style.display === "flex"){
		it.style.display = "none";
	} else {
		it.style.display = "flex";
	}
}

function playPause(arg) {
	var video = document.querySelector(arg);
  if (video.paused) {
	video.play();
  } else {
	video.pause();
  }
}

function toggleMargins() {
	var style = document.body.style;
  if (style.maxWidth !== '800px') {
	style.maxWidth = '800px';
  } else {
	style.maxWidth = 'none';
	}
	// console.log('toggleMargins');
}

function playPauseOrbitVideo(arg) {
	playPause('#myVideo');	
}

function showHideMenu(){
	showHide('nav.container');
}


// attempt to make pages minimum page height
resize_div_inner = function(){
    let div_inner = document.querySelector("div.inner");
    console.log("window onload\n");

    if ( document.body.offsetHeight < window.innerHeight )
	document.body.style.height = window.innerHeight.toString()+"px";
	document.querySelector("div.inner").style.height = window.innerHeight.toString()+"px";

}

//  window.onload = resize_div_inner;
