#!/bin/sh
#
# Bench.sh 
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
echo  "                        Benchmark Generator          "
echo



#where am i ?

if [ ! -f Makefile ]; then
echo
echo "Oops, i need to be launched in the MDcrack root directory."
echo
exit
fi

#mdcrack-version exists ?

if [ ! -f /usr/sbin/mdcrack-version ]; then
echo
echo "Your version currently installed is not up to date or incorrectly installed"
echo "Do you want me to rebuild a non Ncurses binary before making the benchmarks (default: yes) ? [yes/no]"
read
if [ -s $REPLY ]; then
REPLY=yes
fi

if [ $REPLY = "no" ]; then
echo
echo "I didn't find my \"mdcrack-version\" file in /usr/sbin."
echo "did you install this release by using make install ?"
echo "make clean"
echo "make little/big install (little for little endian, big for big endian)"
echo "x86 users use \"make little install\"."
echo
exit
fi

echo
echo -n "Modifying Makefile ..... "
sed 's/^LDFLAG=-lncurses/#LDFLAG=-lncurses/' Makefile | sed 's/^NCURSES=-DNCURSES/#NCURSES=-DNCURSES/' > /tmp/.mdcrack-tmp
mv /tmp/.mdcrack-tmp Makefile
echo "ok"
echo
echo "Wich kind of cpu endianness (default: little) ? [little/big]"
read

if [ -s $REPLY ]; then
REPLY=little
fi
echo -n "Compiling/installing mdcrack, please wait a few minutes ..... "
if [ $REPLY = "big" ]; then
make clean big install > /dev/null
echo "ok"
echo
else
make clean little install > /dev/null
echo "ok"
echo
fi
fi



#Ncurses enabled ?

grep NCURSES /usr/sbin/mdcrack-version > /dev/null
if [ $? = 0 ]; then
echo
echo "Your version currently installed is Ncurses enabled"
echo "Do you want me to rebuild a non Ncurses binary before making the benchmarks (default: yes) ? [yes/no]"
read
if [ -s $REPLY ]; then
REPLY=yes
fi

if [ $REPLY = "no" ]; then
echo
echo "You have a Ncurses version installed,"
echo "Please comment Ncurses entries in Makefile before making benchmarks."
echo "rebuild and reinstall mdcrack."
echo "make clean"
echo "make little/big install (little for little endian, big for big endian)"
echo "x86 users use \"make little install\"."
echo
exit
fi

echo
echo -n "Modifying Makefile ..... "
sed 's/^LDFLAG=-lncurses/#LDFLAG=-lncurses/' Makefile | sed 's/^NCURSES=-DNCURSES/#NCURSES=-DNCURSES/' > /tmp/.mdcrack-tmp
mv /tmp/.mdcrack-tmp Makefile
echo "ok"
echo
echo "Wich kind of cpu endianness (default: little) ? [little/big]"
read

if [ -s $REPLY ]; then
REPLY=little
fi

echo -n "Compiling/installing mdcrack, please wait a few minutes ..... "
if [ $REPLY = "big" ]; then
make clean big install > /dev/null
echo "ok"
echo
else
make clean little install > /dev/null
echo "ok"
fi
fi




echo
echo "Please wait a minute, benchmark in progress..."
echo
echo
echo General informations
echo
echo > /tmp/.mdcrack-bench
echo -n "Collecting system informations ..... "
echo "======== System Info ============" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
uname >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo -n "Collecting hardware informations ..... "
echo "======== Hardware Info ==========" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
cat /proc/cpuinfo >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo -n "Collecting compiler informations ..... "
echo "======== Compiler Info ==========" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
gcc -v >> /tmp/.mdcrack-bench 2>&1
echo >> /tmp/.mdcrack-bench
echo "done"
echo -n "Collecting MDcrack informations ..... "
echo "======= Mdcrack Release =========" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
mdcrack -r >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo
echo Benchmarks
echo
echo -n "Benchmarking MD5 ..... "
echo "========== MD5 Bench ============" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
mdcrack -M MD5 -t 10 >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo -n "Benchmarking MD4 ..... "
echo "========== MD4 Bench ============" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
mdcrack -M MD4 -t 10 >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo -n "Benchmarking NTLM v1 ..... "
echo "========== NTLM1 Bench ============" >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
mdcrack -M NTLM1 -t 10 >> /tmp/.mdcrack-bench
echo >> /tmp/.mdcrack-bench
echo "done"
echo
echo "[press enter to see the report]"
read
echo
cat /tmp/.mdcrack-bench
echo "==================================" 
echo
echo
echo
echo
echo "Do you agree to send now this report to my mailbox (default: no) ? [yes/no]"
read
if [ -s $REPLY ]; then
REPLY=no
fi

if [ $REPLY != "yes" ]; then
echo
rm /tmp/.mdcrack-bench
exit
fi

echo -n "Sending bench to c3rb3r@hotmail.com ..... "
cat /tmp/.mdcrack-bench | mail -s "Mdcrack benchmark" c3rb3r@hotmail.com 
echo "ok"
echo
echo "thank you"
echo "and have a nice day."
rm /tmp/.mdcrack-bench
echo



