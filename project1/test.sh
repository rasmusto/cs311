#/bin/sh
FAILFLAG=0

if [ `./prog1.sh /nfs/one/two` != "/nfs/one" ]
then
    echo "failed 1"
    FAILFLAG=1
fi

if [ `./prog1.sh /nfs/stak/u14/w/wallacch` != "/nfs/stak/u14/w" ]
then
    echo "failed 2"
    FAILFLAG=1
fi

if [ `./prog1.sh /nfs/stak` != "/nfs" ]
then
    echo "failed 3"
    FAILFLAG=1
fi

if [ `./prog1.sh /` != "/" ]
then
    echo "failed 4"
    FAILFLAG=1
fi

if [ `./prog1.sh /nfs` != "/" ]
then
    echo "failed 5"
    FAILFLAG=1
fi

if [ `./prog1.sh ~` != "/nfs/farm/u2/r" ]
then
    echo "failed 6"
    FAILFLAG=1
fi

if [ `./prog1.sh ../../cs151` != "../.." ]
then
    echo "failed 7"
    FAILFLAG=1
fi

if [ `./prog1.sh -c /nfs/stak` != "3" ]
then
    echo "failed 8"
    FAILFLAG=1
fi

if [ `./prog1.sh -c /nfs/` != "2" ]
then
    echo "failed 9"
    FAILFLAG=1
fi

if [ `./prog1.sh -c /nfs/stak/a2/classes` != "5" ]
then
    echo "failed 10"
    FAILFLAG=1
fi

if [ `./prog1.sh -c /` != "1" ]
then
    echo "failed 11"
    FAILFLAG=1
fi

if [ `./prog1.sh -c ../../cs151/mytextfile.txt` != "3" ]
then
    echo "failed 12"
    FAILFLAG=1
fi

echo "FAILFLAG = $FAILFLAG"
