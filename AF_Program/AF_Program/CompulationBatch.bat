::@echo off
::MD %2TextFiles\
xcopy "%1TextFiles\." "%2TextFiles\." /v /i /h /y /e
:: /f to show full path directories
::attrib -s -h "%2TextFiles\."