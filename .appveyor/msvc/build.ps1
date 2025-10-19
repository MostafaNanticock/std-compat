# Ensure full error messages are displayed
$ErrorActionPreference = "Continue"
$WarningPreference = "Continue" 
$VerbosePreference = "Continue"

function Build-And-Test($Arch, $Dir) {
    Write-Output "=== Building $Arch with Ninja Multi-Config ==="
    cmake -S . -B $Dir -G "Ninja Multi-Config" -A $Arch
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    cmake --build $Dir --config Release
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Push-Location $Dir
    ctest -C Release --output-on-failure --timeout 60
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test Win32 build_x86
Build-And-Test x64   build_x64
