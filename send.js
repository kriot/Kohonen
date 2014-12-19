$(document).ready(function(){
	$("#send").click(function(){
    PrepareImage();
	});
	ResetCanvas();
});
function getImage()
{
	var b = 2;
	file = "";
	var w = $("#theCanvas").width();
	var h = $("#theCanvas").height();
	file += b +" "+ w + " " + h+" ";
	var ctx = document.getElementById("theCanvas").getContext("2d");
	img = ctx.getImageData(0,0,w,h);
	img2 = ctx.createImageData(w,h);
	for(var i=0;i<w*h*4;i+=4)
	{
		file += ((img.data[i+0])<200?1:0) + " ";
		img2.data[i+0] =  ((img.data[i+0])<200?1:0)*255; 
		img2.data[i+1] = 255;
		img2.data[i+2] = 255;
		img2.data[i+3] = 255;
	}
	ctx.putImageData(img2, 0, 0);
	return file;
	
}

function PrepareImage()
{
	var w = $("#theCanvas").width();
	var h = $("#theCanvas").height();
	var ctx = document.getElementById("theCanvas").getContext("2d");
	img = ctx.getImageData(0,0,w,h);
  var left = w, right = 0, top = h, bottom = 0;
  for(var i = 0; i < h; ++i)
  {
    for(var j = 0; j < w; ++j)
    {
      var p = i*w*4 + j*4;
      if(img.data[p] < 200) //plotted pixel
      {
        if(i < top)
          top = i;
        if(i > bottom)
          bottom = i;
        if(j < left)
          left = j;
        if(j > right)
          right = j;
      }
    }
  }
  //cut image
  img = ctx.getImageData(left, top, right-left, bottom-top);
  ctx.putImageData(img, 0, 0);
}

function ResetCanvas()
{
	var w = $("#theCanvas").width();
	var h = $("#theCanvas").height();
	var context = document.getElementById("theCanvas").getContext("2d");
	context.beginPath();
	context.rect(0, 0, w, h);
	context.fillStyle = 'white';
	context.fill();
}