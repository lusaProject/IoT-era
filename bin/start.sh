#!/bin/bash

echo "kill"
killall nginx

echo "start nginx"
./nginx -p ../esdata -c conf/nginx.conf

echo "netstat"
netstat -anlutp
