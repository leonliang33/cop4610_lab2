#!/bin/bash

LISTLEN=10000
TESTFILE=./bashpipingtest
TESTFILE2=./bashtest2

for i in `seq 1 $LISTLEN`
do
	echo "YOUR TEST FACE x$i TIMES" >> $TESTFILE
	echo "ANOTHER TEST x$i" >> $TESTFILE2
	echo "MORE STUFF x$i TIMES" >> $TESTFILE
	echo "ONE MORE x$i TIMES" >> $TESTFILE
done

TESTSIZE=$(stat -c%s "$TESTFILE")
TESTSIZE2=$(stat -c%s "$TESTFILE2")

echo "Added $LISTLEN x 2 lines to test file, $TESTFILE"
echo "This file is now $TESTSIZE bytes."

echo "Also added $LISTLEN lines to a second test file, $TESTFILE2"
echo "This alternate test file is now $TESTSIZE2 bytes."
