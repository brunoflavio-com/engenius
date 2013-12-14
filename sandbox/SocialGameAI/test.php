<?php

// The data to send to the API
$postData = array(
    'ori' => '100',
    'des' => '101',
    'type'=> 'insert'
);

// Setup cURL
$ch = curl_init('http://localhost:5000/parsejson');
curl_setopt_array($ch, array(
    CURLOPT_POST => TRUE,
    CURLOPT_RETURNTRANSFER => TRUE,
    CURLOPT_HTTPHEADER => array(
        'Content-Type: application/json'
    ),
    CURLOPT_POSTFIELDS => json_encode($postData)
));

echo "Sent object:" . json_encode($postData) . "<br><br>";
// Send the request
$response = curl_exec($ch);

// Check for errors
if($response === FALSE){
    die(curl_error($ch));
}

echo $response;

// Decode the response
$responseData = json_decode($response, TRUE);

// Print the date from the response
print_r( $responseData );
