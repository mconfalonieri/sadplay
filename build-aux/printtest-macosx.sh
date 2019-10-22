#!/bin/sh
for logfile in `ls -1 test_*.log`; do
    cat $logfile | tap2junit > $logfile.xml
done
