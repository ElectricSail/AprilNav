!#bash/bin

##### Constants
TITLE="System Information for $HOSTNAME:"
RIGHT_NOW=$(date +"%x %r %Z")
TIME_STAMP="Updated on $RIGHT_NOW by $USER"

echo $TITLE
echo $RIGHT_NOW
echo $TIME_STAMP
echo

doubleterminal=false


if [ $# -gt 0 ]; then
    echo -e "Your command line contains $# arguments"
else
    echo "Your command line contains no arguments"
fi

echo
echo "You start with $# positional parameters"
echo

# Loop until all parameters are used up
while [ "$1" != "" ]; do
    echo "Parameter 1 equals $1"
    echo "You now have $# positional parameters"
    if [ "$1" == "-h" ]; then
      echo "    -h : help"
      echo "    -d : double terminal"
    elif [ "$1" == "-d" ]; then
      doubleterminal=true
      echo -e "\e[96m Double Terminal Activated \e[97m"
      if [ "$doubleterminal" = true ]; then
        echo "ADKHAKGHAGSASGASGSAGASG"
      fi
    else
      echo -e "\033[31m $1 is Not an accepted argument, -h for accepted options \e[97m"
      break
    fi

    # Shift all the parameters down by one
    shift
done


./build/bin/StarTracker -S .401 -X Calibration/BlackCamera.txt
