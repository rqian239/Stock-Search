# Stock-Search
Created by Richard Qian, Dylan DePasquale, and Douglas Ta

Stock Search is an easy-to-use, command-line application for searching notable days of given stocks based on a couple of criteria: best/worst returns and largest/smallest intraday range.

By default, you may select stocks from the Dow 30 and conduct your search by following the instructions in the CLI.

Our application also measures the speed of two sorting methods used in our search: heap sort and merge sort.

## How to Build and Run Stock-Search

There are two main ways to build and run Stock-Search: in the CLion IDE or in your terminal.

## Build/Run in CLion

1.  Clone the repository.
2.  Open the project in your CLion IDE (I am using version 2021.1.1).
3.  CLion should automatically load the project and automatically run the CMake configuration.
4.  Check your run/debug configurations in the top-left. There should be a CMake Application configuration created by CLion.
5.  Build the project ('Ctrl+F9' or 'Cmd+F9') and run the configuration ('Shift+F10').


## Build/Run in the Terminal
1. Clone the repository.
2. Ensure you have CMake installed (I am using cmake version 3.28.3).
3. Navigate to the project root directory and cd into `build/`.
4. Execute `cmake -B. -S..` and then `cmake --build .`
5. The executable should be found in the Debug directory within the build directory.
6. Run the exe in the terminal: `Stock_Search.exe`


