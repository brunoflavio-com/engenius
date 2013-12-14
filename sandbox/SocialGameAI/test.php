<?php

// The data to send to the API
$postData = array(
    'conn' => array(
        array('ori' =>'bmflavio@gmail.com','des' => 'id@email.pt'),
        array('ori' =>'1','des' => '98'),
        array('ori' =>'2','des' => '101'),
        array('ori' =>'3','des' => '98'),
        array('ori' =>'4','des' => '1001'),
        array('ori' =>'99','des' => '989'),
        array('ori' =>'100','des' => '1801'),
        array('ori' =>'939','des' => '978'),
        array('ori' =>'1010','des' => '1601'),
        array('ori' =>'909','des' => '985'),
        array('ori' =>'10110','des' => '1401'),
        array('ori' =>'969','des' => '983'),
        array('ori' =>'1070','des' => '1021'),
        array('ori' =>'939','des' => '981'),
        
        ), 
    'method'=> 'insert'
);

// Setup cURL
$ch = curl_init('http://localhost:5000/parsejson');
curl_setopt_array($ch, array(
    CURLOPT_POST => TRUE,
    CURLOPT_RETURNTRANSFER => TRUE,
    CURLOPT_HTTPHEADER => array(
        'Content-Type: application/json'
    ),
    CURLOPT_POSTFIELDS => json_encode($postData, JSON_PRETTY_PRINT)
));

echo "Sent object:" . json_encode($postData, JSON_PRETTY_PRINT) . "\n\n";
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
