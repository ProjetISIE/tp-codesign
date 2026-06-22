{
  description = "Nix flake Verilog development environment";
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
          quartusUnwrapped = pkgs-quartus.quartus-prime-lite-unwrapped.override {
            supportedDevices = [ "Cyclone IV" ];
          };
          quartusWrapped = pkgs-quartus.quartus-prime-lite.override { supportedDevices = [ "Cyclone IV" ]; };
        in
        {
          default =
            (pkgs.buildFHSUserEnv {
              name = "nios2-dev-env";
              targetPkgs =
                p:
                with p;
                [
                  bashInteractive
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
                  lcov
                  jq
                  quartusWrapped
                ]
                ++ lib.optionals stdenv.isLinux [
                  clang-uml # UML diagram generator
                  cppcheck # C++ Static analysis
                  socat # Serial terminal for manual testing
                  valgrind # Debugging and profiling
                ];
              multiPkgs =
                p: with p; [
                  ncurses5
                  zlib
                  glib
                ];
              profile = ''
                export PATH=${quartusUnwrapped}/nios2eds/bin:${quartusUnwrapped}/nios2eds/bin/gnu/H-x86_64-pc-linux-gnu/bin:$PATH
              '';
            }).env;
        }
      );
    };
}
