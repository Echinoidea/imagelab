# cpp env flake template
{
  description = "imagelab";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        config = {
          permittedInsecurePackages = [
          ];
          allowUnfree = true;
          allowUnfreePredicate = pkg: true;
        };
      };
    in {
      devShells.default = pkgs.mkShell {
        name = "imagelab";
        NIX_CONFIG = "experimental-features = nix-command flakes";
        shellHook = ''
        '';
        nativeBuildInputs = with pkgs; [
          cmake
        ];
        buildInputs = with pkgs; [
          clang
          gcc
          lld
          libcxx
          libgcc
          gnumake
          lldb
        ];
      };
    });
}
