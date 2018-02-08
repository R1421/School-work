<?php

/* 
 * Vivo Applications
 * 
 * Common PHP used in Crypto
 */

if (!isset($_SESSION))
    session_start();

/* Redirects the page to start.php if the user isn't logged in. */
function ensure_logged_in() {
    if (!isset($_SESSION["name"]))
        redirect("index", "You must log in before you can view that page.");
}

/* Redirects the page to todolist.php if the user is logged in. */
function ensure_logged_out() {
    if (isset($_SESSION["name"]))
        redirect("versus", "You are already logged in.");
}

/* Returns a new PDO object with the error attributes set. */
function makePDO() {
    $db = new PDO("mysql:dbname=Names;host=localhost;charset=utf8", 
                                  "root", "!8phcibdRk2h");     
    # For descriptive SQL error messages.
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    return $db;
}

/* Prints the footer html for each page. */
function printFooter() {
?>      
        <footer>
            <a href="about-us">About Us</a>
            <p>&#9830</p>
            <a href="contact-us">Contact Us</a>
        </footer>
    </body>
</html>
<?php
}

/* Prints the header html for each page. */
function printHeader($title, $description, $keywords, $cssfiles = null, $jsfiles = null) {
    ?>
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <meta name="description" content=<?php echo "'" . $description . "'" ?>>
            <meta name="keywords" content=<?php echo "'" . $keywords . "'" ?>>
            <meta name="author" content="Vivo Applications">
            <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0"/>
            <title><?= $title ?></title>
            <script type="text/javascript" src="http://code.jquery.com/jquery-latest.min.js"></script>
            <script>
            $.noConflict();
            </script>
            <?php
            if ($cssfiles != null) {
                foreach ($cssfiles as $cssfile) {
                    ?>
                    <link href=<?= $cssfile ?> type="text/css" rel="stylesheet" />
                    <?php
                }
            }

            if ($jsfiles != null) {
                foreach ($jsfiles as $jsfile) {
                    ?>
                    <script src=<?= $jsfile ?> type="text/javascript"></script>
                    <?php
                }
            }
            ?>
            
            <link rel="icon" type="image/png" href="images/crypto_logo_black.svg">
        </head>
        <body>
    <?php
}

/* Prints the navbar html. */
function printNavbar() {
    ?>
    <nav>
        <input type="checkbox" id="button">
        <label for="button" onclick></label>
        
        <ul>
            <div id="crypto_logo_nav">
                <a href="index">
                    <img src="images/crypto_logo_white.svg" alt="Crypto" width="40px" height="40px" />
                </a>
            </div>
            <a href="training">
                <li id="nav_training" class="nav_item"><img src="images/training.svg" alt="playground" width="25px" height="25px" />
                Training</li>
            </a>
            <a href="playground">
                <li id="nav_playground" class="nav_item">
                <img src="images/playground.svg" alt="playground" width="25px" height="25px" />
                Playground
                </li>
            </a>
            <a href="versus">
                <li id="nav_versus" class="nav_item">
                <img src="images/versus.svg" alt="versus" width="25px" height="25px" />
                Versus
                </li>
            </a>
            <a href="profile">
                <li id="nav_profile" class="nav_item">
                <img src="images/profile.svg" alt="profile" width="25px" height="25px" /> 
                Profile 
                </li>
            </a>
            <?php
              $user = $_SESSION["name"];
            ?>
            <a href="profile">
                <li id="hello_user" class="hello_item">
                hello, <?php echo $user; ?>!
                </li>
            </a>
            <a href="logout">
                <li id="nav_logout" class="nav_item">Logout</li>
            </a>
        </ul>
    </nav>
    <?php
}

/* Shorthand for redirecting to another page with an optional flash message. */
function redirect($url, $flash_message = NULL) {
    if ($flash_message) {
        $_SESSION["flash"] = $flash_message;
    }
    header("Location: $url");
    die();
}
