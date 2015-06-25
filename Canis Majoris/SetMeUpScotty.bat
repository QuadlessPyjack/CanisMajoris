echo off
set LOG=log_%DATE%_%TIME%.txt
set LOG=%LOG::=-%
set LOG=%LOG:/=-%
REM echo LOG var is = %LOG%
echo =============================================
echo   Canis Majoris Dev Environment Init Script
echo     - author: Bogdan Vitel, 12/06/2015 -
echo =============================================
echo ============================================= >> %LOG%
echo   Canis Majoris Dev Environment Init Script >> %LOG%
echo     - author: Bogdan Vitel, 12/06/2015 -       >> %LOG%
echo ============================================= >> %LOG%
echo
echo >> %LOG%
echo 1. Setting Up Libraries Repository
echo 1. Setting Up Libraries Repository >> %LOG%
subst X: ..\auxiliaries
echo Libs Repository Successfully Mounted
echo Libs Repository Successfully Mounted >> %LOG%

set AUXILIARIES=X:\SDL_draw-1.2.13\lib\x86\SDL_draw.dll

echo 2.  Copying Engine Test Data
echo 2.  Copying Engine Test Data >> %LOG%

echo 2a. Copying .OBJ Model Data
echo 2a. Copying .OBJ Model Data >>%LOG%
copy X:\TestData\*.obj *.obj
echo OBJ Model Data Copy Complete
echo OBJ Model Data Copy Complete >> %LOG%

echo All Engine Test Data Files Copied Successfully
echo All Engine Test Data Files Copied Successfully >> %LOG%

echo 3. Launching VS Solution
echo 3. Launching VS Solution >> %LOG%

echo Have a nice day!
echo Have a nice day! >> %LOG%

"Canis Majoris.sln"