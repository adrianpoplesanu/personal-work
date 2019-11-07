<?php
    $url = 'http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/';

    function get_url($url) {
        $contents = file_get_contents($url);
        if ($contents !== false) {
            return $contents;
        }
        return "error!";
    }

    function post_url($url, $data, $headers) {
        return "error!";
    }

    echo get_url($url) . "\n";
    echo post_url($url, [], []) . "\n";
?>
