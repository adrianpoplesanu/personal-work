<?php
    $string = "beautiful";
    $time = "winter";

    $str = 'This is a $string $time morning!';
    echo $str . "\n";
    
    eval("\$str = \"$str\";");
    echo $str . "\n";

    $str2 = 'aaa';
    eval("\$str2 = \"bbb\";");

    echo $str2 . "\n";

    eval("\$str2 = \$str;");
    echo $str2 . "\n";

    $str3 = "This is a $string $time $time morning!";
    echo $str3 . "\n";

    $str4 = "$str2";
    echo $str4. "\n";
?>
