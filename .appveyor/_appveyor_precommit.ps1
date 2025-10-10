# _appveyor_precommit.ps1
# Ensure full error messages are displayed
$ErrorActionPreference = "Continue"
$WarningPreference = "Continue"
$VerbosePreference = "Continue"

$repoRoot = git rev-parse --show-toplevel
Set-Location $repoRoot

$matrixFiles = Get-ChildItem ".appveyor" -Recurse -Include *.yml | Sort-Object FullName
$hashBefore = ""
if (Test-Path "appveyor.yml") {
    $hashBefore = (Get-FileHash "appveyor.yml").Hash
}

Write-Host "[AppVeyor] Generating unified matrix..."
& .appveyor/merge_matrices.ps1

if (-not (Test-Path "appveyor.merged.yml")) {
    Write-Error "Merge failed: missing appveyor.merged.yml"
    exit 1
}

# Compare new vs existing
$hashAfter = (Get-FileHash "appveyor.merged.yml").Hash
if ($hashBefore -ne $hashAfter) {
    Write-Host "[AppVeyor] Detected changes - updating appveyor.yml"
    Copy-Item "appveyor.merged.yml" "appveyor.yml" -Force

    # Stage it in Git
    git add appveyor.yml
}

exit 0
