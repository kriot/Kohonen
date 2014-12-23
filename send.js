var RecResolution = 100;
$(document).ready(function(){
	$("#send").click(function(){
    PrepareImage();
		$.ajax({
			type: "POST",
			url: "service.php",
			data: {img: getImage()}
		}).done(function(data){
			$("#data").html(data);
		});
	});
	ResetCanvas();
});
function getImage()
{
	file = "";
	var w = RecResolution;
	var h = RecResolution;
	file += RecResolution * RecResolution + " ";
	var ctx = document.getElementById("theCanvas").getContext("2d");
	img = ctx.getImageData(500, 0, RecResolution, RecResolution);
	for(var i=0;i<w*h*4;i+=4)
	{
		file += img.data[i+0] + " ";
	}
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
  var wc = right-left;
  var hc = bottom-top;
  img = ctx.getImageData(left, top, wc, hc);
  //For testing crop
  //ctx.putImageData(img, 0, 0);
  
  //straching image
  var simg = ctx.createImageData(RecResolution, RecResolution);
  for(var i = 0; i < hc; ++i)
  {
    for(var j = 0; j < wc; ++j)
    {
      var p = i*wc*4 + j*4;
      if(img.data[p] < 200) //plotted pixel
      {
        var ap = Math.floor(i*RecResolution/hc)*RecResolution*4 + Math.floor(j*RecResolution/wc)*4;
        simg.data[ap + 0] = img.data[p + 0];
        simg.data[ap + 1] = img.data[p + 1];
        simg.data[ap + 2] = img.data[p + 2];
        simg.data[ap + 3] = img.data[p + 3];
      }
    }
  }
  ctx.putImageData(simg, 0, 0);

  //Distance field
  var d = []; 
  for(var i = 0; i < RecResolution; ++i)
  {
    d[i] = [];
    for(var j = 0; j < RecResolution; ++j)
    {
      var p = i*RecResolution*4 + j*4;
      if(simg.data[p+3] > 200  ) //plotted pixel
      {
        d[i][j] = {x: 0, y: 0, c: 0};
      }
      else
      {
        d[i][j] = {x: RecResolution, y: RecResolution, c: 255};
      }
    }
  }
  checkPixel = function(y, x, vy, vx)
  {
    if(y+vy<0 || x+vx<0 || y+vy >= RecResolution || x+vx >= RecResolution)
      return RecResolution*RecResolution;
    var cp = d[y+vy][x+vx];
    return (true ? (cp.x - vx)*(cp.x - vx) + (cp.y - vy)*(cp.y - vy) : RecResolution*RecResolution);
  }
  for(var j = 1; j + 1 < RecResolution; ++j)
  {
    for(var i = 1; i + 1 < RecResolution; ++i)
    {
      var min = checkPixel(j, i, 0, 0);
      var t;
      if((t = checkPixel(j, i, -1, 0)) < min)
      {
        min = t;
        d[j][i].x = d[j-1][i].x ;
        d[j][i].y = d[j-1][i].y + 1;
      }
      if((t = checkPixel(j, i, -1, -1)) < min)
      {
        min = t;
        d[j][i].x = d[j-1][i-1].x + 1;
        d[j][i].y = d[j-1][i-1].y + 1;
      }
      if((t = checkPixel(j, i, 0, -1)) < min)
      {
        min = t;
        d[j][i].x = d[j][i-1].x + 1;
        d[j][i].y = d[j][i-1].y;
      }

      if((t = checkPixel(j, i, -1, +1)) < min)
      {
        min = t;
        d[j][i].x = d[j-1][i+1].x - 1;
        d[j][i].y = d[j-1][i+1].y + 1;
      }
    }
  }
  //Back step
  
  //Attention! this function uses global array d/d2;
  checkPixel = function(y, x, vy, vx)
  {
    if(y+vy<0 || x+vx<0 || y+vy >= RecResolution || x+vx >= RecResolution)
      return RecResolution*RecResolution;
    var cp = d2[y+vy][x+vx];
    return (true ? (cp.x - vx)*(cp.x - vx) + (cp.y - vy)*(cp.y - vy) : RecResolution*RecResolution);
  }

  var d2 = []; 
  for(var i = 0; i < RecResolution; ++i)
  {
    d2[i] = [];
    for(var j = 0; j < RecResolution; ++j)
    {
      var p = i*RecResolution*4 + j*4;
      if(simg.data[p+3] > 150  ) //plotted pixel
      {
        d2[i][j] = {x: 0, y: 0, c: 0};
      }
      else
      {
        d2[i][j] = {x: RecResolution, y: RecResolution, c: 255};
      }
    }
  }
  for(var j = RecResolution - 2; j > 0; --j)
  {
    for(var i = RecResolution - 2; i > 0; --i)
    {
      var min = checkPixel(j, i, 0, 0);
      var t;
      if((t = checkPixel(j, i, 1, 0)) < min)
      {
        min = t;
        d2[j][i].x = d2[j+1][i].x ;
        d2[j][i].y = d2[j+1][i].y - 1;
      }
      if((t = checkPixel(j, i, 1, -1)) < min)
      {
        min = t;
        d2[j][i].x = d2[j+1][i-1].x + 1;
        d2[j][i].y = d2[j+1][i-1].y - 1;
      }
      if((t = checkPixel(j, i, 0, 1)) < min)
      {
        min = t;
        d2[j][i].x = d2[j][i+1].x - 1;
        d2[j][i].y = d2[j][i+1].y;
      }

      if((t = checkPixel(j, i, +1, +1)) < min)
      {
        min = t;
        d2[j][i].x = d2[j+1][i+1].x - 1;
        d2[j][i].y = d2[j+1][i+1].y - 1;
      }
    }
  }
  var r = []; 
  for(var i = 0; i < RecResolution; ++i)
  {
    r[i] = [];
    for(var j = 0; j < RecResolution; ++j)
    {
      r[i][j] = Math.min((d[i][j].x)*(d[i][j].x) + d[i][j].y*d[i][j].y, (d2[i][j].x)*(d2[i][j].x) + d2[i][j].y*d2[i][j].y);
      //r[i][j] = (d2[i][j].x)*(d2[i][j].x) + d2[i][j].y*d2[i][j].y
      //r[i][j] = (d[i][j].x)*(d[i][j].x) + d[i][j].y*d[i][j].y
    }
  }

  var cov = 70;
  var dimg = ctx.createImageData(RecResolution, RecResolution);
  for(var i = 0; i < RecResolution; ++i)
  {
    for(var j = 0; j < RecResolution; ++j)
    {
      var p = i*RecResolution*4 + j*4;
      var c = 255 - 255*(cov/(cov+Math.pow((r[i][j]), 0.7)));
      c = Math.floor(c);
      dimg.data[p + 0] = c;
      dimg.data[p + 1] = c;
      dimg.data[p + 2] = c;
      dimg.data[p + 3] = 255;
    }
  }
  ctx.putImageData(dimg, 500, 0);

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
