#!/bin/sh

if test $OSTYPE = 'HP-UX' ; then

# hostid and pid are not availible on hp, but uname -i 
# and awk are. 
#
# dec2hex is a program that is written to perform
# conversion from decimal to hexadecimal representation.
# It should be present in the same directory as this
# file.
#  gcc -o dec2hex dec2hex.c

  ../tmpasswd 1997 12 31 1 $HOST `uname -i` > .license ;
  TMHOME=.
  export TMHOME
  ../client
  ../rpc.toolmaker .license &
  echo waiting 70 seconds...
  sleep 70
  ../client
  kill `ps -e | grep rpc.toolmaker | awk '{print $1}'`
else 
  ../tmpasswd 1997 12 31 1 $HOST `hostid` > .license ;
  TMHOME=.
  export TMHOME
  ../client
  ../rpc.toolmaker .license &
  echo waiting 70 seconds...
  sleep 70
  ../client
  kill `pid rpc.toolmaker`
fi
../client

