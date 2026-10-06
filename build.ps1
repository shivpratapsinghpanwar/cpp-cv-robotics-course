<#
.SYNOPSIS
  Build (and run) a course exercise with one command.

.EXAMPLE
  .\build.ps1 day01_ex02            # build + run your exercise
  .\build.ps1 day01_ex02 -Solution  # build + run the reference solution (day01_sol02)
  .\build.ps1                       # build everything (no run)
  .\build.ps1 day01_ex02 -Release   # optimized build
  .\build.ps1 -List                 # show all available targets
#>
param(
    [Parameter(Position = 0)][string]$Target,
    [switch]$Solution,
    [switch]$Release,
    [switch]$List
)
$ErrorActionPreference = 'Stop'
$preset = if ($Release) { 'release' } else { 'debug' }

# 1) Make the MSVC compiler (cl.exe), CMake and Ninja available in this shell.
#    This only happens once per PowerShell window; afterwards it is instant.
if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    $vs = 'C:\Program Files\Microsoft Visual Studio\18\Community'
    if (-not (Test-Path $vs)) {
        $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
        if (Test-Path $vswhere) { $vs = & $vswhere -latest -property installationPath }
    }
    $vcvars = "$vs\VC\Auxiliary\Build\vcvars64.bat"
    if (-not $vs -or -not (Test-Path $vcvars)) {
        throw "Could not find Visual Studio with C++ tools. Install the 'Desktop development with C++' workload."
    }
    Write-Host "Setting up the Visual Studio C++ environment (once per window)..." -ForegroundColor DarkGray
    # Run vcvars64.bat in cmd, then copy the environment variables it sets into this PowerShell.
    cmd /c "`"$vcvars`" >nul 2>&1 && set" | ForEach-Object {
        if ($_ -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] }
    }
    # CMake + Ninja ship with Visual Studio.
    $env:PATH = "$vs\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;" +
                "$vs\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;$env:PATH"
    if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) { throw "Failed to set up the MSVC environment." }
}

Push-Location $PSScriptRoot
try {
    # 2) Configure (first time, or after you add a new day folder).
    cmake --preset $preset | Out-Null
    if ($LASTEXITCODE -ne 0) { cmake --preset $preset; throw "CMake configure failed." }

    if ($List) {
        cmake --build --preset $preset --target help |
            Select-String -Pattern '^(day\d\d_(ex|sol)\d+):' |
            ForEach-Object { $_.Matches[0].Groups[1].Value } | Sort-Object
        return
    }

    if ($Solution -and $Target) { $Target = $Target -replace '_ex(\d+)', '_sol$1' }

    # 3) Build.
    if ($Target) { cmake --build --preset $preset --target $Target }
    else         { cmake --build --preset $preset }
    if ($LASTEXITCODE -ne 0) { throw "Build failed - read the first error message above (it is usually the real one)." }

    # 4) Run.
    if ($Target) {
        $exe = Join-Path $PSScriptRoot "build\$preset\bin\$Target.exe"
        Write-Host "`n--- running $Target ---" -ForegroundColor Cyan
        & $exe
        Write-Host "--- exit code $LASTEXITCODE ---" -ForegroundColor Cyan
    }
}
finally {
    Pop-Location
}
