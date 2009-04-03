@echo off

set OMNET=c:\omnet\bin

rem Make sure that you have Visual Studio 2003 set up properly.
rem Run vsvars32.bat if in doubt.

set PATH=%PATH%;%OMNET%

cd ..

cd util
opp_nmakemake -f -I..\util -I..\ipv6 -I..\wimax
nmake -f Makefile.vc depend
nmake -f Makefile.vc 
cd ..

cd ipv6
opp_nmakemake -f -I..\util -I..\ipv6 -I..\wimax
nmake -f Makefile.vc depend
nmake -f Makefile.vc 
cd ..

cd wimax
opp_nmakemake -f -I..\util -I..\ipv6 -I..\wimax
nmake -f Makefile.vc depend
nmake -f Makefile.vc 
cd ..

