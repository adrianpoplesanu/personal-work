<?php
    $url = 'http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/';
    $contents = file_get_contents($url);
    if ($contents !== false) {
        echo $contents;
    }
?>
