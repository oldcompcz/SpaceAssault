# SpaceAssault
DOS space shooter in ASCII.

## Development setup

1. Unpack copy of Borland's TurboC somewhere.
2. Pull this repository into a working copy.
3. Make a copy of `MAKEFILE.LOC.template` named `MAKEFILE.LOC` and update it's contents to match Your environment.
4. Run DosBox so it sees `turboc` and Your working copy. For example:
  ```bat
  start "Space Assault dev" "C:\Program Files (x86)\DOSBox-0.74\DOSBox.exe" -c "mount C C:\Data\projects\dos" -c "C:" -c "cd spaceass" -c "set PATH=C:\turboc\bin" -noconsole
  ```
5. Simply type `make` to recompile and build the project.
