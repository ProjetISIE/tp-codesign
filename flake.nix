{
  description = "Nix flake DE2-115 development environment";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    nixpkgs-quartus.url = "github:NixOS/nixpkgs/788c34d";
  };
  outputs =
    {
      self,
      nixpkgs,
      nixpkgs-quartus,
    }:
    let
      forEachSupportedSystem =
        f:
        nixpkgs.lib.genAttrs [ "x86_64-linux" ] (
          system:
          f {
            pkgs = import nixpkgs {
              inherit system;
              config.allowUnfree = true;
            };
            pkgs-quartus = import nixpkgs-quartus {
              inherit system;
              config.allowUnfree = true;
            };
          }
        );
    in
    {
      devShells = forEachSupportedSystem (
        {
          pkgs,
          pkgs-quartus,
        }:
        let
          quartusUnwrapped =
            pkgs-quartus.callPackage "${nixpkgs-quartus}/pkgs/applications/editors/quartus-prime/quartus.nix"
              {
                supportedDevices = [ "Cyclone IV" ];
              };
        in
        {
          default =
            (pkgs.buildFHSEnv {
              name = "nios2-dev-env";
              targetPkgs =
                p: with p; [
                  clang-tools # Clang CLIs, including LSP
                  cmake-format # CMake formatter
                  cmake-language-server # Cmake LSP
                  doxygen # Documentation generator
                  lldb # Clang debug adapter
                  gnumake
                  iverilog # Icarus Verilog compiler
                  svls # SystemVerilog LSP
                  verilator
                  vhd2vl
                  quartusUnwrapped
                  glib
                  zlib
                  freetype
                  fontconfig
                  libx11
                  libxext
                  libxrender
                  libxrandr
                  libxft
                  libice
                  libsm
                  libxtst
                  libxi
                  libxml2
                  libxcrypt-legacy
                ];
              multiPkgs =
                p: with p; [
                  ncurses5
                  zlib
                  glib
                  freetype
                  fontconfig
                  libx11
                  libxext
                  libxrender
                  libxrandr
                  libxft
                  libice
                  libsm
                  libxtst
                  libxi
                  libxml2
                  libxcrypt-legacy
                ];
              profile = ''
                export PATH=${quartusUnwrapped}/quartus/bin:${quartusUnwrapped}/qsys/bin:${quartusUnwrapped}/nios2eds/bin:${quartusUnwrapped}/nios2eds/bin/gnu/H-x86_64-pc-linux-gnu/bin:$PATH
              '';
            }).env;
        }
      );
    };
}
