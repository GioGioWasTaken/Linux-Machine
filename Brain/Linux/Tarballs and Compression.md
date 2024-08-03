## Tarballs
Tarballs are an archiving file format. 

### Archiving
Archiving is the action of taking many files, and essentially appending them to one another. Making them a linear format.

Tar, short for "tape archive," is a command-line utility used to create, manipulate, and extract files from archives in the Unix and Linux environments. Without compression, tar simply combines multiple files and directories into a single archive file, with the .tar extension. It does not compress the files; it only bundles them together.

### Zipping/compression of tar files
tar files are not zipped on their own. Most of the time they are compressed using `gzip`, which uses the deflate algorithm to zip files.
### Why are compressed files so useful?
Since modern CPU's are much faster than internet connection, it is more efficient for one machine to compress, and for the other to decompress, than to transfer a fully sized file over the internet.

### Why tar over zip?

zip files are built for windows, and are not made to hold all the custom proprities a Linux file might have (think about what you see when you use `ls -l` on a file.)
### Why zip over tar?

.zip files are more like .gz.tar files. They append already compressed versions. Which means we can decompress files by index.

### tar.gz and gz.tar each have their advantage 



### Why Do Files Weigh So Much Before Finishing Compilation?
1. **Intermediate Files**: The build process generates many intermediate files, such as object files (`.o`), precompiled headers, and temporary files.
2. **Debug Information**: Compiling with debug information (`-g` flag) creates larger files to store symbols and other debugging data.
3. **Dependencies**: The build process might include numerous dependencies, each contributing to the overall size.
4. **Multiple Build Configurations**: Some build systems compile multiple versions (e.g., debug and release) simultaneously.
5. **Source Files**: The source code itself, including documentation and auxiliary files, adds to the total size.
6. **Build Artifacts**: The build system might produce additional artifacts like logs, temporary build files, and cache files.

Once the compilation is complete, many of these intermediate and temporary files are not needed and can be deleted, significantly reducing the final size of the installed software.
