rem ..\misc\make.bat

gcc -I..\misc -I..\include -c poet.c

gcc -I..\misc -I..\include -o poet.exe poet.o libwin.a
