# elk
             

## tools
* [ ] link: link with library, or local file: (echo "file;compileinfo" >>
      config.con)
      If links with remote library has to provide the repo prefix. If not
      provided elk will search for stuff and ask if right thing was found
      
* [ ] embed: embedded tool for AVR development
    - [ ] init
    - [ ] config
    - [ ] build
    - [ ] upload
    - [ ] monitor
    - [ ] generate
* [ ] remote control stuff
    - [ ] sync: sync remotes with upstream
    - [ ] being able to alias stuff
    - [ ] pack: pack project into independent package
* [X] build: only compiles thing if forced or if changes occured
      options:
        - --recompile
        - --extra-flags
        
* [ ] test: gtest
* [ ] fetch: download all remote-packages

## Model
* packages are locate through remotes:
  
  git repositor that contain 'package.con' files which describe, where packages
  are located how they are to be compiled and so on...
  
* tool system: have 'tools.c' file where you can include a tool. a tool would
  consist of a c library with a single public function that will be called on
  the associated keywor
  
* con files: c object notations basicly struct initialisations that are loaded
  into single memory block for parsing.
