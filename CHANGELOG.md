# Changelog

All notable changes to this project are documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [3.0.0] - unreleased

### Changed
- Ported to Qt 6 (6.4 or newer). Qt4 and Qt5 are no longer supported. Source port by
  Théotime de Charrin (MOBS team).
- Builds with CMake 3.16 and C++17 against libneurosuite 3 (formerly libklustersshared),
  which can also be built as part of Klusters (`-DKLUSTERS_BUNDLE_NEUROSUITE=ON`).
- Installs a desktop entry and AppStream metadata under the ID `io.github.neurosuite.Klusters`.
- Windows and macOS packages bundle the Qt runtime (Windows also the MSVC runtime) and show the handbook with the
  built-in viewer (QTextBrowser), as does the AppImage. The .deb uses QtWebEngine.
- The handbook is found relative to the executable, so relocated installs show it.
- Licence file corrected to GPL-3.0-or-later, matching the source headers.

### Removed
- Qt4/Qt5 and KDE4 build code and the old `depends` packaging helper.
