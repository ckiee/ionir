@echo off

rem Build project first.
call build.bat

rem Run tests.
cd build
SET testExec=test\Debug\IonIrTests.exe

if %errorlevel% EQU 0 (
    if not exist %testExec% (
        echo Build appears to be successful, however, test executable file does not exist.
    ) Else (
        %testExec%

        if %errorlevel% NEQ 0 (
            echo Tests appear to have failed.
        ) Else (
            echo Tests passed successfully.
        )
    )
) Else (
    echo Build did not exit successfully, test executable will not be run.
)

cd ..
