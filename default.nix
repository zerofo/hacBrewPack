{ stdenv }:

stdenv.mkDerivation rec {
  pname = "hacBrewPack";
  version = "3.16";

  src = ./src;

  patches = [];

  preBuild = ''
    mv config.mk.template config.mk
  '';

  makeFlags = [ "CC=${stdenv.cc.targetPrefix}cc" ];
  enableParallelBuilding = true;

  installPhase = ''
    install -D hacbrewpack $out/bin/hacbrewpack
  '';

  meta = {
    homepage = "https://github.com/gayhearts/hacBrewPack";
    description = "Make NCAs/NSPs from Nintendo Switch homebrews";
    longDescription = "hacBrewPack is a tool for creating Nintendo Switch NCAs (Nintendo Content Archive) from homebrews and pack them into NSPs (Nintendo Submission Package)
    Thanks: SciresM, yellows8, Adubbz, SwitchBrew";
    license = licenses.gpl2;
    platforms = platforms.unix;
    mainProgram = "hacBrewPack";
  };
}
