@echo off
setlocal enabledelayedexpansion

echo === StanRobotixLib - Installation Automatique (FRC 6622) ===

rem 1. Configuration des chemins globaux WPILib
set "WPILIB_USER=%USERPROFILE%\wpilib\2026"
set "MAVEN_USER=%WPILIB_USER%\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
set "VENDOR_USER=%WPILIB_USER%\vendordeps"

if not exist "%MAVEN_USER%" mkdir "%MAVEN_USER%"
if not exist "%VENDOR_USER%" mkdir "%VENDOR_USER%"

rem 2. URLs distantes
set "RAW_REPO=https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main"
set "JSON_URL=%RAW_REPO%/StanRobotixLib.json"
set "RAW_MAVEN=%RAW_REPO%/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
set "ZIP_URL=%RAW_MAVEN%/StanRobotixLib-cpp-1.0.0-headers.zip"
set "POM_URL=%RAW_MAVEN%/StanRobotixLib-cpp-1.0.0.pom"

rem 3. Telechargement des fichiers vers le cache global WPILib
echo -^> Telechargement de StanRobotixLib.json...
where curl >nul 2>nul
if %ERRORLEVEL% equ 0 (
    curl -fsSL "%JSON_URL%" -o "%VENDOR_USER%\StanRobotixLib.json"
) else (
    powershell -NoProfile -Command "(New-Object Net.WebClient).DownloadFile('%JSON_URL%', '%VENDOR_USER%\StanRobotixLib.json')"
)

if exist "%VENDOR_USER%\StanRobotixLib.json" (
    echo    [+] StanRobotixLib.json installe dans %VENDOR_USER%
) else (
    echo [X] Erreur lors du telechargement de StanRobotixLib.json
    exit /b 1
)

echo -^> Telechargement des en-tetes C++ (support hors-ligne)...
where curl >nul 2>nul
if %ERRORLEVEL% equ 0 (
    curl -fsSL "%ZIP_URL%" -o "%MAVEN_USER%\StanRobotixLib-cpp-1.0.0-headers.zip"
    curl -fsSL "%POM_URL%" -o "%MAVEN_USER%\StanRobotixLib-cpp-1.0.0.pom"
) else (
    powershell -NoProfile -Command "(New-Object Net.WebClient).DownloadFile('%ZIP_URL%', '%MAVEN_USER%\StanRobotixLib-cpp-1.0.0-headers.zip')"
    powershell -NoProfile -Command "(New-Object Net.WebClient).DownloadFile('%POM_URL%', '%MAVEN_USER%\StanRobotixLib-cpp-1.0.0.pom')"
)
echo    [+] En-tetes C++ mis en cache dans %MAVEN_USER%

rem Duplication dans C:\Users\Public\wpilib si present
if exist "C:\Users\Public\wpilib\2026" (
    set "MAVEN_PUBLIC=C:\Users\Public\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
    set "VENDOR_PUBLIC=C:\Users\Public\wpilib\2026\vendordeps"
    if not exist "!MAVEN_PUBLIC!" mkdir "!MAVEN_PUBLIC!"
    if not exist "!VENDOR_PUBLIC!" mkdir "!VENDOR_PUBLIC!"
    copy /Y "%VENDOR_USER%\StanRobotixLib.json" "!VENDOR_PUBLIC!\" >nul
    copy /Y "%MAVEN_USER%\StanRobotixLib-cpp-1.0.0-headers.zip" "!MAVEN_PUBLIC!\" >nul
    copy /Y "%MAVEN_USER%\StanRobotixLib-cpp-1.0.0.pom" "!MAVEN_PUBLIC!\" >nul
    echo    [+] En-tetes et vendordep copies dans C:\Users\Public\wpilib\2026
)

rem 4. Installation dans un projet robot cible si specifie ou detecte
set "TARGET_DIR="

if not "%~1"=="" (
    set "TARGET_DIR=%~1"
) else if exist "build.gradle" (
    set "TARGET_DIR=%CD%"
)

if not "!TARGET_DIR!"=="" (
    echo -^> Injection de la vendordep dans le projet : !TARGET_DIR!
    if not exist "!TARGET_DIR!\vendordeps" mkdir "!TARGET_DIR!\vendordeps"
    copy /Y "%VENDOR_USER%\StanRobotixLib.json" "!TARGET_DIR!\vendordeps\StanRobotixLib.json" >nul
    echo    [+] vendordeps\StanRobotixLib.json injecte dans le projet.

    if exist "!TARGET_DIR!\build.gradle" (
        findstr /C:"mavenLocal()" "!TARGET_DIR!\build.gradle" >nul
        if errorlevel 1 (
            echo    [!] Note : Verifiez la presence de mavenLocal^(^) dans repositories { } de build.gradle.
        ) else (
            echo    [+] mavenLocal^(^) detecte dans build.gradle.
        )
    )
) else (
    echo.
    echo [*] Note : Execute en dehors d'un projet robot specifique.
    echo     La vendordep est desormais disponible partout sur cet ordinateur !
    echo     Dans VS Code : WPILib -^> Manage Vendor Libraries -^> Install new library (offline) -^> StanRobotixLib.
)

echo.
echo === StanRobotixLib est prete a l'emploi sur cette machine ! ===
