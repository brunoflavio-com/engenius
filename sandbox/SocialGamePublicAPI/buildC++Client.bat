REM Script for generating c++ client files for SocialGamePublicApi using Gsoap 2.8

echo off
SET OUTPUT_FILE=Service1
SET OUTPUT_PATH=stub
SET WSDL=service1.wsdl
 
RD /s /q %OUTPUT_PATH%
MD %OUTPUT_PATH%
 
wsdl2h.exe -o %OUTPUT_PATH%/%OUTPUT_FILE%.h -I ../../wsdl %WSDL%
soapcpp2 -j -C %OUTPUT_PATH%/%OUTPUT_FILE%.h -I ../../import/ -d"%OUTPUT_PATH%"
pause