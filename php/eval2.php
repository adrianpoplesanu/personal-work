<?php
    $string = "beautiful";
    $time = "winter";

    $str = 'This is a $string $time morning!';
    echo $str . "\n";
    
    eval("\$str = \"$str\";");
    echo $str . "\n";

    $str2 = 'This is a $string $time morning!';
    echo $str2 . "\n";

    $str2 = "$str2";
    echo $str2. "\n";
?>
