<?php
require_once 'HTTP/Request2.php';
require_once 'HTTP/Request2/CookieJar.php';

function testUserGraph() {
  // The data to send to the API
  $userGraph = array(
      'HumourStatus' => array(
			  array(
			      'Id' => 1,
			      'Name' => 'Normal'
			      )
		     ),
		     
      'Interests' => array(),
      
      'Relationships' => array(
	  array('RelationshipTagId' => 1,
		'Strength' => 2,
		'UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test3@test.com'
		),
	  array('RelationshipTagId' => 2,
		'Strength' => 5,
		'UserAEmail' => 'test2@test.com',
		'UserBEmail' => 'test3@test.com'
		),
	  array('RelationshipTagId' => 1,
		'Strength' => 5,
		'UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test2@test.com'
		),
	  ), 
	  
      'Users'=> array(
	  array('Birthdate' => '0001-01-01T00:00:00',
		'Email' => 'test3@test.com',
		'FacebookProfile' => null,
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,2,3,4
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

  $cookieJar = new HTTP_Request2_CookieJar();
  
  $request = new HTTP_Request2('http://localhost:5000/loadusergraph');
  $request->setMethod(HTTP_Request2::METHOD_POST)
    ->setHeader('Content-Type: application/json')
    ->setBody(json_encode($userGraph, JSON_PRETTY_PRINT));
  $request->setCookieJar($cookieJar);

  echo "Sent object:" . json_encode($userGraph, JSON_PRETTY_PRINT) . "\n\n";
  // Send the request
  $response = $request->send();  

  echo $response->getBody();

  echo "Requesting the user graph:\n";
  $request2 = new HTTP_Request2('http://localhost:5000/getusergraph');
  $request2->setMethod(HTTP_Request2::METHOD_GET);
  $request2->setCookieJar($cookieJar);
  $response2 = $request2->send();
  $rcvUserGraph = json_decode($response2->getBody());
  
  echo json_encode($rcvUserGraph, JSON_PRETTY_PRINT)."\n";
  
  echo "#######################################################\n";
  echo "Check if received userGraph matches the one we expect:";
  $userGraph['HumourStatus'] = array();
  $userGraph['Interests'] = array();
  
  if(json_encode($userGraph, JSON_PRETTY_PRINT) 
          === json_encode($rcvUserGraph, JSON_PRETTY_PRINT)) {
      echo "YES!\n";
  } else {
      echo "NO <------------\n";
  }
}

testUserGraph();
