{
  description = "QMK userspace dev shell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { nixpkgs, ... }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-darwin"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      devShells = forAllSystems (
        pkgs:
        let
          # Boards are the keyboards in qmk.json. Every keymap here is "thomashexton".
          listBoards = ''
            echo "Boards:"
            ${pkgs.jq}/bin/jq -r '.build_targets[][0]' "$QMK_USERSPACE/qmk.json" | sed 's/^/  /'
          '';

          qmk-sync = pkgs.writeShellApplication {
            name = "qmk-sync";
            runtimeInputs = [ pkgs.git ];
            text = ''
              for repo in "$QMK_USERSPACE" "$QMK_HOME"; do
                if [ -n "$(git -C "$repo" status --porcelain --untracked-files=no)" ]; then
                  echo "Uncommitted changes in $repo; commit or stash them first." >&2
                  exit 1
                fi
              done
              echo "Pulling qmk_userspace..."
              git -C "$QMK_USERSPACE" pull --recurse-submodules
              echo "Pulling qmk_firmware..."
              git -C "$QMK_HOME" pull
              git -C "$QMK_HOME" submodule update --init --recursive
            '';
          };

          qmk-build = pkgs.writeShellApplication {
            name = "qmk-build";
            runtimeInputs = [ pkgs.qmk ];
            text = ''
              if [ $# -eq 0 ]; then
                exec qmk userspace-compile
              fi
              exec qmk compile -kb "$1" -km thomashexton
            '';
          };

          qmk-flash = pkgs.writeShellApplication {
            name = "qmk-flash";
            runtimeInputs = [ pkgs.qmk ];
            text = ''
              if [ $# -eq 0 ]; then
                echo "Usage: qmk-flash <board>"
                ${listBoards}
                exit 1
              fi
              echo "Put the keyboard in bootloader mode when asked."
              exec qmk flash -kb "$1" -km thomashexton
            '';
          };
        in
        {
          default = pkgs.mkShell {
            # qmk brings the CLI plus the ARM/AVR toolchains and flashing tools.
            packages = [
              pkgs.qmk
              qmk-sync
              qmk-build
              qmk-flash
            ];

            # Expects qmk_firmware (thomashexton/qmk_firmware, thomashexton-boards)
            # cloned next to this repo: ~/qmk/qmk_firmware, ~/qmk/qmk_userspace.
            shellHook = ''
              root="$(git rev-parse --show-toplevel)"
              export QMK_USERSPACE="$root"
              export QMK_HOME="$(dirname "$root")/qmk_firmware"
              if [ ! -d "$QMK_HOME" ]; then
                echo "qmk_firmware not found at $QMK_HOME" >&2
              fi
              cat <<'HELP'
              QMK dev shell
                qmk-sync            pull userspace, modules and firmware fork
                qmk-build [board]   build one board, or all boards
                qmk-flash <board>   build and flash (no board: list boards)
              HELP
            '';
          };
        }
      );
    };
}
