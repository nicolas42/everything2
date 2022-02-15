function aspect(id){
	// return width / height
	theImage = document.getElementById(id);
	
	return theImage.naturalWidth / theImage.naturalHeight;
}

function originalSize(id){
	
	theImage = document.getElementById(id);
	
	theImage.height = theImage.naturalHeight;
	theImage.width = theImage.naturalWidth;
}

function fitWidth(id){
	theImage = document.getElementById(id);
	theImage.width = window.innerWidth;
	theImage.height = window.innerWidth / aspect(id);
	
}

function fitHeight(id){
	theImage = document.getElementById(id);
	theImage.height = window.innerHeight;
	theImage.width = window.innerHeight * aspect(id);
}

function resize(id, scale){
	
	theImage = document.getElementById(id);
	theImage.height = theImage.naturalHeight * scale;
	theImage.width = theImage.naturalWidth * scale;
}

function init(){
	fitHeight("theImage");
}