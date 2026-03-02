#!/usr/bin/env pwsh
param(
    # The incoming version.
    [String]$Tag = "latest",

    # Whether to write outputs.
    [Switch]$Dry = $false,

    # Forces writing of outputs.
    [Switch]$Force = $false
);

# -  PROPERTIES  - #

# check if we can actually output colors or not
$C_NONE = if ($env:NO_COLOR -or -not $IsPty) { $true } else { $false }

$C_CLEAR = [char]27 + "[2K";
$C_DIM = if ($C_NONE) { "" } else { [char]27 + "[2m" };
$C_RESET = if ($C_NONE) { "" } else { [char]27 + "[0m"; };
$C_RED = if ($C_NONE) { "" } else { [char]27 + "[1;31m"; };
$C_GREEN = if ($C_NONE) { "" } else { [char]27 + "[32m"; };

# check if Talos already exists currently
$TalosRepo = "rroessler/langs.talos";
$TalosBinary = try { (Get-Command "talos" -ErrorAction Stop).Path; } catch {};
$TalosVersion = try { & $TalosBinary --version } catch {};
$TalosUpgrade = $TalosBinary.Count -ne 0; # denote if we are upgrading
$TalosDest = if ($env:TALOS_DIRECTORY_ROOT) { $env:TALOS_DIRECTORY_ROOT; } else { "${Home}\.talos"; };

$TalosLabelFatal = if ($TalosUpgrade) { "Upgrade" } else { "Install" };
$TalosLabelBasic = if ($TalosUpgrade) { "Upgrading" } else { "Installing" };
$TalosLabelPrefix = if ($TalosUpgrade) { "upgrad" } else { "install" };

# resolve the version such that it has the correct tag associated
if ($TalosVersion -match "^(?<content>.*)-main$") { $TalosVersion = $matches['content']; }

# -  METHODS  - #

# Handles formating spinner messages.
function Format-Message {
    param([String]$Msg, [String]$Lbl = $TalosLabelBasic);
    return "${C_GREEN}${Lbl}${C_RESET}: ${C_DIM}$Msg${C_RESET}";
}

# Handles formating fatal exceptions.
function Format-Fatal {
    param([String]$Msg, [String]$Lbl = $TalosLabelFatal);
    return "${C_RED}Exception.${Lbl}${C_RESET}: $Msg";
}

# Handles exiting with a fatal exception.
function Exit-Fatal {
    param([String]$Msg, [String]$Lbl = $TalosLabelFatal);
    Write-Host (Format-Fatal -Msg $Msg -Lbl $Lbl);
    exit 1; # and exit forcefully now from process
}

# Handles exiting with a success result.
function Exit-Success {
    param([String]$Msg, [String]$Lbl = $TalosLabelBasic);
    Write-Host (Format-Message -Msg $Msg -Lbl $Lbl);
    exit 0;# and exit forcefully now from process
}

# Handles starting a spinner instance.
function Invoke-Spinner() {
    # prepare the incoming spinner details now
    param([ScriptBlock]$ScriptBlock, [Object[]]$ArgumentList = @(), [String]$Msg = "");

    # prepare the available frames to be used now
    $frames = @("⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏");

    # prepare the job to be executed now
    $job = Start-Job -ScriptBlock $ScriptBlock -ArgumentList $ArgumentList;

    # show our incoming details whilst possible
    while ($job.State -eq "Running") {
        foreach ($frame in $frames) {
            Write-Host "`r$frame $Msg" -NoNewline;
            Start-Sleep -Milliseconds 80; # sleep
        }
    }

    # clear the current output now
    Write-Host "$C_SHOW$C_CLEAR`r" -NoNewline;

    # receive the incoming results now
    $results = Receive-Job -Job $job;
    Remove-Job -Job $job; # remove

    # and return the jobs results now
    return $results;
}

# These three environment functions are roughly copied from https://github.com/prefix-dev/pixi/pull/692
# They are used instead of `SetEnvironmentVariable` because of unwanted variable expansions.
function Publish-Env {
    if (-not ("Win32.NativeMethods" -as [Type])) {
        Add-Type -Namespace Win32 -Name NativeMethods -MemberDefinition @"
[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
public static extern IntPtr SendMessageTimeout(
    IntPtr hWnd, uint Msg, UIntPtr wParam, string lParam,
    uint fuFlags, uint uTimeout, out UIntPtr lpdwResult);
"@
    }
    $HWND_BROADCAST = [IntPtr] 0xffff
    $WM_SETTINGCHANGE = 0x1a
    $result = [UIntPtr]::Zero
    [Win32.NativeMethods]::SendMessageTimeout($HWND_BROADCAST,
        $WM_SETTINGCHANGE,
        [UIntPtr]::Zero,
        "Environment",
        2,
        5000,
        [ref] $result
    ) | Out-Null
}

# Handles writing the desired output environment variables.
function Write-Env {
    param([String]$Key, [String]$Value)

    $RegisterKey = Get-Item -Path 'HKCU:'

    $EnvRegisterKey = $RegisterKey.OpenSubKey('Environment', $true)
    if ($null -eq $Value) {
        $EnvRegisterKey.DeleteValue($Key)
    }
    else {
        $RegistryValueKind = if ($Value.Contains('%')) {
            [Microsoft.Win32.RegistryValueKind]::ExpandString
        }
        elseif ($EnvRegisterKey.GetValue($Key)) {
            $EnvRegisterKey.GetValueKind($Key)
        }
        else {
            [Microsoft.Win32.RegistryValueKind]::String
        }
        $EnvRegisterKey.SetValue($Key, $Value, $RegistryValueKind)
    }

    Publish-Env
}

# Handles getting the current environment details.
function Get-Env {
    param([String] $Key)
    $RegisterKey = Get-Item -Path 'HKCU:'
    $EnvRegisterKey = $RegisterKey.OpenSubKey('Environment')
    $EnvRegisterKey.GetValue($Key, $null, [Microsoft.Win32.RegistryValueOptions]::DoNotExpandEnvironmentNames)
}

# Attempts finding the latest Talos version.
function Find-Talos-Latest([String]$target) {
    $message = Format-Message -Lbl "Validating" -Msg "'${target}:latest'";
    $version = Invoke-Spinner -Msg $message -ScriptBlock {
        param([String]$repo); # allow access to the given repository value now
        return (curl.exe -sL "https://api.github.com/repos/$repo/releases/latest" | ConvertFrom-Json).tag_name;
    } -ArgumentList $TalosRepo;

    # return if we have a valid version resolved
    if ($version.Count -ne 0) { return $version; }

    # otherwise error out since we could not validate the target
    Exit-Fatal -Lbl "Validation" -Msg "Could not resolve '${target}:latest'";
}

# Handles validating a talos version.
function Validate-Talos-Version([String]$version) {
    return Invoke-Spinner -Msg $message -ScriptBlock {
        param([String]$version, [String]$repo); # ensure we capture our params to be used
        $tags = try { curl.exe -fsL "https://api.github.com/repos/$repo/tags" | ConvertFrom-Json; } catch { @() };

        # check that each of the tags is available now
        foreach ($tag in $tags) {
            if ($tag.name -eq $version) { return $true; }
        }

        # if we reached here, then there is no valid tag available
        return $false;
    } -ArgumentList $version, $TalosRepo;
}

# Handles registering the path instance.
function Register-Talos-Path([String]$binary) {
    # only try adding to path if there isn't already a "talos.exe" in the path
    $path = (Get-Env -Key "Path") -split ';'

    # update the binary when we cannot find the original
    if ($path -notcontains $binary) {
        $path += $binary;
        Write-Env -Key 'Path' -Value ($path -join ';');
        $env:PATH = $path -join ';';
    }
}

# We install talos using it's own function in the unlikely case we need to recall anything.
function Install-Talos-Main {
    # prepare the incoming parameters to be used now
    param([String]$Tag);

    # resolve the incoming details about the installation
    $arch = "x64";
    $validated = $false;
    $target = "talos-windows-$arch";
    $version = if ($Tag -match "^\d+\.\d+\.\d+") { "v$Tag"; } else { $Tag; };

    # check if the requested tag actually exists firstly
    if ($version -eq "latest") {
        $version = Find-Talos-Latest $target;
        $validated = $true; # define as validated
    }

    # run some validation checks now as necessary
    $message = Format-Message -Lbl "Validating" -Msg "'${target}:$version'";
    if (-not $validated) { $validated = Validate-Talos-Version $version };

    # handle the resulting validation now
    if (-not $validated) { Exit-Fatal -Lbl "Validation" -Msg "Invalid Talos tag '$version'"; }
    if ($Dry) { Exit-Success -Msg "Would have tried ${TalosLabelPrefix}ing Talos '$version'"; }

    # we need to stop if the current version is the same
    if (-not $Force -and $version -eq $TalosVersion) {
        Exit-Success -Msg "Talos already upgraded to '$version'";
    }

    $tmpdir = "$([System.IO.Path]::GetTempPath())\talos";
    $zip_src = "$tmpdir\$target"; # prepare the source of the zip
    $zip_file = "$tmpdir\$target.zip"; # prepare zipped output location

    # ensure we remove the old temporary directory, and make a new-one
    Remove-Item -Path $tmpdir -Recurse -Force | Out-Null
    New-Item -Path $tmpdir -ItemType Directory -Force | Out-Null

    # construct the resulting url to be used now
    $url = "https://github.com/$TalosRepo/releases/download/$version/$target.zip";

    # attempt downloading with curl now
    $message = Format-Message -Lbl "Downloading" -Msg "'${target}:$version'";
    $download = Invoke-Spinner -Msg $message -ScriptBlock {
        param([String]$zip_file, [String]$url); # ensure we capture our params
        return curl.exe "-sL" "-o" "$zip_file" "-w" "%{response_code}" "$url";
    } -ArgumentList $zip_file, $url;

    # handle the incoming result of the request now
    $message = switch ($download) {
        200 { break; }
        404 { "Could not find Talos '$Tag'"; }
        500 { "Release endpoint is not available"; }
        000 { "Script requires an internet connection"; }
        default { "Could not request Talos '$Tag'. Received response-code '$download'" }
    };

    # stop on any incoming failures now
    if ($message) { Exit-Fatal -Lbl "Download" -Msg $message };

    # attempt unpacking into a suitable location now
    $message = Format-Message -Lbl "Unpacking" -Msg "'${target}:$version'";
    $unpack = Invoke-Spinner -Msg $message -ScriptBlock {
        # prepare the parameters to be used now
        param([String]$zip_file, [String]$source);

        try {
            # start by unpacking the incoming details
            $original = $global:ProgressPreference;
            $global:ProgressPreference = "SilentlyContinue";
            Expand-Archive "$zip_file" "$source" -Force | Out-Null;
            $global:ProgressPreference = $original;
        }
        catch { return "Could not unzip download, $_"; };

        # get the incoming target executable
        $executable = "$source\bin\talos.exe";

        # once unpacked, we firstly test the new binary
        if (-not (Test-Path $executable)) { return "Download was corrupted, could not find 'talos.exe'"; }
    } -ArgumentList $zip_file, $zip_src;

    Write-Host "Source: $tmpdir";

    # if we received an unpacking error, then show
    if ($unpack.Count -ne 0) { Exit-Fatal -Lbl "Unpack" -Msg $unpack; }

    # prepare environment registration
    Register-Talos-Path "$TalosDest\bin";

    # and finally show the user the resulting details
    Write-Host (Format-Message -Msg "Talos '$version' was ${TalosLabelPrefix}ed successfully!");

    # prepare the scheduled job trigger to be used (this is to bypass when "talos.exe" calls this script)
    $trigger = New-ScheduledTaskTrigger -Once -At (Get-Date).AddSeconds(1);
    $settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries;
    $principal = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive;

    # to ensure that our action runs without show a window we must call it via the preinstalled "conhost.exe"
    $action = New-ScheduledTaskAction -Execute 'conhost.exe' -Argument "--headless powershell.exe -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File `"$PSScriptRoot\replace.ps1`" -Source `"$zip_src`" -Destination `"$TalosDest`"";

    # then we want to schedule the incoming job to replace the files
    Register-ScheduledTask -TaskName "Replace-Talos" -Action $action -Trigger $trigger -Principal $principal -Settings $settings -Force | Out-Null;
}

# -  RUNNER  - #

# ensure we are actually running only on "x64" installations for now
if (-not ((Get-CimInstance Win32_ComputerSystem)).SystemType -match "x64-based") {
    Exit-Fatal -Msg "Talos is currently only available Windows x64 hosts";
}

try {
    # pre-hide the current cursor instance now
    [Console]::CursorVisible = $false;

    # actually attempt installing our instance
    Install-Talos-Main -Tag $Tag;
}

finally {
    $jobs = Get-Job; # get the running jobs
    if ($jobs.Count -ne 0) { Write-Host ""; }
    $jobs | Remove-Job -Force; # and clear them
    [Console]::CursorVisible = $true; # show again
}