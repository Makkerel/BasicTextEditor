# CodeEditor

This is a basic text editor in C++ with the wxWidgets Library. Download the latest release on windows which includes the .exe file and run it on windows(this may trigger windows defender just tell it to run anyway). I currently do not have a way to run it easily outside of Windows.

# Installation/Compile

## Step 1
Have a Windows Machine and Install Visual Studio 2022 with C++ Development. I currently do not have a way to easily compile and build outside of Visual Studio.

## Step 2
Download and build [Wxwidgets Library](https://www.wxwidgets.org/downloads/) and build the library. 

## Step 3
Start the solution, go to properties and add the libary for **addtional include directories**. Then go to the linker settings add the **additional library directories** where the libaries were built. Note for the link if you have different platforms the libaries will be different.

## Step 4
You can now build the text editor.

# Future Features
- All Buttons in Status bar will actually work
- Saved Settings for the Text Editor
- More custom changes to the Scintilla Editting Component
