# Klusters

Klusters is a powerful and easy-to-use cluster-cutting application designed to help
neurophysiologists sort action potentials recorded from multiple neurons on groups of
electrodes (e.g. tetrodes or multisite silicon probes). Developed at the Buzsáki lab.

Developed by Lynn Hazan (main developer), Laurent Montel (Qt3 to Qt4/5 porting), David Faure
(Qt3 to Qt4/5 porting), Michaël Zugaro (maintenance), Florian Franzen (OS X support,
maintenance) and Théotime de Charrin (Qt6 porting), distributed under the GNU General Public
License v3 or later.

If you use Klusters, please cite: L. Hazan, M. Zugaro, G. Buzsáki (2006). Klusters,
NeuroScope, NDManager: a free software suite for neurophysiological data processing and
visualization. *J Neurosci Methods* 155:207-216.

## Installing

Download a package for Linux (.deb, AppImage), macOS (.dmg) or Windows (installer or .zip)
from the [releases page](https://github.com/neurosuite/klusters/releases).

On Ubuntu 24.04 or newer, install the .deb together with the `libneurosuite3` package from
the same release:

```bash
sudo apt install ./libneurosuite3_*.deb ./klusters_*.deb
```

## Building

Requires CMake 3.16+, a C++17 compiler, Qt 6.4+ (Widgets, PrintSupport, Xml) and
[libneurosuite](https://github.com/neurosuite/libneurosuite) 3.x.

```bash
# with libneurosuite installed
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build

# or let CMake fetch and build libneurosuite as part of Klusters
cmake -B build -S . -DKLUSTERS_BUNDLE_NEUROSUITE=ON
```

On Ubuntu 24.04 the build dependencies are `cmake ninja-build qt6-base-dev`.
With Nix: `nix build` or `nix develop`. See [CHANGELOG.md](CHANGELOG.md) for changes.
