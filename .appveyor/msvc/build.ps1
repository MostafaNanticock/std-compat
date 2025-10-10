function Build-And-Test($Generator, $Arch, $Dir) {
    Write-Output "=== Building $Arch with $Generator ==="
    $configOutput = cmake -S . -B $Dir -G "$Generator" -A $Arch 2>&1
    $configOutput | Write-Output
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    $buildOutput = cmake --build $Dir --config Release 2>&1
    $buildOutput | Write-Output
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Push-Location $Dir
    $testOutput = ctest -C Release --output-on-failure --timeout 60 2>&1
    $testOutput | Write-Output
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test "$env:GENERATOR" Win32 build_x86
Build-And-Test "$env:GENERATOR" x64   build_x64
