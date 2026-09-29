@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

echo === Installation de StanRobotixLib Vendordep (Windows) ===

rem 1. Generation des headers et publication Maven Local
echo -^> Generation des headers et publication Maven...
call gradlew.bat headersZip publishToMavenLocal publish
if %ERRORLEVEL% neq 0 (
    echo [X] Erreur lors de la compilation Gradle.
    exit /b %ERRORLEVEL%
)

rem 2. Installation dans les caches WPILib Maven locaux
set "DEST_USER=%USERPROFILE%\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
if not exist "%DEST_USER%" mkdir "%DEST_USER%"
copy /Y "build\libs\StanRobotixLib-cpp-1.0.0-headers.zip" "%DEST_USER%\" >nul
copy /Y "build\publications\stanRobotixLib\pom-default.xml" "%DEST_USER%\StanRobotixLib-cpp-1.0.0.pom" >nul
echo -^> Installe dans %DEST_USER%

if exist "C:\Users\Public\wpilib\2026\maven" (
    set "DEST_PUBLIC=C:\Users\Public\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
    if not exist "!DEST_PUBLIC!" mkdir "!DEST_PUBLIC!"
    copy /Y "build\libs\StanRobotixLib-cpp-1.0.0-headers.zip" "!DEST_PUBLIC!\" >nul
    copy /Y "build\publications\stanRobotixLib\pom-default.xml" "!DEST_PUBLIC!\StanRobotixLib-cpp-1.0.0.pom" >nul
    echo -^> Installe dans !DEST_PUBLIC!
)

rem 3. Installation dans le projet robot cible
set "TARGET_PROJECT=%~1"

if "%TARGET_PROJECT%"=="" (
    if exist "..\2026-StanRobotix-OffSeason\Mid-Robot" (
        set "TARGET_PROJECT=..\2026-StanRobotix-OffSeason\Mid-Robot"
    ) else if exist "..\2026-StanRobotix-FRC" (
        set "TARGET_PROJECT=..\2026-StanRobotix-FRC"
    )
)

if not "%TARGET_PROJECT%"=="" (
    if exist "%TARGET_PROJECT%" (
        echo -^> Installation dans le projet robot : %TARGET_PROJECT%
        if not exist "%TARGET_PROJECT%\vendordeps" mkdir "%TARGET_PROJECT%\vendordeps"
        copy /Y "StanRobotixLib.json" "%TARGET_PROJECT%\vendordeps\StanRobotixLib.json" >nul
        echo    [+] StanRobotixLib.json copie dans %TARGET_PROJECT%\vendordeps\
        
        if exist "%TARGET_PROJECT%\build.gradle" (
            findstr /C:"mavenLocal()" "%TARGET_PROJECT%\build.gradle" >nul
            if errorlevel 1 (
                echo    [!] Note : Ajoutez mavenLocal^(^) dans le bloc repositories { } de %TARGET_PROJECT%\build.gradle si ce n'est pas deja fait.
            ) else (
                echo    [+] mavenLocal^(^) detecte dans build.gradle
            )
        )
    ) else (
        echo [!] Repertoire cible introuvable : %TARGET_PROJECT%
    )
) else (
    echo.
    echo Pour installer le fichier vendordep dans un projet robot specifique :
    echo   install_vendordep.bat C:\chemin\vers\votre\projet
)

echo.
echo === Vendordep StanRobotixLib installee avec succes ! ===
