function Get-VcVarsPath {
    try {
        $vsInstall = vswhere -latest -products * `
            -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
            -property installationPath 2>$null
    } catch {
        $vsInstall = $null
    }

    if ($vsInstall -and (Test-Path $vsInstall)) {
        return Join-Path $vsInstall "VC\Auxiliary\Build\vcvarsall.bat"
    }

    switch -Wildcard ($env:APPVEYOR_BUILD_WORKER_IMAGE) {
        "Visual Studio 2015*" {
            return "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
        }
        default {
            throw "Could not locate Visual Studio installation"
        }
    }
}

function Build-And-Test {
    param(
        [string]$Arch,
        [string]$Dir
    )

    $vcvars = Get-VcVarsPath
    Write-Output "=== Building $Arch with Ninja in $Dir ==="

    $inner = @"
& `"$vcvars`" $Arch >`$null
cmake -S . -B $Dir -G Ninja -DCMAKE_BUILD_TYPE=Release
if (`$LASTEXITCODE -ne 0) { exit `$LASTEXITCODE }
cmake --build $Dir
if (`$LASTEXITCODE -ne 0) { exit `$LASTEXITCODE }
ctest --test-dir $Dir --output-on-failure --timeout 60
if (`$LASTEXITCODE -ne 0) { exit `$LASTEXITCODE }
"@

    # Run in a clean PowerShell process, inheriting console output
    $exitCode = & powershell.exe -NoProfile -NonInteractive -Command $inner
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

# Sequential builds
Build-And-Test x86 build_x86
Build-And-Test x64 build_x64
