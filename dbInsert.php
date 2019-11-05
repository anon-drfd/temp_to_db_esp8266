<?php
// Database parameters
$host = "localhost";
$user = "root";
$password = "12345678";
$dbname = "espdemo";

// Create connection
$con = new mysqli($host, $user, $password,$dbname);

// Check connection
if ($con->connect_error) {
die("Connection failed: " . $con->connect_error);
}

// Get current date and time
date_default_timezone_set('Asia/Kuala_Lumpur');
$d = date("Y-m-d");
$t = date("H:i:s");

// Hold value that is sent from NodeMCU
$tempValue = $_POST['tempValue'];

// Check if value is not empty, insert value in the table
if (!empty($_POST['tempValue']))
{
$tempValue = $_POST['tempValue'];
$sql = "INSERT INTO temperaturetable (Date, Time, tempValue) VALUES ('".$d."', '".$t."','".$tempValue."')";
if ($con->query($sql) === TRUE)
{
echo "OK";
}
else
{
echo "Error: " . $sql . "<br>" . $con->error;
}
}

// Close database connection
$con->close();
?>