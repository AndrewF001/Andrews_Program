::@echo off
::MD %2TextFiles\
xcopy "%1TextFiles\." "%2TextFiles\." /i /h /y /e /q
:: /f to show full path directories, remove /q
::attrib -s -h "%2TextFiles\."