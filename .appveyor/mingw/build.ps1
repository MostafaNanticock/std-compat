# Simply add MinGW to PATH and let CMake auto-detect everything
$env:PATH = "$env:MINGW_PATH;$env:PATH"

function Show-MinGW-Info {
    Write-Host "=== MinGW Build Environment ===" -ForegroundColor Cyan
    Write-Host "MinGW Path: $env:MINGW_PATH" -ForegroundColor Yellow
    if ($env:MINGW_VERSION) { Write-Host "MinGW Version: $env:MINGW_VERSION" -ForegroundColor Yellow }
    if ($env:ARCHITECTURE) { Write-Host "Architecture: $env:ARCHITECTURE" -ForegroundColor Yellow }
    Write-Host "AppVeyor Image: $env:APPVEYOR_BUILD_WORKER_IMAGE" -ForegroundColor Yellow
    
    # Show compiler info
    try {
        $gccVersion = & gcc --version 2>&1 | Select-Object -First 1
        Write-Host "GCC: $gccVersion" -ForegroundColor Green
    } catch {
        Write-Host "GCC not found" -ForegroundColor Red
    }
    Write-Host "=================================" -ForegroundColor Cyan
}

function Build-And-Test($Generator, $Dir) {
    Show-MinGW-Info
    
    Write-Host "=== CMake Configure ==="
    cmake -S . -B $Dir -G "$Generator"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Write-Host "=== CMake Build ==="
    cmake --build $Dir --config Release
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Write-Host "=== Run Tests ==="
    Push-Location $Dir
    ctest -C Release --output-on-failure --timeout 60
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test "$env:GENERATOR" build_mingw
