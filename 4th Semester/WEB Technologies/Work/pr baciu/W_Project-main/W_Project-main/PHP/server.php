<?php
session_start();
$username = "";
$email = "";
$errors = array();

// conexiunea la baza de date
$db = mysqli_connect('localhost', 'root', '', 'accounts');

//inregistrare
if (isset($_POST['reg_user'])) {
    // primim informatiile din form
    $username = mysqli_real_escape_string($db, $_POST['txtUsername']);
    $email = mysqli_real_escape_string($db, $_POST['txtMail']);
    $password_1 = mysqli_real_escape_string($db, $_POST['txtPassword']);
    $password_2 = mysqli_real_escape_string($db, $_POST['rpsw']);

    // verificam daca informatiile au fost introduse corect
    if (empty($username)) {
        array_push($errors, "Username is required");
    }
    if (empty($email)) {
        array_push($errors, "Email is required");
    }
    if (empty($password_1)) {
        array_push($errors, "Password is required");
    }
    if ($password_1 != $password_2) {
        array_push($errors, "The two passwords do not match");
    }

    // mai intai verificam baza de date pentru a vedea daca exista deja un user cu acelasi username si/sau parola
    $user_check_query = "SELECT * FROM users WHERE username='$username' OR email='$email' LIMIT 1";
    $result = mysqli_query($db, $user_check_query);
    $user = mysqli_fetch_assoc($result);

    if ($user) { // daca exista un user
        if ($user['username'] === $username) {
            array_push($errors, "Username already exists");
        }

        if ($user['email'] === $email) {
            array_push($errors, "email already exists");
        }
    }

    // daca nu exista erori se va inregistra userul
    if (count($errors) == 0) {
        $password = md5($password_1);//encriptam parola pentru securitate aditionala

        $inj = $db->prepare("INSERT INTO users (username, email, password)  VALUES (?, ?, ?)");
        $inj->bind_param("sss", $username, $email, $password);
        $inj->execute();

        $_SESSION['username'] = $username;
        $_SESSION['success'] = "You are now logged in";
        header('location:index.php');
    }
}

//login
if (isset($_POST['login_user'])) {
    $username = mysqli_real_escape_string($db, $_POST['txtUsername']);
    $password = mysqli_real_escape_string($db, $_POST['txtPassword']);

    if (empty($username)) {
        array_push($errors, "Username is required");
    }
    if (empty($password)) {
        array_push($errors, "Password is required");
    }

    if (count($errors) == 0) {
        $password = md5($password);
        $query = "SELECT * FROM users WHERE (username='$username' OR email='$username') AND password='$password'";
        $results = mysqli_query($db, $query);
        if (mysqli_num_rows($results) == 1) {
            $_SESSION['username'] = $username;
            $_SESSION['success'] = "You are now logged in";
            setcookie("user", $username, time() + (800000), '/');
            $_COOKIE['user'] = $username;
            header('location:index.php');
        } else {
            array_push($errors, "Wrong username/password combination");
        }
    }
}

//afisam fiecare eroare daca exista
if (count($errors) > 0) : ?>

    <?php foreach ($errors as $error) : ?>
        <p><?php echo $error ?></p>
    <?php endforeach ?>

<?php endif ?>

