<?php
// create a new cURL resource
$ch = curl_init();

// set URL and other appropriate options

$hostname = 'http://localhost:8080';

$params = array('foo' => 'bar');
$url = $hostname . '?' . http_build_query($params);
curl_setopt($ch, CURLOPT_URL, $url);

curl_setopt($ch, CURLOPT_HEADER, false);

// set up headers
curl_setopt($ch, CURLOPT_HTTPHEADER, [
    'X-Apple-Tz: 0',
    'X-Apple-Store-Front: 143444,12'
]);

// grab URL and pass it to the browser
curl_exec($ch);

// close cURL resource, and free up system resources
curl_close($ch);
?>
