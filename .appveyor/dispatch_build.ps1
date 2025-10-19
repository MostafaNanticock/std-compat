param(
    [Parameter(Mandatory=$true)]
    [string]$Compiler,
    
    [Parameter(Mandatory=$true)]
    [string]$Generator
)

# Ensure full error messages are displayed
$ErrorActionPreference = "Continue"
$WarningPreference = "Continue"
$VerbosePreference = "Continue"

Write-Host "Dispatching build for compiler: $Compiler, generator: $Generator"

# Dispatch to compiler-specific script
$script = ".appveyor/$Compiler/build.ps1"
if (Test-Path $script) {
    Write-Host "Using compiler-specific build script: $script"
    & "$script"
    if ($LASTEXITCODE -ne 0) {
        throw "Build script failed with exit code $LASTEXITCODE"
    }
} else {
    Write-Host "No compiler-specific script found, using fallback generic build"
    # Fallback generic build
    cmake -S . -B build -G $Generator
    if ($LASTEXITCODE -ne 0) {
        throw "CMake configure failed with exit code $LASTEXITCODE"
    }
    
    cmake --build build --config Release
    if ($LASTEXITCODE -ne 0) {
        throw "CMake build failed with exit code $LASTEXITCODE"
    }
    
    Push-Location build
    try {
        ctest -C Release --output-on-failure --timeout 60
        if ($LASTEXITCODE -ne 0) {
            throw "Tests failed with exit code $LASTEXITCODE"
        }
    } finally {
        Pop-Location
    }
}

Write-Host "Build completed successfully"
