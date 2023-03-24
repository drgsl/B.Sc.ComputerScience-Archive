<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../CSS/animals.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <title>Animals</title>
</head>
<body>

<header class="header">
    <!-- Logo -->
    <a href="index.php" class="logo" target="_self">Furry Park</a>
    <!-- Hamburger icon -->
    <input class="side-menu" type="checkbox" id="side-menu"/>
    <label class="hamb" for="side-menu"><span class="hamb-line"></span></label>
    <!-- Menu -->
    <nav class="nav">
        <ul class="menu">
            <li><a href="../HTML/visit.html">Visit Us</a></li>
            <li><a href="../HTML/donate.html">Donate</a></li>
            <li><a href="animals.php">Animals</a></li>
        </ul>
    </nav>
</header>

<script src="../JAVASCRIPT/api.js"></script>

<div class="poze">
    <?php

    $animal_id = $_GET['species'];

    echo "<style>";
    include '../CSS/an.temp.css';
    echo "</style>";

    $db = mysqli_connect('localhost', 'root', '', 'accounts');
    $query = "SELECT * FROM animals WHERE species = '$animal_id' ";
    $result = $db->query($query);
    $row = $result->fetch_assoc();
    while ($row) {
        echo

            "<div class='chenar'>" .
            "<img src=" . $row['path'] . " class= 'pozeanimale'>";

        if ($row['endangered'] == 1)
            echo "<div class = 'bucati'>
                 <div class = 'text'>" . "<h2>Endangered : </h2>" . "</div>" .
                "<div class = 'info_anim' > Yes <br>" . "</div>" .
                "</div>";
        else echo "<div class = 'bucati'>
                <div class = 'text'>" . "<h2>Endangered : </h2>" . "</div>" .
            "<div class = 'info_anim' > No <br>" . "</div>" .
            "</div>";
        echo "<div class = 'bucati'>" .

            "<div class = 'text'>" . "<h2>Species : </h2>" . "</div>" .
            "<div class = 'info_anim' >" . $row["species"] . "<br>" . "</div>" .
            "</div>" .

            "<div class = 'bucati'>" .
            "<div class = 'text'>" . "<h2>Scientific name : </h2>" . "</div>" .
            "<div class = 'info_anim' >" . $row["scientific"] . "<br>" . "</div>" .
            "</div>" .


            "<div class = 'bucati'>" .
            "<div class = 'text'>" . "<h2>Type : </h2>" . "</div>" .
            "<div class = 'info_anim' >" . $row["type"] . "<br>" . "</div>" .
            "</div>" .

            "<div class = 'bucati'>" .
            "<div class = 'text'>" . "<h2>Lifespan : </h2>" . "</div>" .
            "<div class = 'info_anim' >" . $row["lifespan"] . "<br>" . "</div>" .
            "</div>" .

            "<div class = 'bucati2'>" .
            "<div class = 'text'>" . "<h2>Infos : </h2>" . "</div>" .
            "<div class = 'info' >" . $row["description"] . "<br>" . "</div>" .
            "</div>" .

            "<div class = 'bucati2'>" .
            "<div class = 'text'>" . "<h2>Habitat : </h2>" . "</div>" .
            "<div class = 'info' >" . $row["habitat"] . "<br>" . "</div>" .
            "</div>" .

            "<div class = 'bucati2'>" .
                "<div class = 'text'>" . "<h2>Diet : </h2>" . "</div>" .
                "<div class = 'info_anim' >" . $row["diet"] . "<br>" . "</div>" .
            "</div>" .
//php apeleaza in 2 locuri css uri diferite
            "<div class = 'button'>" .
            "<a href ='exportJSON.php?species=" . $row["species"] . "' target = '_self' >" . "Export JSON" . "</a>" .
            "</div>" .

            "<div class = 'button'>" .
            "<a href ='exportXML.php?species=" . $row["species"] . "' >" . "Export XML" . "</a>" .
            "</div>" .

            "</div>";


        $row = $result->fetch_assoc();


    }
    ?>
</div>
</body>
</html>