with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "nix-build-view";
  src = ./.;
  buildInputs = [ ncurses cmake ];
  configurePhase ="";
  buildPhase = ''
    mkdir -p ${name}/build
    cd ${name}/build
    cmake .. && make
  '';
  installPhase = "mkdir -p $out/bin && mv nix-build-view $out/bin/.";
  meta = {
    description = "a monitor for nix-build";
    homepage = "http://blog.lastlog.de/posts/nix-build-view_using_ncurses/";
  };
}