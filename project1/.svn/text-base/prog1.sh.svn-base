#! /bin/sh
#Torben Rasmussen, Gabriel Condrea, Li Yiwei
dircount=0

#Check for 1-2 arguments
if [ $# -eq 0 -o $# -gt 2 ]
then
    echo "Usage: prog.sh [OPTION]... [DIRECTORY]..."
    exit
fi

#Check for valid options if there are two arguments
if [ $# -eq 2 -a $1 != "-c" ]
then
    echo "prog1.sh: Unrecognized option '$1'"
    exit
fi

#Set dir based on how many arguments there are
if [ $# -eq 2 ]
then
    dir=$2
else
    dir=$1
fi

#Exit if -c is the only argument
if [ $# -eq 1 -a $1 = "-c" ]
then
    echo "prog1.sh: missing operand"
    exit
fi

#Count # of directories if -c flag
if [ $1 = "-c" ]
then
    dircount=`echo $dir | grep -o / | wc -l`
    #Increment the dircount if file is a directory and last char isn't /
    if test -d $dir
    then
        if [ `echo $dir|awk '$0=$NF' FS=` != "/" ]
        then
            dircount=`expr $dircount + 1`
        fi
    fi
    echo $dircount
    exit
fi

#Special case for only one slash
if [ $dir = "/" ]
then
    echo $dir
    exit
fi

#Special case for no slash
if [ `echo $dir|grep -o / | wc -c` = "0" ]
then
    echo "."
    exit
fi

#Check if the final character is a / and remove it
if [ `echo $dir|awk '$0=$NF' FS=` = "/" ]
then
    dir=`echo $dir|sed s/.$//`
fi

#Remove the final word from the directory
while [ `echo $dir|awk '$0=$NF' FS=` != "/" ]
do
    dir=`echo $dir|sed s/.$//`
done

#Remove the final slash 
if [ `echo $dir|grep /|wc -c` != 2 ]
then
    dir=`echo $dir|sed s/.$//`
fi

echo $dir
