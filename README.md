# Rust CHOP
An experimental CPlusPlus CHOP that generates its channel data by calling into a Rust static library. Tested with TouchDesigner 088.

![Alt text](/screenshot.png?raw=true "Creating a sin wave from Rust")

## Before Building
Make sure you have the latest version of Rust installed and `cargo` is in your `PATH`. Also, you will need Visual Studio 2015 to compile the C++ project.

## Instructions
1. Navigate inside the `rust` folder.
2. Execute: `cargo build --release`. This will create `chop.lib` inside of the target directory.
3. Navigate inside the `cplusplus` folder and open the Visual Studio solution file.
4. Build the project in `release` mode. This will create `RustCHOP.dll` in the `Release` folder.
5. Open TouchDesigner, create a `CPlusPlus CHOP` and set its `dll` parameter to the path of `RustCHOP.dll`.