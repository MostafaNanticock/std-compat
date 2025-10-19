function Get-VcVarsPath {
    param([string]$Arch)

    # Use vswhere to locate the latest VS installation on this image
    $vsInstall = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" `
        -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath

    if (-not $vsInstall) {
        Write-Error "Visual Studio installation not found"
        exit 1
    }

    return Join-Path $vsInstall "VC\Auxiliary\Build\vcvarsall.bat"
}

function Build-And-Test($Arch, $Dir) {
    Write-Output "=== Building $Arch with Ninja ==="

    $vcvars = Get-VcVarsPath $Arch

    # Call vcvarsall.bat to set up MSVC environment for the given arch
    cmd /c "`"$vcvars`" $Arch && cmake -S . -B $Dir -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build $Dir && ctest --test-dir $Dir --output-on-failure --timeout 60"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

# Build both architectures sequentially
Build-And-Test x86 build_x86
Build-And-Test x64 build_x64
