<?php
    $options = array(
        'http' => array (
            'method' => 'GET',
            'content' => 'http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/',
            //'header' => 'Content-Type: application/x-www-form-urlencoded'
            )
        );
    $context  = stream_context_create($options);
    //$verify = file_get_contents($url, false, $context);
    echo $context . "\n";
    //print_r($context);
    //$response = http_get("http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/");
    //echo $response;
?>
