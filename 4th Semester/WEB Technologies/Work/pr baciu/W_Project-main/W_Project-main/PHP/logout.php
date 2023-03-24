<?php

if (isset($_COOKIE['user'])) {
    unset($_COOKIE['user']);
    setcookie('user', '', time() - 800000, '/');
    header('location:index.php');
}
