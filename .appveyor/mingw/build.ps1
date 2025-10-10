# Add MinGW to PATH
$env:PATH = "$env:MINGW_PATH;$env:PATH"

function Show-MinGW-Info {
    Write-Output "=== MinGW Build Environment ==="
    Write-Output "MinGW Path: $env:MINGW_PATH"
    if ($env:MINGW_VERSION) { Write-Output "MinGW Version: $env:MINGW_VERSION" }
    if ($env:ARCHITECTURE) { Write-Output "Architecture: $env:ARCHITECTURE" }
    Write-Output "AppVeyor Image: $env:APPVEYOR_BUILD_WORKER_IMAGE"
    
    # Show compiler info
    try {
        $gccVersion = & gcc --version 2>&1 | Select-Object -First 1
        Write-Output "GCC: $gccVersion"
    } catch {
        Write-Output "GCC not found"
    }
    Write-Output "================================="
}

function Build-And-Test($Generator, $Dir) {
    Show-MinGW-Info
    
    # Find available make program
    $makeProgram = $null
    if (Get-Command "mingw32-make.exe" -ErrorAction SilentlyContinue) {
        $makeProgram = (Get-Command "mingw32-make.exe").Source
    } elseif (Get-Command "make.exe" -ErrorAction SilentlyContinue) {
        $makeProgram = (Get-Command "make.exe").Source
        $Generator = "Unix Makefiles"
        Write-Output "Using Unix Makefiles generator with make.exe"
    }
    
    Write-Output "=== CMake Configure ==="
    if ($makeProgram) {
        $configOutput = cmake -S . -B $Dir -G "$Generator" -DCMAKE_MAKE_PROGRAM="$makeProgram" 2>&1
    } else {
        $configOutput = cmake -S . -B $Dir -G "$Generator" 2>&1
    }
    $configOutput | Write-Output
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Write-Output "=== CMake Build ==="
    $buildOutput = cmake --build $Dir --config Release 2>&1
    $buildOutput | Write-Output
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Write-Output "=== Run Tests ==="
    Push-Location $Dir
    $testOutput = ctest -C Release --output-on-failure --timeout 60 2>&1
    $testOutput | Write-Output
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test "$env:GENERATOR" build_mingw
