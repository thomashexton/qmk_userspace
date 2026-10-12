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
      devShells = forAllSystems (pkgs: {
        default = pkgs.mkShell {
          # qmk brings the CLI plus the ARM/AVR toolchains and flashing tools.
          packages = [ pkgs.qmk ];

          # Expects qmk_firmware (thomashexton/qmk_firmware, thomashexton-boards)
          # cloned next to this repo: ~/qmk/qmk_firmware, ~/qmk/qmk_userspace.
          shellHook = ''
            root="$(git rev-parse --show-toplevel)"
            export QMK_USERSPACE="$root"
            export QMK_HOME="$(dirname "$root")/qmk_firmware"
            if [ ! -d "$QMK_HOME" ]; then
              echo "qmk_firmware not found at $QMK_HOME" >&2
            fi
          '';
        };
      });
    };
}
