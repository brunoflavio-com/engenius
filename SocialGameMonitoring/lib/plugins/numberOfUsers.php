#! /usr/bin/php
<?php
$read=fopen("/tmp/numberOfUsers.txt","r");
$value;
while(!feof($read))
  {
  $value = fgets($read). "<br>";
  }
fclose($read);

$client = new SoapClient('http://wvm008.dei.isep.ipp.pt:8000/SocialGameBLLService.svc?singleWsdl');
$result = $client->GetTotalNumberOfUsers();
$result->GetTotalNumberOfUsersResult;

if($value != $result->GetTotalNumberOfUsersResult){
    $write=fopen("/tmp/numberOfUsers.txt","w");
    fwrite($write, $result->GetTotalNumberOfUsersResult);
    fclose($write);
	$total = $result->GetTotalNumberOfUsersResult - $value;
    echo "SERVICE STATUS: ". $total . " New users";
exit(1);
}
else
    echo "SERVICE STATUS: No new users";
exit(0);

?>
