#!/bin/bash

function test() {
    ./main < tests/in$1 > tests/mout$1
    echo $1
    diff tests/out$1 tests/mout$1
}

function valgrind_test() {
    valgrind --leak-check=full ./main < tests/in$1
}

test 5
test 6 
test 7
test 8
test 9

exit 0


