Write-Host "=== StanRobotixLib — Installation Automatique (Windows FRC 6622) ===" -ForegroundColor Cyan

# 1. Chemins globaux WPILib
$wpilibUser = "$env:USERPROFILE\wpilib\2026"
$mavenUser = "$wpilibUser\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
$vendorUser = "$wpilibUser\vendordeps"

if (-not (Test-Path $mavenUser)) { New-Item -ItemType Directory -Path $mavenUser -Force | Out-Null }
if (-not (Test-Path $vendorUser)) { New-Item -ItemType Directory -Path $vendorUser -Force | Out-Null }

# 2. URLs distantes
$rawRepo = "https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main"
$jsonUrl = "$rawRepo/StanRobotixLib.json"
$rawMaven = "$rawRepo/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
$zipUrl = "$rawMaven/StanRobotixLib-cpp-1.0.0-headers.zip"
$pomUrl = "$rawMaven/StanRobotixLib-cpp-1.0.0.pom"

# 3. Telechargement dans le cache global WPILib
Write-Host "-> Telechargement de StanRobotixLib.json..." -ForegroundColor Green
Invoke-WebRequest -Uri $jsonUrl -OutFile "$vendorUser\StanRobotixLib.json"
Write-Host "   [+] StanRobotixLib.json installe dans $vendorUser" -ForegroundColor Green

Write-Host "-> Telechargement des en-tetes C++ (support hors-ligne)..." -ForegroundColor Green
Invoke-WebRequest -Uri $zipUrl -OutFile "$mavenUser\StanRobotixLib-cpp-1.0.0-headers.zip"
Invoke-WebRequest -Uri $pomUrl -OutFile "$mavenUser\StanRobotixLib-cpp-1.0.0.pom"
Write-Host "   [+] En-tetes C++ mis en cache dans $mavenUser" -ForegroundColor Green

if (Test-Path "C:\Users\Public\wpilib\2026") {
    $mavenPublic = "C:\Users\Public\wpilib\2026\maven\com\stanrobotix\StanRobotixLib-cpp\1.0.0"
    $vendorPublic = "C:\Users\Public\wpilib\2026\vendordeps"
    if (-not (Test-Path $mavenPublic)) { New-Item -ItemType Directory -Path $mavenPublic -Force | Out-Null }
    if (-not (Test-Path $vendorPublic)) { New-Item -ItemType Directory -Path $vendorPublic -Force | Out-Null }
    Copy-Item "$vendorUser\StanRobotixLib.json" "$vendorPublic\" -Force
    Copy-Item "$mavenUser\StanRobotixLib-cpp-1.0.0-headers.zip" "$mavenPublic\" -Force
    Copy-Item "$mavenUser\StanRobotixLib-cpp-1.0.0.pom" "$mavenPublic\" -Force
    Write-Host "   [+] En-tetes et vendordep copies dans C:\Users\Public\wpilib\2026" -ForegroundColor Green
}

# 4. Injection dans un projet robot cible si specifie ou detecte
$targetDir = $null
if ($args.Count -gt 0 -and $args[0]) {
    $targetDir = $args[0]
} elseif (Test-Path "build.gradle") {
    $targetDir = $PWD.Path
}

if ($targetDir -and (Test-Path $targetDir)) {
    Write-Host "-> Injection de la vendordep dans le projet : $targetDir" -ForegroundColor Green
    $projectVendor = "$targetDir\vendordeps"
    if (-not (Test-Path $projectVendor)) { New-Item -ItemType Directory -Path $projectVendor -Force | Out-Null }
    Copy-Item "$vendorUser\StanRobotixLib.json" "$projectVendor\" -Force
    Write-Host "   [+] vendordeps\StanRobotixLib.json injecte dans le projet." -ForegroundColor Green
} else {
    Write-Host ""
    Write-Host "[*] Execute en dehors d'un projet robot specifique." -ForegroundColor Yellow
    Write-Host "    La vendordep est desormais disponible partout sur cet ordinateur !" -ForegroundColor Yellow
    Write-Host "    Dans VS Code : WPILib -> Manage Vendor Libraries -> Install new library (offline) -> StanRobotixLib." -ForegroundColor Yellow
}

Write-Host ""
Write-Host "=== StanRobotixLib est prete a l'emploi sur cette machine ! ===" -ForegroundColor Cyan
