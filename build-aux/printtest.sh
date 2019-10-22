#!/bin/sh
for logfile in `ls -1 test_*.log`; do cat $logfile | ~/go/bin/tap2junit; echo ""; done
