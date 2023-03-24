<?php

$db = mysqli_connect('localhost', 'root', '', 'accounts');

$file = $_GET["myfile"];
$ext = pathinfo($file, PATHINFO_EXTENSION);
if ($ext == 'json') //json
{


    $jsondata = file_get_contents('../XML_JSON/' . $file);
    $data = json_decode($jsondata, true);

    $species = $data['species'];
    $animal_check_query = "SELECT species FROM animals WHERE species='$species' LIMIT 1";
    $result = mysqli_query($db, $animal_check_query);
    $animal = mysqli_fetch_assoc($result);
    if (!$animal) {
        $scientific = $data['scientific'];
        $type = $data['type'];
        $lifespan = $data['lifespan'];
        $description = $data['description'];
        $habitat= $data['habitat'];
        $diet = $data['diet'];
        $diet_filter = $data['diet_filter'];
        $habitat_filter = $data['habitat_filter'];
        $endangered = $data['endangered'];
        $path = $data ['path'];


        $inj = $db->prepare("INSERT INTO animals (species ,scientific, type, lifespan, description, habitat, diet, diet_filter,
                     habitat_filter,endangered, path)  VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        $inj->bind_param("sssssssssss", $species,$scientific, $type,$lifespan,$description, $habitat, $diet, $diet_filter,
            $habitat_filter,$endangered, $path);
        $inj->execute();
        header("location:animals.php");

        //echo $data['species'];
    } else echo "Species already exists";
} else //xml
{
    $animalinfo = simplexml_load_file('../XML_JSON/' . $file) or die("Error: Cannot create XML object");

    $species = $animalinfo->species;
    $animal_check_query = "SELECT species FROM animals WHERE species='$species' LIMIT 1";
    $result = mysqli_query($db, $animal_check_query);
    $animal = mysqli_fetch_assoc($result);
    if (!$animal) {
        $scientific = $animalinfo->scientific;
        $type = $animalinfo->type;
        $lifespan = $animalinfo->lifespan;
        $description = $animalinfo->description;
        $habitat = $animalinfo->habitat;
        $diet = $animalinfo->diet;
        $diet_filter = $animalinfo->diet_filter;
        $habitat_filter = $animalinfo->habitat_filter;
        $endangered = $animalinfo->endangered;
        $path = $animalinfo->path;


        $inj = $db->prepare("INSERT INTO animals (species ,scientific, type, lifespan, description, habitat, diet, diet_filter,
                     habitat_filter,endangered, path)  VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        $inj->bind_param("sssssssssss", $species,$scientific, $type,$lifespan,$description, $habitat, $diet, $diet_filter,
                  $habitat_filter,$endangered, $path);
        $inj->execute();
        header("location:animals.php");
    } else echo "Species already exists";

}