<?php

function testUserGraph() {
  // The data to send to the API
  $userGraph = array(
      'Relationships' => array(
	  array('RelationshipTagId' => 1,
		'Strenght' => 2,
		'UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test3@test.com'
		),
	  array('RelationshipTagId' => 2,
		'Strenght' => 5,
		'UserAEmail' => 'test2@test.com',
		'UserAEmail' => 'test3@test.com'
		),
	  array('RelationshipTagId' => 1,
		'Strenght' => 5,
		'UserAEmail' => 'test@test.com',
		'UserAEmail' => 'test2@test.com'
		),
	  ), 
      'Users'=> array(
	  array('Birthdate' => '0001-01-01T00:00:00',
		'Email' => 'test3@test.com',
		'FacebookProfile' => null,
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (
		    ),
		'LinkedInProfile' => null,
		'Name' => null,
		'PhoneNumber' => null,
		'Surname' => null
		),
	  array('Birthdate' => '0001-01-01T00:00:00',
		'Email' => 'test@test.com',
		'FacebookProfile' => null,
		'HumourStatusId'  => 1,
		'InterestsIDs' => array ( 1
		    ),
		'LinkedInProfile' => null,
		'Name' => null,
		'PhoneNumber' => null,
		'Surname' => null
		),
	  array('Birthdate' => '0001-01-01T00:00:00',
		'Email' => 'test2@test.com',
		'FacebookProfile' => null,
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (
		    ),
		'LinkedInProfile' => null,
		'Name' => null,
		'PhoneNumber' => null,
		'Surname' => null
		)
      )
  );

  // Setup cURL
  $ch = curl_init('http://localhost:5000/loadusergraph');
  curl_setopt_array($ch, array(
      CURLOPT_POST => TRUE,
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_HTTPHEADER => array(
	  'Content-Type: application/json'
      ),
      CURLOPT_POSTFIELDS => json_encode($userGraph, JSON_PRETTY_PRINT)
  ));

  echo "Sent object:" . json_encode($userGraph, JSON_PRETTY_PRINT) . "\n\n";
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
}

testUserGraph();