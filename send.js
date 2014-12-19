$(document).ready(function(){
	$("#send").click(function(){
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
