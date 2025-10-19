function Build-And-Test($Arch, $Dir) {
    Write-Output "=== Building $Arch with Ninja ==="

    $vcvars = Join-Path $env:VSINSTALLDIR "VC\Auxiliary\Build\vcvarsall.bat"

    if (-not (Test-Path $vcvars)) {
        Write-Error "vcvarsall.bat not found at $vcvars"
        exit 1
    }

    # Run vcvarsall + cmake + build + test in one cmd.exe invocation
    cmd /c "`"$vcvars`" $Arch && cmake -S . -B $Dir -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build $Dir && ctest --test-dir $Dir --output-on-failure --timeout 60"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

# Build both architectures sequentially
Build-And-Test x86 build_x86
Build-And-Test x64 build_x64
