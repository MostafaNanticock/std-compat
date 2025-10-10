# Ensure full error messages are displayed
$ErrorActionPreference = "Continue"
$WarningPreference = "Continue" 
$VerbosePreference = "Continue"

function Build-And-Test($Generator, $Arch, $Dir) {
    Write-Output "=== Building $Arch with $Generator ==="
    cmake -S . -B $Dir -G "$Generator" -A $Arch
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    cmake --build $Dir --config Release
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Push-Location $Dir
    ctest -C Release --output-on-failure --timeout 60
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test "$env:GENERATOR" Win32 build_x86
Build-And-Test "$env:GENERATOR" x64   build_x64
