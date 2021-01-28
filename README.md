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
  Press <kbd>NUMPAD PLUS</kbd> or <kbd>NUMPAD MINUS</kbd> to change it while playing.
  </br>
  Press <kbd>NUMPAD MULTIPLY</kbd> to loop over common values.
  </br>
  Press <kbd>END</kbd> to toggle displaying a bar.
  </p>
 </details>
 <details>
  <summary>Drifter mod in singleplayer mode</summary>
  <p>
  Toggle it ON/OFF with <kbd>NUMPAD DIVIDE</kbd>
  </p>
  <p>If its ON when you enter the car select menu, the game will bug. Toggle it when you're already in the car select menu.<br>
  This feature doesnt work for everyone (I belive it depends on the game version).</p>
 </details>
 <details>
  <summary>A console (WiP)</summary>
  <p>You can type some commands into it...</p>
  <p>Change your username with the <code>name</code> command. The change will be visible when you enter the LAN menu.
  <br>See current fps with the <code>fps</code> command.
  <br>Better features to the console will be added soon :)</p>
 </details>
 <details>
  <summary>Save your username</summary>
  <p>Edit the <b>cfg.ini</b> config file, change the "<b>YOUR_NAME_HERE</b>" section to your prefered username</p>
 </details>

## How can I try it?
Download <b>d3d9.dll</b> and <b>cfg.ini</b> from [the releases page](https://github.com/tobii-dev/blur-d3d9-hooks/releases), and place them in the same directory as the <b>Blur.exe</b> executable.


To uninstall, just remove the files <b>d3d9.dll</b> and <b>cfg.ini</b> from where you installed them.

## Building from source
> If you want to compile the DLL from source, you need a compiler that can do that :)

[Microsoft Visual Studio](https://visualstudio.microsoft.com/vs/) is the IDE that I am using for this project.

It comes with the needed compilation tools & [MSBuild.exe](https://docs.microsoft.com/en-us/visualstudio/msbuild/msbuild), the build system.


To compile the DLL:
1. Clone this repository. `git clone https://github.com/tobii-dev/blur-d3d9-hooks`
2. Run `premake5.bat` to generate the project Visual Studio Solution `.sln` file.
	* You will find the file in the `build/` directory.
3. Open it in Visual Studio and build it.
	* There was also a way to build it from the command line, using MSBuild.exe, but I forgot how :upside_down_face:


## TODO
[DONE] Clean up the d3d9 hooks
- Add more hooks to game events
- Plugins
- Find IDE independent way to create DLL
