To export in GCC on Linux :

g++ PyCalc-CE.cpp -o PyCalc-CE -lcurl -lm

Needs libcurl-devel package.

Debain based Distro : sudo apt install libcurl-devel
Red Hat : sudo yum install libcurl-devel
Fedora : sudo dnf install libcurl-devel
Arch sudo pacman -S libcurl-devel

Similarly to export on Windows, install mingw-curl.

Export Command for Windows :

x86_64-w64-mingw32-g++ PyCalc-CE.cpp -o PyCalc-CE.exe -std=c++23 -Wall -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib -lcurl
