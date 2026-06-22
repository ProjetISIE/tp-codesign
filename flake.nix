{
  description = "Nix flake Verilog development environment";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    nixpkgs-quartus.url = "github:NixOS/nixpkgs/788c34d";
    # nixpkgs-quartus.url = "github:NixOS/nixpkgs/95776cb0c15d796f3907ddf302c5e9c0c5cb02f6";
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
        { pkgs, pkgs-quartus }:
        {
          default = pkgs.mkShell {
            packages =
              with pkgs;
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
                (pkgs-quartus.quartus-prime-lite.override { supportedDevices = [ "Cyclone IV" ]; })
              ]
              ++ lib.optionals stdenv.isLinux [
                clang-uml # UML diagram generator
                cppcheck # C++ Static analysis
                socat # Serial terminal for manual testing
                valgrind # Debugging and profiling
              ];
          };
        }
      );
    };
}
