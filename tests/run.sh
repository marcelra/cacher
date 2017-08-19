BASEDIR=$(dirname $(realpath "$0"))
echo $BASEDIR
PATHTOBIN=$BASEDIR/../bin
LOGFILE=$PATHTOBIN/../log/server.out
touch $LOGFILE
echo $PATHTOBIN
xterm -e tail -f $PATHTOBIN/../log/server.out &
$PATHTOBIN/server > $LOGFILE &
$PATHTOBIN/client
kill -15 %1
kill -15 %2
exit
