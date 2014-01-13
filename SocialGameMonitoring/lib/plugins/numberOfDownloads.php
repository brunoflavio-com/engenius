#!/usr/bin/php
<?php
$read=fopen("/tmp/downloads.txt","r");
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
    $write=fopen("/tmp/downloads.txt","w");
    fwrite($write, $result->GetTotalNumberOfUsersResult);
    fclose($write);
    $total = $result->GetTotalNumberOfUsersResult - $value;
echo "SERVICE STATUS: " . $total . " downloads in the past hour";
if($total>5){
	if($total>100)
		exit(2);
	exit(1);
}
    exit(0);
}
else
    echo "SERVICE STATUS: No downloads in the past hour";
    exit(0);
?>


