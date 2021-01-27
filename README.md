# blur-d3d9-hooks
WARNING: This project is still in development, and has not been tested on other systems / game versions.

The aim of this project is to create a small and simple library that allows us to run C++ code inside the game process.
Once that is working, we might move forward to implement a plugin system, where other plugins are loaded DLLs that can make use of this library.

## Features (so far)
The functionality so far is:
<details>
  <summary>A frame limiter</summary>
  <p>
  Set the limit in the <b>cfg.ini</b> config file. Most people use 30 fps.
  </p>
  <p>
  Press <b>NUMPAD_PLUS</b> or <b>NUMPAD_MINUS</b> to change it while playing.
  </br>
  Press <b>NUMPAD_MULTIPLY</b> to loop over common values.
  </br>
  Press <b>END</b> to toggle displaying a bar.
  </p>
 </details>
 <details>
  <summary>Drifter mod in singleplayer mode</summary>
  <p>
  Toggle it ON/OFF with <b>NUMPAD_DIVIDE</b>
  </p>
  <p>If its ON when you enter the car select menu, the game will bug. Toggle it when you're already in the car select menu.<br>
  This feature doesnt work for everyone (I belive it depends on the game version).</p>
 </details>
 <details>
  <summary>A console (WiP)</summary>
  <p>You can type some commands into it...</p>
  <p>Change your username with the <b>name</b> command. The change will be visible when you enter the LAN menu.
  <br>See current fps with the <b>fps</b> command.
  <br>Better features to the console will be added soon :)</p>
 </details>
 <details>
  <summary>Save your username</summary>
  <p>Edit the <b>cfg.ini</b> config file, change the "YOUR_NAME_HERE" section to your prefered username</p>
 </details>

## How can I try it?
Download <b>d3d9.dll</b> and <b>cfg.ini</b> from the releases, and place them in your blur installation directory (where the <b>Blur.exe</b> executable is).
To uninstall, simply delete the files, rename them, or move them to a different directory.
</p>
If you want to compile the DLL yourself:
1) Clone this repository.
2) Run premake5.bat to generate a Visual Studio Solution file.
3) Open the generated .sln file (build/<b>blur-d3d9.sln</b>)
4) Build it. (There was also a way to build it from the command line, using MSBuild.exe, but I forgot how...)
