<?php
$db = mysqli_connect('localhost', 'root', '', 'tw');

$firstName= mysqli_real_escape_string($db, $_POST['firstName'] );
$lastName = mysqli_real_escape_string($db, $_POST['lastName']);
$country = mysqli_real_escape_string($db, $_POST['country']);
$subject = mysqli_real_escape_string($db, $_POST['subject']);


if(mysqli_query($db, "INSERT INTO feedback(firstName, lastName, country, subject) VALUES('$firstName','$lastName', '$country','$subject')")) {
    echo 'Thank you for your message';
} else {
    echo "Error: ". mysqli_error($db);
}


?>