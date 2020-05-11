@echo off

rem Prepare environment.
set testExec=test\IonIrTests.exe
del %testExec%

rem Build project first.
call build.bat

rem Run tests.
cd build

if %errorlevel% equ 0 (
    if not exist %testExec% (
        echo Build appears to be successful, however, test executable file does not exist.
    ) else (
        %testExec%

        if %errorlevel% NEQ 0 (
            echo Tests appear to have failed.
        ) else (
            echo Tests passed successfully.
        )
    )
) else (
    echo Build did not exit successfully, test executable will not be run.
)

cd ..
