@echo off
MD %2TextFiles\
xcopy  /e /y /t "%1TextFiles\." "%2TextFiles"