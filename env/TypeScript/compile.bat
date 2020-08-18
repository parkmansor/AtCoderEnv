call node_modules\.bin\tsc
if %ERRORLEVEL% equ 0 (
    call node dist\index.js
)
