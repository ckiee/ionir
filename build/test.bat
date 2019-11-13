@echo off

cmake --config ..
cmake ..
cmake --build .

SET testExec=test\Debug\IonIrTests.exe

if %errorlevel% EQU 0 (
    if not exist %testExec% (
        echo Build appears to be successful,3 however, test executable file does not exist.
        exit
    )

    %testExec%

    if %errorlevel% NEQ 0 (
        echo Tests appear to have failed.
    ) Else (
        echo Tests passed successfully.
    )
) Else (
    echo Build did not exit successfully, test executable will not be run.
)
