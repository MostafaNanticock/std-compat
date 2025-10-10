$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$output = Join-Path $root "..\appveyor.merged.yml"

Write-Host "Merging matrix fragments..."

# Simple YAML parser for matrix entries
function Parse-SimpleYaml {
    param([string]$content)
    
    $matrixEntries = @()
    $currentEntry = @{}
    $inEntry = $false
    
    foreach ($line in ($content -split "`n")) {
        $trimmed = $line.Trim()
        if ($trimmed -eq "" -or $trimmed.StartsWith("#")) { continue }
        
        if ($trimmed.StartsWith("-")) {
            # Save previous entry if it exists
            if ($currentEntry.Count -gt 0) {
                $matrixEntries += $currentEntry
            }
            # Start new matrix entry
            $currentEntry = @{}
            $inEntry = $true
            
            # Check if there's a key-value pair on the same line as the dash
            $restOfLine = $trimmed.Substring(1).Trim()
            if ($restOfLine -match "^([^:]+):\s*(.*)$") {
                $key = $matches[1].Trim()
                $value = $matches[2].Trim()
                # Remove quotes if present
                if ($value.StartsWith('"') -and $value.EndsWith('"')) {
                    $value = $value.Substring(1, $value.Length - 2)
                }
                $currentEntry[$key] = $value
            }
            continue
        }
        
        if ($inEntry -and $trimmed -match "^([^:]+):\s*(.*)$") {
            $key = $matches[1].Trim()
            $value = $matches[2].Trim()
            # Remove quotes if present
            if ($value.StartsWith('"') -and $value.EndsWith('"')) {
                $value = $value.Substring(1, $value.Length - 2)
            }
            $currentEntry[$key] = $value
        }
    }
    
    # Don't forget the last entry
    if ($currentEntry.Count -gt 0) {
        $matrixEntries += $currentEntry
    }
    
    return @{ matrix = $matrixEntries }
}

$entries = @()
Get-ChildItem -Path $root -Directory | ForEach-Object {
    $file = Join-Path $_.FullName "matrix.yml"
    if (Test-Path $file) {
        Write-Host "Processing $($_.Name)/matrix.yml"
        $content = Get-Content $file -Raw
        $yaml = Parse-SimpleYaml $content
        if ($yaml.matrix) { 
            $entries += $yaml.matrix 
            Write-Host "  Found $($yaml.matrix.Count) matrix entries"
        }
    }
}

if (-not $entries) {
    Write-Error "No matrix entries found!"
    exit 1
}

# Simple YAML generator
function Convert-ToSimpleYaml {
    param($object, [int]$indent = 0)
    
    $spaces = "  " * $indent
    $result = ""
    
    if ($object -is [hashtable] -or $object -is [PSCustomObject]) {
        foreach ($key in $object.Keys) {
            $value = $object[$key]
            if ($value -is [array]) {
                $result += "$spaces${key}:`n"
                foreach ($item in $value) {
                    if ($item -is [hashtable] -or $item -is [PSCustomObject]) {
                        $result += "$spaces  - "
                        $keys = @($item.Keys)
                        for ($i = 0; $i -lt $keys.Count; $i++) {
                            $subKey = $keys[$i]
                            $subValue = $item[$subKey]
                            if ($i -eq 0) {
                                $result += "${subKey}: $subValue`n"
                            } else {
                                $result += "$spaces    ${subKey}: $subValue`n"
                            }
                        }
                    } elseif ($item -is [string] -and $item.Contains("`n")) {
                        # Handle multiline strings with proper indentation
                        $result += "$spaces  - |`n"
                        foreach ($line in ($item -split "`n")) {
                            $result += "$spaces    $line`n"
                        }
                    } else {
                        $result += "$spaces  - $item`n"
                    }
                }
            } elseif ($value -is [hashtable] -or $value -is [PSCustomObject]) {
                $result += "$spaces${key}:`n"
                $result += Convert-ToSimpleYaml $value ($indent + 1)
            } elseif ($value -is [string] -and $value.Contains("`n")) {
                # Handle multiline strings
                $result += "$spaces${key}: |`n"
                foreach ($line in ($value -split "`n")) {
                    $result += "$spaces  $line`n"
                }
            } else {
                $result += "$spaces${key}: $value`n"
            }
        }
    }
    
    return $result
}

# Add SCRIPT environment variable to each matrix entry based on compiler
foreach ($entry in $entries) {
    if ($entry["COMPILER"] -eq "mingw") {
        $entry["SCRIPT"] = "ci/build-mingw.ps1"
    } elseif ($entry["COMPILER"] -eq "msvc") {
        $entry["SCRIPT"] = "ci/build-msvc.ps1"
    }
}

$buildScript = @"
ps: |
  `$script = `$env:SCRIPT
  if (-not (Test-Path `$script)) { Write-Error "Missing build script: `$script"; exit 1 }
  & `$script
"@

$final = @{
    #
    # This file is automatically generated by .appveyor/merge_matrices.ps1
    # This is done through a Git pre-commit hook to ensure appveyor.yml is always up to date.
    #
    # DO NOT EDIT THIS FILE MANUALLY
    #
    version = "1.0.{build}"
    environment = @{ matrix = $entries }
    build_script = $buildScript
}

$yamlContent = Convert-ToSimpleYaml $final
Set-Content $output -Value $yamlContent -Encoding utf8
Write-Host "Unified matrix written to $output ($($entries.Count) total entries)"
