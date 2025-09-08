@echo off
setlocal enabledelayedexpansion

:: Args:
:: %1 = Shader source directory
:: %2 = Build shaders directory

set SHADER_DIR=%~1
set BUILD_DIR=%~2

:: Make sure the output directory exists
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

:: Loop over all .slang files in SHADER_DIR
for %%f in ("%SHADER_DIR%\*.slang") do (
    echo Compiling %%~nxf...
    slangc -target spirv -profile spirv_1_4 -emit-spirv-directly "%%f" -o "%BUILD_DIR%\%%~nf.spv"
)

echo.
echo All shaders compiled to: %BUILD_DIR%
endlocal
