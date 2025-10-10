$ErrorActionPreference = "Stop"

# Get the directory where this script is located
$hookSourceDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Get the git hooks directory
$repoRoot = git rev-parse --show-toplevel
$gitHooksDir = Join-Path (Join-Path $repoRoot ".git") "hooks"

Write-Host "Installing Git hooks from $hookSourceDir to $gitHooksDir"

# Find all files without extensions (excluding this script)
$hookFiles = Get-ChildItem -Path $hookSourceDir -File | Where-Object { 
    -not $_.Extension -and $_.Name -ne "install-git-hooks"
}

foreach ($hookFile in $hookFiles) {
    $sourcePath = $hookFile.FullName
    $targetPath = Join-Path $gitHooksDir $hookFile.Name
    
    Write-Host "Installing $($hookFile.Name)..."
    Copy-Item $sourcePath $targetPath -Force
    
    # Make executable on Unix/Linux/macOS
    if ($IsLinux -or $IsMacOS) {
        & chmod +x $targetPath
    }
}

Write-Host "Git hooks installation complete."
