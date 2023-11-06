#!/bin/bash
echo "Implementing: $0"
echo "PPID of count.sh: "
ps -ef | grep count.sh
cleanup() {
echo "count.sh has stopped"
exit 1
}
trap cleanup INT
i=1
while [ $i -le $1 ]
do
echo $i >> count.txt
i=$((i + 1))
sleep 1
done
