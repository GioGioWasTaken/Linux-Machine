### Building from source

Whenever I install something using pacman, I am installing a pre-compiled binary. Someone already put in the computation power needed to compile this binary, and i'm using their efofrts. Building from source, is compiling it on your own.

# Why should you build from SRC?
1. **Customization**: You can enable or disable specific features and optimizations tailored to your needs.
2. **Security**: Building from source allows you to inspect the code and ensure there are no hidden vulnerabilities or backdoors.
3. **Optimization**: You can optimize the software for your specific hardware, potentially improving performance.
4. **Learning**: It provides insight into the software’s structure and build process, which can be educational.
5. **Latest Features**: Access to the latest features and bug fixes that may not yet be available in precompiled binaries.

# Why Do Files Weigh So Much Before Finishing Compilation?
1. **Intermediate Files**: The build process generates many intermediate files, such as object files (`.o`), precompiled headers, and temporary files.
2. **Debug Information**: Compiling with debug information (`-g` flag) creates larger files to store symbols and other debugging data.
3. **Dependencies**: The build process might include numerous dependencies, each contributing to the overall size.
4. **Multiple Build Configurations**: Some build systems compile multiple versions (e.g., debug and release) simultaneously.
5. **Source Files**: The source code itself, including documentation and auxiliary files, adds to the total size.
6. **Build Artifacts**: The build system might produce additional artifacts like logs, temporary build files, and cache files.

Once the compilation is complete, many of these intermediate and temporary files are not needed and can be deleted, significantly reducing the final size of the installed software.
