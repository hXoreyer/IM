<?php
include 'rander.php';
$rand = make_rander(5);

$output=exec('python sendmail.py '.$rand .' ' .$_POST['em']);
echo $rand;
?>
