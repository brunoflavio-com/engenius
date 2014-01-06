<?php
require_once 'HTTP/Request2.php';
require_once 'HTTP/Request2/CookieJar.php';

function testUserGraph() {
  // The data to send to the API
  $userGraph = array(
      'Users'=> array(
	  array(
		'Email' => 'test3@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,2,3,4
		    ),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1
		    ),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test2@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		)
      ),
      'Relationships' => array(
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 2
		),
	  array('UserAEmail' => 'test2@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 2,
		'Strength' => 5
		),
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test2@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 5
		),
      ),
      'Interests' => array(),
      'RelationshipTags' => array(),
      'HumourStatus' => array()
  );

  $cookieJar = new HTTP_Request2_CookieJar();
  
  $request = new HTTP_Request2('http://localhost:5000/loadusergraph');
  $request->setMethod(HTTP_Request2::METHOD_POST)
    ->setHeader('Content-Type: application/json')
    ->setBody(json_encode($userGraph, JSON_PRETTY_PRINT));
  $request->setCookieJar($cookieJar);

  //echo "Sent object:" . json_encode($userGraph, JSON_PRETTY_PRINT) . "\n\n";
  // Send the request
  $response = $request->send();  

  //echo $response->getBody();

  echo "Requesting the user graph:\n";
  $request2 = new HTTP_Request2('http://localhost:5000/getusergraph');
  $request2->setMethod(HTTP_Request2::METHOD_GET);
  $request2->setCookieJar($cookieJar);
  $response2 = $request2->send();
  $rcvUserGraph = json_decode($response2->getBody());
  
  //echo json_encode($rcvUserGraph, JSON_PRETTY_PRINT)."\n";
  
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
  echo "\n\n\n";
}

function testFriendsWithCommonInterests() {
  // The data to send to the API
  $userGraph = array(
      'Users'=> array(
	  array(
		'Email' => 'test3@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,2,3,4
		    ),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,4),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test2@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (2,3),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		)
      ),
      'Relationships' => array(
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 2
		),
	  array('UserAEmail' => 'test2@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 2,
		'Strength' => 5
		),
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test2@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 5
		),
      ),
      'Interests' => array(),
      'RelationshipTags' => array(),
      'HumourStatus' => array()
  );

  $cookieJar = new HTTP_Request2_CookieJar();
  
  $request = new HTTP_Request2('http://localhost:5000/loadusergraph');
  $request->setMethod(HTTP_Request2::METHOD_POST)
    ->setHeader('Content-Type: application/json')
    ->setBody(json_encode($userGraph, JSON_PRETTY_PRINT));
  $request->setCookieJar($cookieJar);

  //echo "Sent object:" . json_encode($userGraph, JSON_PRETTY_PRINT) . "\n\n";
  // Send the request
  $response = $request->send();  

  //echo $response->getBody();

  
  
  $interests = array(2,3);
  $expected_users = array('test2@test.com','test3@test.com');
  
  echo "Requesting users with these interests in common:\n";
  print_r($interests);
  
  $request2 = new HTTP_Request2('http://localhost:5000/getfriendswithcommoninterests');
  $request2->setMethod(HTTP_Request2::METHOD_POST)
    ->setHeader('Content-Type: application/json')
    ->setBody(json_encode($interests, JSON_PRETTY_PRINT));
  $request2->setCookieJar($cookieJar);
  $response2 = $request2->send();
  $rcvUserList = json_decode($response2->getBody());
  
  echo "#######################################################\n";
  echo "Check if received users matches the ones we expect:";
  
  sort($expected_users);
  sort($rcvUserList);
  if($expected_users == $rcvUserList) {
      echo "YES!\n";
  } else {
      echo "NO <------------\n";
  }
  echo "\n\n\n";
}

function testStats() {
  // The data to send to the API
  $userGraph = array(
      'Users'=> array(
	  array(
		'Email' => 'test3@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,2,3,4
		    ),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (1,4),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		),
	array(
		'Email' => 'test2@test.com',
		'Name' => null,
		'Surname' => null,
		'Birthdate' => '0001-01-01T00:00:00',
		'HumourStatusId'  => 1,
		'InterestsIDs' => array (2,3),
		'PhoneNumber' => null,
		'LinkedInProfile' => null,
		'FacebookProfile' => null,		
		)
      ),
      'Relationships' => array(
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 2
		),
	  array('UserAEmail' => 'test2@test.com',
		'UserBEmail' => 'test3@test.com',
		'RelationshipTagId' => 2,
		'Strength' => 5
		),
	  array('UserAEmail' => 'test@test.com',
		'UserBEmail' => 'test2@test.com',
		'RelationshipTagId' => 1,
		'Strength' => 5
		),
      ),
      'Interests' => array(),
      'RelationshipTags' => array(),
      'HumourStatus' => array()
  );

  $cookieJar = new HTTP_Request2_CookieJar();
  
  $request = new HTTP_Request2('http://localhost:5000/loadusergraph');
  $request->setMethod(HTTP_Request2::METHOD_POST)
    ->setHeader('Content-Type: application/json')
    ->setBody(json_encode($userGraph, JSON_PRETTY_PRINT));
  $request->setCookieJar($cookieJar);

  //echo "Sent object:" . json_encode($userGraph, JSON_PRETTY_PRINT) . "\n\n";
  // Send the request
  $response = $request->send();  

  //echo $response->getBody();

  
  
  
  echo "Requesting graph stats:\n";
  
  $request2 = new HTTP_Request2('http://localhost:5000/getgraphstats');
  $request2->setMethod(HTTP_Request2::METHOD_GET);
  $request2->setCookieJar($cookieJar);
  $response2 = $request2->send();
  $rcvStats = json_decode($response2->getBody(),true);
  print_r($rcvStats);
  
  echo "#######################################################\n";
  echo "Check if received users matches the ones we expect:";
  
  $expected_total = 2;
  $expected_average = 4;
 
  if($expected_total == $rcvStats['TotalFriends'] &&
          $expected_average == $rcvStats['AverageStrength']) {
      echo "YES!\n";
  } else {
      echo "NO <------------\n";
  }
  echo "\n\n\n";
}

testUserGraph();

testFriendsWithCommonInterests();

testStats();
