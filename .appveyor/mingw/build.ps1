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
    
    # Check for make tools that CMake looks for
    Write-Host "Make tools available:" -ForegroundColor Yellow
    $makeTools = @("mingw32-make.exe", "make.exe", "gmake.exe")
    foreach ($tool in $makeTools) {
        $found = Get-Command $tool -ErrorAction SilentlyContinue
        if ($found) {
            Write-Host "  ✓ $tool found at: $($found.Source)" -ForegroundColor Green
        } else {
            Write-Host "  ✗ $tool not found" -ForegroundColor Red
        }
    }
    
    # List all executables in MinGW path for debugging
    if (Test-Path $env:MINGW_PATH) {
        Write-Host "All .exe files in MinGW path:" -ForegroundColor Yellow
        Get-ChildItem $env:MINGW_PATH -Filter "*.exe" | ForEach-Object { 
            Write-Host "  - $($_.Name)" -ForegroundColor Gray
        }
    }
    
    Write-Host "=================================" -ForegroundColor Cyan
}

function Build-And-Test($Generator, $Dir) {
    Show-MinGW-Info
    
    # Find and set make program explicitly for CMake
    $makeProgram = $null
    $makeTools = @("mingw32-make.exe", "make.exe", "gmake.exe")
    foreach ($tool in $makeTools) {
        $found = Get-Command $tool -ErrorAction SilentlyContinue
        if ($found) {
            $makeProgram = $found.Source
            Write-Host "Using make program: $makeProgram" -ForegroundColor Green
            break
        }
    }
    
    Write-Host "=== CMake Configure ==="
    $actualGenerator = $Generator
    # If mingw32-make.exe is missing but make.exe is present, use Unix Makefiles
    if (-not (Get-Command "mingw32-make.exe" -ErrorAction SilentlyContinue) -and (Get-Command "make.exe" -ErrorAction SilentlyContinue)) {
        Write-Host "mingw32-make.exe not found, but make.exe is present. Switching generator to 'Unix Makefiles'." -ForegroundColor Yellow
        $actualGenerator = "Unix Makefiles"
    }
    
    if ($makeProgram) {
        cmake -S . -B $Dir -G "$actualGenerator" -DCMAKE_MAKE_PROGRAM="$makeProgram"
    } else {
        cmake -S . -B $Dir -G "$actualGenerator"
    }
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
