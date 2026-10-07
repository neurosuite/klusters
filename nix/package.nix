{ lib
, stdenv
, src
, cmake
, ninja
, qtbase
, wrapQtAppsHook
, libneurosuite
}:

stdenv.mkDerivation {
  pname = "klusters";
  version = "3.0.0";
  inherit src;

  nativeBuildInputs = [ cmake ninja wrapQtAppsHook ];
  buildInputs = [ qtbase libneurosuite ];

  meta = {
    description = "Cluster cutting application for spike sorting";
    homepage = "https://neurosuite.github.io";
    license = lib.licenses.gpl3Plus;
    mainProgram = "klusters";
    platforms = lib.platforms.unix;
  };
}
