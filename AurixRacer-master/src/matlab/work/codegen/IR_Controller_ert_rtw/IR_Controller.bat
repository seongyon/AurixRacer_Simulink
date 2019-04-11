set "VSCMD_START_DIR=%CD%"

call "setup_msvc150.bat"

call "%VS150COMNTOOLS%..\..\VC\Auxiliary\Build\VCVARSALL.BAT" AMD64

cd .

if "%1"=="" (nmake  -f IR_Controller.mk all) else (nmake  -f IR_Controller.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
