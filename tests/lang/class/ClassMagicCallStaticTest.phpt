--TEST--
Class magic static call test
--FILE--
<?php

if (class_exists("\NonMagicMethodClass") && class_exists("\MagicMethodClass")) {
    // $NonMagicMethodClass::staticCalculateSum(12, 24, 48); // fata error
    $sum = MagicMethodClass::staticCalculateSum(12, 24, 48);
    echo "the sum is " . $sum ."\n";
    $ret = MagicMethodClass::notProcessCase("zapi");
    if (is_null($ret)) {
        echo "MagicMethodClass::notProcessCase('zapi') return null\n";
    }
}

?>
--EXPECT--
the sum is 84
MagicMethodClass::notProcessCase('zapi') return null