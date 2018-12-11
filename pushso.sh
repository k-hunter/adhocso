#!/bin/bash
adb shell
mkdir -p /data/adhoc
exit 
adb push adhocyaya.so /data/adhoc/
adb shell 
chmod 777 /data/adhoc/adhocyaya.so
exit 



