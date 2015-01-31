$(document).ready(function(){
	    var ctx = document.getElementById("theCanvas").getContext("2d");
		    var w = Math.sqrt(data[0]);
			    var h = w;
				    img = ctx.createImageData(w, h); 
					    var k = 1;
						    for(var i = 0; i < w*h*4; i += 4, ++k)
{
	    img.data[i + 0] = data[k];
	    img.data[i + 1] = data[k];
	    img.data[i + 2] = data[k];
				    img.data[i + 3] = 255;
}

ctx.putImageData(img, 100, 0);
});

