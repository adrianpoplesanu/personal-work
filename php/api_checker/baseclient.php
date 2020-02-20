<?php
require 'vendor/autoload.php';

class BaseAPIClient {
    public function __construct() {
        echo "construct\n";
        $this->host = "10.10.76.16";
    }

    public function get_status() {
        echo "get_status\n";
        $uri = "/status";
        $client = new GuzzleHttp\Client(['base_uri' => 'http://www.cursvalutar.ro']);
        $response = $client->request('GET', 'curs-gbp');
        echo $response->getBody();
        // $client do request
        // do a request to $this->host . $uri and print it
    }
}

$api_client = new BaseAPIClient();
$api_client->get_status();
?>
