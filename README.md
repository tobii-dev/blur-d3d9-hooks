# blur-d3d9-hooks
WARNING: This project is still in development, and has not been tested on other systems / game versions.

The aim of this project is to create a small and simple library that allows us to run C++ code inside the game process.
Once that is working, we might move forward to implement a plugin system, where other plugins are loaded DLLs that can make use of this library.

## Features (so far)
The functionality so far is:
<details>
  <summary>A frame limiter</summary>
  <p>
  Set the limit in the <b>cfg.ini</b> config file. Most people use ~30 fps.
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
  Toggle it ON/OFF with <kbd>NUMPAD DIVIDE</kbd> or with the <code>tg</code> console command.
  </p>
  <p>If it is ON when you enter the car select menu, the game will bug. Toggle it ON only when you're already in the car select menu.<br>
  ~~This feature doesnt work for everyone (I belive it depends on the game version).~~ working for Blur.exe v1.2</p>
 </details>
 <details>
  <summary>A console (WiP)</summary>
  <p>You can type some commands into it...</p>
  <p>Change your username with the <code>name</code> command. The change will be visible when you enter the LAN menu.
  <br>See current fps with the <code>fps</code> command.
  <br>See current lobby info with the <code>info</code> command.
  <br>Toggle Single-Player DRITER mod with <code>tg</code> command.
  <br>Change the number of laps for the race with <code>laps <#n></code> command.
  <br>Better features to the console will be added soon :)</p>
 </details>
 <details>
  <summary>LAN lobby laps higher than 9</summary>
  <p>When hosting a LAN lobby, you can set the number of laps for the race to a number between 10 and 255. Example: <code>laps 20</code>.
  <br>When going over 127 laps, it will display the laps in the lobby as a negative number.
  <br>To make sure all the players in your lobby also have this updated value, open and close the lobby settings menu.
  <br>YOU WILL HAVE TO USE THE <code>laps</code> COMMAND TO BE ABLE TO CHANGE LOBBY SETTINGS AGAIN (just type "laps" into the console).
  <br>During the race, if you pick up a powerup after lap 127, you will not be able to pick it up again for the rest of the race.</p>
  <br>This will also allow you to do multiple laps on the Mount Haruna track. After crossing the finnish line, keep driving forward untill you clip trough the invisible wall at the end. The car will fall into  <b>t h e    v o i d</b>  and will be teleported back to the start of the track.
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
	* There was also a way to build it from the command line, using [MSBuild.exe](https://docs.microsoft.com/en-us/visualstudio/msbuild/msbuild), but I forgot how :upside_down_face:


## TODO
- [x] Clean up the d3d9 hooks
- [ ] SP laps
- [ ] Store LAN mods
- [ ] Add more hooks to game events
- [ ] Plugins
- [ ] Find IDE independent way to create DLL
