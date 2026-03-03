#!/usr/bin/env pwsh

# -  PARAMETERS  - #

param(
    [Switch]$Schedule = $false,
    [String]$Location = "${Home}\.talos"
);

# -  PROPERTIES  - #

# check if we can actually output colors or not
$C_NONE = if ($env:NO_COLOR -or -not $IsPty) { $true } else { $false }

$C_DIM = if ($C_NONE) { "" } else { [char]27 + "[2m" };
$C_RESET = if ($C_NONE) { "" } else { [char]27 + "[0m"; };
$C_GREEN = if ($C_NONE) { "" } else { [char]27 + "[32m"; };

# -  RUNNER  - #

if ($Schedule) {
    # prepare the scheduled job trigger to be used (this is to bypass when "talos.exe" calls this script)
    $trigger = New-ScheduledTaskTrigger -Once -At (Get-Date).AddSeconds(1);
    $settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries;
    $principal = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive;

    # to ensure that our action runs without show a window we must call it via the preinstalled "conhost.exe"
    $action = New-ScheduledTaskAction -Execute 'conhost.exe' -Argument "--headless powershell.exe -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File `"$PSScriptRoot\remove.ps1`" -Location `"$Location`"";

    # then we want to schedule the incoming job to replace the files
    Register-ScheduledTask -TaskName "Remove-Talos" -Action $action -Trigger $trigger -Principal $principal -Settings $settings -Force | Out-Null;
}

# otherwise we can safely remove the location (should not be running)
else {
    Remove-Item -Path $Location -Recurse -Force | Out-Null;
}

# declare that a success occured
Write-Host "${C_GREEN}Removing${C_RESET}: ${C_DIM}Successfully uninstalled Talos!${C_RESET}";
