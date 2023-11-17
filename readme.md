## Setup

- Install Simplicity Studio 5 (Latest)
- Connect Hardware using USB-C
- Install all the prompted updates/upgrades
- Install GeckoSDK (4.3.2 OR Latest) with both extenstions: Silicon Labs Matter - 2.1.1 and Silicon Labs Amazon Sidewalk
  SDK -
  1.2.2
- Make sure the system and every thing is up-to-date
- Follow
  the [link](https://community.silabs.com/s/article/Installing-EGIT-with-Simplicity-Studio-5-version-5-3-x?language=en_US)
  to setup and install git with Simplicity Studio
- Clone Repo
- In Simplicity Studio Click File -> Import
- Browse and select cloned repo folder
- From the Detected Project List Select silicon_labs_hardware - Simplicity Studio (.sls) and click Next
- Make sure the SDK, Board and Part are reflected correctly and click Next
- Change project name from silicon_labs_hardware_2 to silicon_labs_hardware (same repo name which will overwrite some
  files) and click Finish
- Simplicity Studio will load the project and add sdk files in there, it will make some changes to files which we can
  simple checkout before building the application
- Make sure there is no change while running `git status`

## Simplicity Studio Fix

If Simplicity studio fails to start (on MacOs) use the following command to fix it:

```shell
sudo codesign --force --sign - /Applications/Simplicity\ Studio.app 
```

## Start Application

To start the application follow these steps:

- Make sure the setup is done successfully and open the application
- Connect the hardware
- From the project explorer Right click the project (silicon_labs_hardware) and select Run As
- Click `1 Silicon Labs ARM Program`
- It will build the project and port it to the hardware

## Hardware Fix (When changes don't reflect)

Sometimes the changes don't reflect on hardware after the application is installed on it due to unknown reasons. To Fix
that we have to reset the hardware for this follow the steps:

- Click `Lanucher` from the top right panel and goto `EXAMPLE PROJECTS & DEMOS`
- Search for `blinky`
- Two projects will appear one with `CREATE` button and other one with `RUN`
- Click RUN and port that to the hardware
- This resets the hardware (somehow)
- Goto `Simplicity IDE` and install the application again, this time the changes will reflect correctly

## Create Binary of the project

To create the binary file make sure that you've built the project otherwise Right Click on project folder and
Click `Build Project`

Set the following ENV variables in console

```shell
export PATH_GCCARM=/Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/gnu_arm/10.3_2021.10
export PATH_SCMD=/Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/adapter_packs/commander/Commander.app/Contents/MacOS
```

make sure `create_bl_files.sh` is executable, if not run:

```shell
chmod -R 777 ./create_bl_files.sh
```

run the sh file:

```shell
./create_bl_files.sh
```

This will generate files in `output_gbl` folder and the file `application.gbl` is to be used for upgrading the firmware
through flutter app
