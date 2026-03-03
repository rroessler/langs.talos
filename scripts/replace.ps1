#!/usr/bin/env pwsh

# -  PARAMETERS  - #

param(
    # Talos Archive Source.
    [String]$Source,

    # Talos Home Folder.
    [String]$Destination 
);

# -  RUNNER  - #

# Replaces the desired destination with a source folder.
Remove-Item -Path "$Destination" -Recurse -Force -ErrorAction SilentlyContinue;
Move-Item -Path "$Source" -Destination "$Destination" -ErrorAction SilentlyContinue;
