#!/usr/bin/env bash
set -euo pipefail

# -  PROPERTIES  - #

# get some incoming details about talos
talos_target="talos-"
talos_repo="rroessler/langs.talos"
talos_binary=$(command -v talos 2>&1 || true)
talos_dest=${TALOS_DIRECTORY_ROOT:-$HOME/.talos}
talos_upgrade=$([ -z $talos_binary ] && echo false || echo true)
talos_version=$([ -z $talos_binary ] && echo "" || $talos_binary --version)

talos_label_fatal=$([ $talos_upgrade = true ] && echo "Upgrade" || echo "Install")
talos_label_basic=$([ $talos_upgrade = true ] && echo "Upgrading" || echo "Installing")
talos_label_prefix=$([ $talos_upgrade = true ] && echo "upgrad" || echo "install")
talos_label_padding=$(printf "%${#talos_label_basic}s " "")

# resolve the version such that the correct tag is associated
talos_version=${talos_version/-main/}

# check if we have been told about no color
NO_COLOR=${NO_COLOR:-"0"}
if ! [ -t 0 ]; then NO_COLOR="1"; fi

OPT_CPID=
OPT_DRY=false
OPT_FORCE=false
OPT_TAG=latest

# prepare all the coloring details
C_CLEAR="\033[2K"
C_DIM=$([ $NO_COLOR != "0" ] || echo "\033[2m")
C_RESET=$([ $NO_COLOR != "0" ] || echo "\033[0m")
C_RED=$([ $NO_COLOR != "0" ] || echo "\033[1;31m")
C_GREEN=$([ $NO_COLOR != "0" ] || echo "\033[32m")

# -  METHODS  - #

# Handles successful exits.
exit_success() {
    echo -e "$C_GREEN$talos_label_basic$C_RESET: $C_DIM$1$C_RESET"
    exit # ensure we forcefully exit
}

# Handles failure exits.
exit_failure() {
    echo -e "${C_RED}Exception.$1$C_RESET: $2" >&2
    exit 1 # ensure we forcefully exit
}

# Handles validating "latest" versions.
version_latest() {
    local url="https://api.github.com/repos/$talos_repo/releases/latest"
    local command="curl -sL $url | jq -r '.tag_name'" # prepare the command
    spinner_run "Validating" "'$talos_target:latest'" eval $command
}

# Handles validating any incoming versions.
version_validate() {
    local url="https://api.github.com/repos/$talos_repo/tags"
    local command="curl -sL $url | jq -r '.[] | select(.name == \"$1\") | .name'"
    spinner_run "Validating" "'$talos_target:$1'" eval $command
}

# Handles resolving a suitable version.
version_resolve() {
    # ensure we wrap a suitable set of details
    if [[ $OPT_TAG =~ ^[0-9]+\.[0-9]+\.[0-9]+ ]]; then OPT_TAG="v$OPT_TAG"; fi

    # attempt finding the latest version as well
    if [[ $OPT_TAG = "latest" ]]; then
        # attempt getting the latest tag available
        OPT_TAG=$(version_latest)

        # force an immediate failure if the incoming version was not found
        if [ $OPT_TAG = null ]; then
            exit_failure "Validation" "Could not resolve '$talos_target:latest'"
        fi

        # can safely return since we have a valid "latest" tag
        return
    fi

    # we want to ensure the incoming version is valid now
    if [ -z $(version_validate "$OPT_TAG") ]; then exit_failure "Validation" "Invalid Talos tag '$OPT_TAG'"; fi
}

# Handles deciding platform labels.
platform_resolve() {
    # get the baseline platform name
    local platform=$(uname -ms)

    # and convert it to a suitable value
    case $platform in
    'MINGW64'*) talos_target+="windows-x64" ;;
    'Darwin x86_64') talos_target+="darwin-x64" ;;
    'Darwin arm64') talos_target+="darwin-arm64" ;;
    'Linux x86_64') talos_target+="linux-x64" ;;
    'Linux aarch64' | 'Linux arm64') talos_target+="linux-arm64" ;;
    *) exit_failure $talos_label_fatal "Unsupported platform '$platform'" ;;
    esac
}

# Handles preparing spinners.
spinner_prepare() { printf "\033[?25l" >&2; }

# Handles cleaing up after spinners.
spinner_cleanup() { printf "\033[?25h\033[0m" >&2; }

# Handles executing commands with a spinner.
spinner_run() {
    # prepare the parameters given
    local label="$1"
    local message="$2"
    shift 2 # remove

    # prepare the baseline frames to be used
    local frames_list=("⠋" "⠙" "⠹" "⠸" "⠼" "⠴" "⠦" "⠧" "⠇" "⠏")
    local frames_count=${#frames_list[@]} # count the total frames

    # start the command background
    "${@:-:}" &

    # bind the incoming command pid
    OPT_CPID=$!

    # setup trap to kill the running process
    trap 'kill $OPT_CPID &>/dev/null || true; exit' EXIT INT TERM

    # prepare a frame index to be used
    local frames_index=0

    # run the spinner whilst the command executes
    while kill -0 "$OPT_CPID" 2>/dev/null; do
        local frames_head="${frames_list[$frames_index]}" # get the current frame to show
        printf "\r%s $C_GREEN%s$C_RESET: $C_DIM%s$C_RESET" "$frames_head" "$label" "$message" >&2

        frames_index=$(((frames_index + 1) % frames_count))
        sleep 0.08 # wait a little before polling again
    done

    # clear the output after completion
    printf "\r\033[K" >&2

    # wait for the command to complete to get the exit-code
    wait $OPT_CPID
    local errc=$?

    # and return the result now
    return $errc
}

# Adds a "~" to a given path.
env_tildify() {
    if [[ $1 = $HOME/* ]]; then
        local rep=\~/
        echo "${1/$HOME\//$rep}"
    else
        echo "$1"
    fi
}

# Handles bootstrapping the $PATH with "talos".
env_bootstrap() {
    # prepare the installation directory now
    local binary="$talos_dest/bin"
    local shell=$(basename "$SHELL")
    local btldr=$(env_tildify $binary)

    # prepare the configuration items to be used
    local configs=()
    local refresh=()
    local commands=()

    # attempt determining the necessary configurations
    case $shell in
    fish)
        configs=("$HOME/.config/fish/config.fish")
        commands=("set --export PATH $binary \$PATH")
        ;;

    zsh)
        configs=("$HOME/.zshrc")
        commands=("export PATH=\"$binary:\$PATH\"")
        ;;

    bash)
        configs=("$HOME/.bash_profile" "$HOME/.bashrc")
        commands=("export PATH=\"$binary:\$PATH\"")
        ;;

    # for all items that fail, we break to print to user
    *) ;;
    esac

    # declare as requiring to set manually
    local manual=true

    # attempt writing to the given configuration now
    for config in "${configs[@]}"; do
        if [[ -n $config ]] && [[ -w $config ]]; then
            # prepare the tildified configuration
            local ctldr=$(env_tildify $config)

            # update the incoming configuration now
            {
                echo -e "\n# Talos Environment Variables"
                for cmd in "${commands[@]}"; do echo "$cmd"; done
            } >>"$config"

            # declare to the used about adding this item
            echo -e "$talos_label_padding ${C_DIM}Added '$btldr' to \$PATH in '$ctldr'$C_RESET"

            # add this command to the refresh handler
            refresh+=("source $ctldr")

            # declare as not needing to set manually
            manual=false
        fi
    done

    # show the manual prompt if necessary
    if [ $manual = true ]; then
        # alert the user about manual installations
        echo -e "$talos_label_padding ${C_DIM}Manually add '$btldr' to \$PATH for '$shell' or similar$C_RESET"
    fi

    # otherwise show all the necessary export commands now
    echo -e "$talos_label_padding ${C_DIM}To get started, run the following commands$C_RESET"
    for cmd in "${refresh[@]}"; do echo -e "$talos_label_padding     $C_DIM$cmd$C_RESET"; done
    echo -e "$talos_label_padding     ${C_DIM}talos --help$C_RESET" # and show the main prompt
}

# Handles parsing the incoming arguments
main_parse() {
    while [[ $# -gt 0 ]]; do
        case $1 in
        --dry) OPT_DRY=true ;;
        --force) OPT_FORCE=true ;;
        --tag)
            OPT_TAG=$2
            shift
            ;;

        *) ;;
        esac

        # shift this current argument off now
        shift
    done
}

# Prepare the installation handler now
main_install() {
    # hide the current cursor instance
    spinner_prepare

    # prepare a trap to handling incoming details
    trap spinner_cleanup EXIT INT TERM

    # resolve the baseline details
    platform_resolve
    main_parse "$@"
    version_resolve

    # set the local version string now
    local version=$OPT_TAG

    # check if we are just doing a dry-run or if there would be no override at all
    if [ $OPT_DRY = true ]; then exit_success "Would have tried ${talos_label_prefix}ing Talos '$version'"; fi
    if [[ $OPT_FORCE == false && $talos_version == $version ]]; then exit_success "Talos already upgraded to '$version'"; fi

    # prepare all the temporary file locations
    local tmp_dir=$(mktemp -d)
    local zip_odir="$tmp_dir/$talos_target"
    local zip_file="$tmp_dir/$talos_target.zip"

    # construct the necessary download url now
    local url="https://github.com/$talos_repo/releases/download/$version/$talos_target.zip"

    # attempt downloading with curl now
    local command="curl -sL -o '$zip_file' -w '%{response_code}' '$url'"
    local result=$(spinner_run "Downloading" "'$talos_target:$version'" eval $command)

    # handling incoming results now
    case $result in
    200) result='' ;;
    404) result="Could not find Talos '$version'" ;;
    500) result="Release endpoint is not available" ;;
    000) result="Script requires an internet connection" ;;
    *) result="Could not request Talos '$version'. Received response-code '$result'" ;;
    esac

    # stop on any incoming failure results
    if [[ -n $result ]]; then exit_failure "Download" $result; fi

    # remove the original location if it exists
    rm -rf $talos_dest

    # attempt unpacking the incoming archive now
    command="unzip -q '$zip_file' -d '$tmp_dir' && mv '$zip_odir' '$talos_dest'"
    spinner_run "Unpacking" "'$talos_target:$version'" eval $command

    # restore the cursor that we hid now
    spinner_cleanup

    # show the resulting success message for the user
    local success="Talos '$version' was ${talos_label_prefix}ed successfully!"
    echo -e "$C_GREEN$talos_label_basic$C_RESET: $C_DIM$success$C_RESET"

    # prepare the environment registration now
    if command -v talos >/dev/null; then exit; fi

    # otherwise we need to update the path now
    env_bootstrap
}

# -  RUNNER  - #

# only run main script if executed directly
if [ ${BASH_SOURCE[0]} = ${0} ]; then main_install "$@"; fi
