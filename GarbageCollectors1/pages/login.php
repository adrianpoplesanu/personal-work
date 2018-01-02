<?php
include_once($_SERVER['DOCUMENT_ROOT'] . "/GarbageCollectors1/config.php");
include_once($MODEL_ROOT . 'login_adapter.php');
session_start();
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $login_adapter = new LoginAdapter();
    if ($login_adapter->validate($username, $password)) {
        $_SESSION['USERNAME'] = $username;
        header("Location: index.php");
        exit();
    } else {
        $_SESSION['LOGIN_ERROR'] = "Username or password incorrect";
        header("Location: login.php");
    }
} else {
?>
<html>
<head>
    <title>GarbageCollector ver 1.0</title>
    <link rel="stylesheet" href="<?php echo($AHOST); ?>css/bootstrap.min.css">
    <link rel="stylesheet" href="<?php echo($AHOST); ?>css/login.css">
    <script src="<?php echo($AHOST); ?>js/jquery.min.js"></script>
    <script src="<?php echo($AHOST); ?>js/bootstrap.min.js"></script>
    <script src="<?php echo($AHOST); ?>js/login.js"></script>
</head>
<body>
    <div class="col-md-4 col-md-offset-4 text-center">
        <div class="search-box">
            <div class="caption">
                <h3>Garbage Collectors v1.0</h3>
            </div>
            <form method="POST" class="login-form">
                    <input type="text" id="username" name="username" class="form-control" placeholder="Username">
                    <input type="password" id="password" name="password" class="form-control" placeholder="Parola">
                    <input type="submit" id="submit" class="form-control" value="Conectare">
            </form>
            <?php if (isset($_SESSION['LOGIN_ERROR'])) {
                unset ($_SESSION['LOGIN_ERROR']);
            ?>
                <div id="error-login">Username sau parola incorecte</div>
            <?php } ?>
        </div>
    </div>
</body>
</html>
<?php
}
?>