![DebugTrace Banner](assets/banners/debug_trace_banner.svg)

# DebugTrace

Simple debug tracing for convenience

# Installation

The installation and build is tested on *ubuntu24.04 LTS*

## dependencies

## use cmake to install the header-only library

```bash
# change the next line to change the install prefix to your liking
INSTALL_PREFIX=/usr
mkdir ./build
cd build
cmake -Wno-dev -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} ..
cmake --build . --parallel $(nproc)
sudo cmake --install .
```
This will install the headers from the include-folder to `${INSTALL_PREFIX}/dkyb`

To use the headers in your code, make sure that ${INSTALL_PREFIX} is in the include directories of your project.
Include the file in your code e.g:
```c++
#define DO_TRACE_
#include <dkyb/traceutil.h>
```
## Powered by
Reduce the smells, keep on top of code-quality. Sonar Qube is run on every push to the `main` branch on GitHub.


[![SonarQubeCloud](assets/icons/logo-sonarqube-cloud-small.png)](https://sonarcloud.io/project/overview?id=kingkybel)
