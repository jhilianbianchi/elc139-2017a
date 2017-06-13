#!/bin/sh
#
# install.sh 
# 
#
#
# Gregory Duchemin, 09 August 2001
# c3rb3r@hotmail.com
#
#
#
echo
echo
echo  "~    ~  ~~~    ~~    ~~~   ~~~   ~~   ~  ~     "
echo  "    /|      |  |       )    __|  |      /           "
echo  "| || |   |  |  |    |   / |   |  |    | \\          "
echo  "|    |  ___/   __/  |   \\ |   |  __/  |  \\        "
echo
echo  "                            Installer             "
echo



#where am i ?

if [ ! -f Makefile ]; then
echo
echo "Oops, i need to be launched in the MDcrack root directory."
echo
exit
fi

#wanna color in your life ?

echo
echo "Do you want a Ncurses enabled version of MDcrack (default: no) ? [yes/no]"
read

if [ -z $REPLY ]; then
REPLY=no
fi

echo -n "Modifying Makefile ..... "
if [ $REPLY != "yes" ]; then
sed 's/^LDFLAG=-lncurses/#LDFLAG=-lncurses/' Makefile | sed 's/^NCURSES=-DNCURSES/#NCURSES=-DNCURSES/' > /tmp/.mdcrack-tmp
mv /tmp/.mdcrack-tmp Makefile
echo "ok"
echo
else
sed 's/^#LDFLAG=-lncurses/LDFLAG=-lncurses/' Makefile | sed 's/^#NCURSES=-DNCURSES/NCURSES=-DNCURSES/' > /tmp/.mdcrack-tmp
mv /tmp/.mdcrack-tmp Makefile
echo "ok"
echo
fi


#where should i store the resume file ?

echo
echo "When you interrupt my work, i always save it to be able to restart the session later."
echo "Give me an absolute path+filename (default: /tmp/.mdcrack-resume) "
read

if [ -z $REPLY ]; then
REPLY=/tmp/.mdcrack-resume
fi


REPLY=$(echo $REPLY | sed 's/\//\\\//g')

echo -n "Modifying Makefile ..... "

sed 's/\-DRESUME_FILE=.* -DBENCH/\-DRESUME_FILE="\\"'$REPLY'\\"" -DBENCH/' Makefile > /tmp/.mdcrack-tmp
mv /tmp/.mdcrack-tmp Makefile
echo "ok"
echo



#big or little, i speak about endianness :-) 

echo
echo "Wich kind of cpu endianness (default: little) ? [little/big]"
read

if [ -z $REPLY ]; then
REPLY=little 
fi

echo -n "Compiling and installing mdcrack, please wait a few minutes ..... "
if [ $REPLY != "big" ]; then
make clean little install > /dev/null
echo "ok"
echo
else
make clean big install > /dev/null 
echo "ok"
echo
fi


echo
echo "mdcrack is installed in /usr/sbin."
echo
echo "If your display looks like a bit crappy when running mdcrack, i suggest to reinstall without Ncurses."
echo
echo "Have a nice day."
echo


