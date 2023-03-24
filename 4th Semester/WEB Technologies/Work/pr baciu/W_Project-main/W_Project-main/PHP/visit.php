<?php
$db = mysqli_connect('localhost', 'root', '', 'accounts');

$username = mysqli_real_escape_string($db, $_POST['username'] );
$email = mysqli_real_escape_string($db, $_POST['email']);
$number = mysqli_real_escape_string($db, $_POST['number']);
$persons = mysqli_real_escape_string($db, $_POST['persons']);


if(mysqli_query($db, "INSERT INTO customers(name, email, number, persons) VALUES('$username','$email','$number','$persons')")) {
    echo 'Reservation complete';
} else {
    echo "Error: ". mysqli_error($db);
}


?>