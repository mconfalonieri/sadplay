#!/bin/sh
for logfile in `ls -1 test_*.log`; do tap2junit $logfile $logfile.xml; cat $logfile.xml; done