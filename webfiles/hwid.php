<?php
$link = mysqli_connect("database_host", "database_user","database_password");
$database = mysqli_select_db($link, "database_name");

$user = $_GET['username'];
$storedtoken = '1337';
$token = $_GET['token'];
$hwid = mysqli_real_escape_string($link, $_GET['hwid']);
$tables = "xf_user";

$sql = "SELECT * FROM ". $tables ." WHERE username = '". mysqli_real_escape_string($link,$user) ."'" ;
$result = $link->query($sql);

if ($result->num_rows > 0) {
    // Outputting the rows
    while($row = $result->fetch_assoc())
    {
        function Redirect($url, $permanent = false)
        {
            if (headers_sent() === false)
            {
                header('Location: ' . $url, true, ($permanent === true) ? 301 : 302);
            }
        exit();
        }
		
		if($token != $storedtoken){
			return;
		}

        if (strlen($row['hwid']) > 1)
        {
            if ($hwid != $row['hwid'])
            {
                echo 'declined';
            }
            else
            {
                echo 'accepted';
            }
        }
        else
        {
            $sql = "UPDATE ". $tables ." SET hwid='$hwid' WHERE username='$user'";
            if(mysqli_query($link, $sql))
            {
                echo 'new';
            }
            else
            {
                echo 'error';
            }
        }
    }
}  
?>
