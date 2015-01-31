<?php
	$dat = file_get_contents("web/visualize.dat");
	$dat = '['.str_replace(" ", ", ", $dat).']';
?>
<html>
<head>
	<script src="jquery.js"></script>
	<script>
	var data = <?php echo $dat; ?>;
	</script>
	<script src="visualize.js"></script>
</head>
<body>
	<canvas id="theCanvas"></canvas>
</body>
</html>
