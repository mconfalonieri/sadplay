#!/bin/sh
for logfile in `ls -1 test_*.log`; do tap2junit $file $file.xml; cat $file.xml; done