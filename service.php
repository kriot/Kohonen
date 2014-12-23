<?php
file_put_contents("web/recognize.dat", $_POST["img"]);
echo shell_exec("./main letters.net < ./web/recognize.dat");
?>
