$env:PATH = "$env:MINGW_PATH;$env:PATH"

function Show-MinGW-Info {
    Write-Host "=== MinGW Build Environment Information ===" -ForegroundColor Cyan
    Write-Host "MinGW Path: $env:MINGW_PATH" -ForegroundColor Yellow
    if ($env:MINGW_VERSION) { Write-Host "MinGW Version: $env:MINGW_VERSION" -ForegroundColor Yellow }
    if ($env:ARCHITECTURE) { Write-Host "Architecture: $env:ARCHITECTURE" -ForegroundColor Yellow }
    if ($env:QT_VERSION) { Write-Host "Qt Version: $env:QT_VERSION" -ForegroundColor Yellow }
    Write-Host "AppVeyor Image: $env:APPVEYOR_BUILD_WORKER_IMAGE" -ForegroundColor Yellow
    
    # Show actual compiler versions
    try {
        $gccVersion = & gcc --version 2>&1 | Select-Object -First 1
        Write-Host "GCC Version: $gccVersion" -ForegroundColor Green
    } catch {
        Write-Host "GCC not found in PATH" -ForegroundColor Red
    }
    
    try {
        $gppVersion = & g++ --version 2>&1 | Select-Object -First 1
        Write-Host "G++ Version: $gppVersion" -ForegroundColor Green
    } catch {
        Write-Host "G++ not found in PATH" -ForegroundColor Red
    }
    
    Write-Host "==========================================" -ForegroundColor Cyan
}

function Build-And-Test($Generator, $Dir) {
    Show-MinGW-Info
    
    Write-Host "=== Building with $Generator (MinGW) ==="
    cmake -S . -B $Dir -G "$Generator"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    cmake --build $Dir --config Release
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Push-Location $Dir
    ctest -C Release --output-on-failure --timeout 60
    $result = $LASTEXITCODE
    Pop-Location
    if ($result -ne 0) { exit $result }
}

Build-And-Test "$env:GENERATOR" build_mingw
