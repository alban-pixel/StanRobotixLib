Write-Host "=== StanRobotixLib — Installation Rapide (Windows FRC 6622) ===" -ForegroundColor Cyan

if (-not (Test-Path "build.gradle")) {
    Write-Host "[!] Attention : aucun fichier build.gradle detecte dans le repertoire courant ($PWD)." -ForegroundColor Yellow
    Write-Host "    Assurez-vous d'executer cette commande a la racine de votre projet robot FRC." -ForegroundColor Yellow
}

if (-not (Test-Path "vendordeps")) {
    New-Item -ItemType Directory -Path "vendordeps" | Out-Null
}

$jsonUrl = "https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/StanRobotixLib.json"
Write-Host "-> Telechargement de StanRobotixLib.json..." -ForegroundColor Green
Invoke-WebRequest -Uri $jsonUrl -OutFile "vendordeps\StanRobotixLib.json"
Write-Host "   [+] vendordeps\StanRobotixLib.json installe" -ForegroundColor Green

$cacheDir = "$env:USERPROFILE\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
if (-not (Test-Path $cacheDir)) {
    New-Item -ItemType Directory -Path $cacheDir -Force | Out-Null
}

$rawBase = "https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
Write-Host "-> Telechargement des en-tetes C++ (support hors-ligne)..." -ForegroundColor Green
Invoke-WebRequest -Uri "$rawBase/StanRobotixLib-cpp-1.0.0-headers.zip" -OutFile "$cacheDir\StanRobotixLib-cpp-1.0.0-headers.zip"
Invoke-WebRequest -Uri "$rawBase/StanRobotixLib-cpp-1.0.0.pom" -OutFile "$cacheDir\StanRobotixLib-cpp-1.0.0.pom"
Write-Host "   [+] En-tetes C++ mis en cache dans $cacheDir" -ForegroundColor Green

if (Test-Path "C:\Users\Public\wpilib\2026\maven") {
    $publicDir = "C:\Users\Public\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
    if (-not (Test-Path $publicDir)) {
        New-Item -ItemType Directory -Path $publicDir -Force | Out-Null
    }
    Copy-Item "$cacheDir\StanRobotixLib-cpp-1.0.0-headers.zip" "$publicDir\" -Force
    Copy-Item "$cacheDir\StanRobotixLib-cpp-1.0.0.pom" "$publicDir\" -Force
    Write-Host "   [+] En-tetes C++ copies dans $publicDir" -ForegroundColor Green
}

Write-Host ""
Write-Host "=== StanRobotixLib a ete installee avec succes ! ===" -ForegroundColor Cyan
Write-Host "Vous pouvez maintenant compiler votre projet :"
Write-Host "  gradlew.bat test"
