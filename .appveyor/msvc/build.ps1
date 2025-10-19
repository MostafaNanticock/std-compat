# Ensure full error messages are displayed
$ErrorActionPreference = "Continue"
$WarningPreference = "Continue" 
$VerbosePreference = "Continue"

function Build-And-Test($Arch, $Dir) {
    Write-Output "=== Building $Arch with Ninja ==="
    cmake -S . -B $Dir -G "Ninja" -A $Arch -DCMAKE_BUILD_TYPE=Release
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    cmake --build $Dir
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Push-Location $Dir
    ctest --output-on-failure --timeout 60
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test Win32 build_x86
Build-And-Test x64   build_x64
