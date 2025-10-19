function Get-VcVarsPath {
    param([string]$Arch)

    $vswhere = Join-Path "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer" "vswhere.exe"
    $vsInstall = $null

    if (Test-Path $vswhere) {
        try {
            $vsInstall = & $vswhere -latest -products * `
                -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
                -property installationPath 2>$null
        } catch {
            $vsInstall = $null
        }
    }

    if ($vsInstall -and (Test-Path $vsInstall)) {
        return Join-Path $vsInstall "VC\Auxiliary\Build\vcvarsall.bat"
    }

    # Fallback for VS2015 (no vswhere, different layout)
    switch -Wildcard ($env:APPVEYOR_BUILD_WORKER_IMAGE) {
        "Visual Studio 2015*" {
            return "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
        }
        default {
            Write-Error "Visual Studio installation not found"
            exit 1
        }
    }
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
