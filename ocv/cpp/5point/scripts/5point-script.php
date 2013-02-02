#!/usr/bin/php
<?
for($i=0; $i < 10; $i++) {
    for($j=0; $j < 10; $j++) {
        //echo "a$i$j : ratsimp(a$i$j);\n";

        for($k=0; $k < 4; $k++) {
            $file = "data/a$i${j}_$k.txt";
            //echo "stringout(\"$file\", coeff(a$i$j, z, $k));\n";

            $fp = fopen($file, "r") or die("Can't open $file\n");

            $line = fgets($fp); // blank
            $line = trim(fgets($fp));

            if($line == "0;") {
                continue;
            }

            // replace power of 2 with multiply
            $line = preg_replace("/(e..)\^2/", "$1*$1", $line);

            // replace power of 3 with multiply
            $line = preg_replace("/(e..)\^3/", "$1*$1*$1", $line);

            echo "M($i,$j)[$k] = $line\n";
        }
    }
}

?>
