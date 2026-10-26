param (
    [Parameter(Mandatory=$true)]
    [string]$FileName
)

# Configuration
$cmakeExe = "C:\Program Files\CMake\bin\cmake.EXE"
$buildDir = "./build"
$executable = "./build/Compile.exe"
$logFile = "output.txt"

Write-Host "Processing... (Check $logFile for details)" -ForegroundColor Cyan

# Wrap the logic in a script block and redirect everything to the file
& {
    Write-Output "--- Build Started at $(Get-Date) ---"
    
    # Run CMake Build
    & $cmakeExe --build $buildDir --config Debug --target all -j 12 --

    if ($?) {
        Write-Output "`n--- Execution Output ($FileName) ---"
        & $executable $FileName
    }
    else {
        Write-Output "`nERROR: Build failed. Execution skipped."
    }
} > $logFile 2>&1

# Final status update to the console
if ($?) {
    Write-Host "Done! Output written to $logFile" -ForegroundColor Green
} else {
    Write-Host "Process failed. Check $logFile for errors." -ForegroundColor Red
}