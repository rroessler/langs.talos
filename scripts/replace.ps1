#!/usr/bin/env pwsh

# -  PARAMETERS  - #

param(
    [String]$Source, # Talos Archive Source.
    [String]$Destination # Talos Home Folder.
);

# -  RUNNER  - #

# Replaces the desired destination with a source folder.
Remove-Item -Path "$Destination" -Recurse -Force -ErrorAction SilentlyContinue;
Move-Item -Path "$Source" -Destination "$Destination" -ErrorAction SilentlyContinue;
