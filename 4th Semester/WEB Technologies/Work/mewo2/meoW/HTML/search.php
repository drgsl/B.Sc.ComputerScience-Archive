<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link href="https://fonts.googleapis.com/css2?family=Nunito:ital,wght@0,200;1,200&display=swap" rel="stylesheet">
    <title>MeoW</title>
    <link href="../CSS/search.css" rel="stylesheet">
</head>

<body>
    <div class="div-body">
        <div id="nav-background">
            <div id="nav-container">
                <header id="nav-header">
                    <h1><a class="nav-logo-function" href="index.html#home" id="nav-logo">

                            MeoW
                        </a></h1>
                    <img src="https://i.imgur.com/xcFvxAK.png" class="hamburger-img" id="nav-menu-button">
                </header>
                <nav>
                    <ul id="navv" class="nav-ul hide-ul">
                        <li><a class="nav-link" href="index.html#about">About Us</a></li>
                        <li><a class="nav-link" href="index.html#contact">Contact</a></li>
                        <li><a class="nav-link" href="../HTML/search.html">Animals</a></li>
                        <li><a class="nav-link" href="../HTML/login.html">Login</a></li>
                    </ul>
                </nav>
            </div>
        </div>
        <div class="page">
            <div class="left">
                <div class="title"> Filter </div>
                <form action="" method="post">
                    <div class="subtitle"> <b class="susbtitle1"> Region: </b> <br></div>
                    <select name="Region">
                        <option value=""></option>
                        <?php
                        $db = mysqli_connect('localhost', 'root', '', 'tw');
                        $query = "SELECT DISTINCT region FROM animals ";
                        $result = $db->query($query);
                        $row = $result->fetch_assoc();
                        while ($row) {
                            echo "<option value=" . $row['region'] . ">" . $row['region'] . "</option>";
                            $row = $result->fetch_assoc();
                        }
                        ?>
                    </select>


                    <div class="subtitle"> <b class="susbtitle1"> Habitat: </b><br></div>
                    <select name="Habitat">
                        <option value=""></option>
                        <?php
                        $db = mysqli_connect('localhost', 'root', '', 'tw');
                        $query = "SELECT DISTINCT habitat FROM animals ";
                        $result = $db->query($query);
                        $row = $result->fetch_assoc();
                        while ($row) {
                            echo "<option value=" . $row['habitat'] . ">" . $row['habitat'] . "</option>";
                            $row = $result->fetch_assoc();
                        }
                        ?>
                    </select>


                    <div class="subtitle"> <b class="susbtitle1"> Type: </b><br></div>
                    <select name="Type">
                        <option value=""></option>
                        <?php
                        $db = mysqli_connect('localhost', 'root', '', 'tw');
                        $query = "SELECT DISTINCT tip FROM animals ";
                        $result = $db->query($query);
                        $row = $result->fetch_assoc();
                        while ($row) {
                            echo "<option value=" . $row['tip'] . ">" . $row['tip'] . "</option>";
                            $row = $result->fetch_assoc();
                        }
                        ?>
                    </select>


                    <div class="subtitle"> <b class="susbtitle1"> Conservation: </b><br></div>
                    <select name="Conservation">
                        <option value=""></option>
                        <?php
                        $db = mysqli_connect('localhost', 'root', '', 'tw');
                        $query = "SELECT DISTINCT conservation FROM animals ";
                        $result = $db->query($query);
                        $row = $result->fetch_assoc();
                        while ($row) {
                            echo "<option value=" . $row['conservation'] . ">" . $row['conservation'] . "</option>";
                            $row = $result->fetch_assoc();
                        }
                        ?>
                    </select>


                    <input class="submitFilter" type="submit" name="submit" value="Filter">
                </form>

            </div>
            <div class="right">
                <div class="search-section">
                    <input type="text" id="searchbar" class="search-input" placeholder="search by name">
                    <button class="search-button" type="button" value="Search">All animals</button>
                </div>

                <?php
                echo "<style>";
                include '../CSS/animals.css';
                echo "</style>";

                $db = mysqli_connect('localhost', 'root', '', 'tw');
                $ok = 0;
                $region = "";
                $habitat = "";
                $type = "";
                $conservation = "";
                if (isset($_POST['submit'])) {
                    if (!empty($_POST['Region'])) {
                        $region = "WHERE region='" . $_POST['Region'] . "' ";
                        $ok = 1;
                    }

                    if (!empty($_POST['Habitat'])) {
                        if ($ok == 1)
                            $habitat = "AND habitat='" . $_POST['Habitat'] . "' ";
                        else {
                            $habitat = "WHERE habitat='" . $_POST['Habitat'] . "' ";
                            $ok = 1;
                        }
                    }

                    if (!empty($_POST['Type'])) {
                        if ($ok == 1)
                            $type = "AND tip='" . $_POST['Type'] . "' ";
                        else {
                            $type = "WHERE tip='" . $_POST['Type'] . "' ";
                            $ok = 1;
                        }
                    }

                    if (!empty($_POST['Conservation'])) {
                        if ($ok == 1)
                            $conservation = "AND conservation='" . $_POST['Conservation'] . "' ";
                        else {
                            $conservation = "WHERE conservation='" . $_POST['Conservation'] . "' ";
                            $ok = 1;
                        }
                    }
                }
                $filterquery = "SELECT name, image FROM animals " . $region . $habitat . $type . $conservation . "ORDER BY name";
                //$query = "SELECT species,path FROM animals ORDER BY species";
                //echo $filterquery;
                $result = $db->query($filterquery);
                $row = $result->fetch_assoc();
                $nr = 0;
                echo "<div class='animal-section'>";
                
                while ($row) {
                    $nr++;
                    
                    if ($nr % 3 == 1)
                    echo "<div class='row' id='animalSection'>";
                        echo

                        "<div class='animal-container'>" .
                            // "<a href = '../PHP/animal_temp.php?species=" . $row['species'] . "' class = 'link_animale' >" .
                            "<a>" . "<img src=" . $row['image'] . "<' class = 'animal-img'>" .
                            "</a>" .

                            "<div class = 'name' >" . $row["name"] . "<br>" . "</div>" .

                            "</div>";


                    $row = $result->fetch_assoc();
                    if ($nr % 3 == 0 || !$row)
                        echo "</div>";
                }
               
                ?>
            </div>
        </div>
    </div> 

    <footer class="footer-reference">
        <br>
        <p>Authors: Bobu Dragos & Breahna Teodora & Zaharie Robert </p>
        <br>
        <p> <a href="doc.html"> Scholarly HTML Documentation </a></p>
    </footer>
    <script src="../JS/navbar.js"></script>

</body>

</html>