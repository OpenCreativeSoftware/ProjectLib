OCS ProjectLib
==============
**What is ProjectLib?**

OCS ProjectLib is a fully-featured library for reading and writing OCS project files.
Every OCS product (Timeline, Waveform and etc.) uses ProjectLib under the hood to open and manipulate various project files and their data.
ProjectLib source code is located at `src/lib/`

**Can it be used independently?**

Yes! ProjectLib can be built as a shared library and used freely in your projects.
Check `examples/` folder for code samples

OCS ProjectLibCLI
=================
ProjectLib provides a basic CLI-interface for managing .ocs files called ProjectLibCLI.
ProjectLibCLI source code is located at `src/cli/`
## CLI Usage Examples

### Creating new OCS project:
```
./ProjectLibCLI --path PATH --new --type TYPE
```
Where:
* `PATH` is a path to the new project
* `TYPE` is a project type (`timeline`/`raster`/`waveform` and etc.)

### Dump OCS project info
```
./ProjectLibCLI --path PATH --dump
```
Where:
* `PATH` is a path to the project you want to get a dump of

### Modify OCS project info
```
./ProjectLibCLI --path PROJECT_PATH --modify MODIFICATION_TYPE --modify-path MODIFICATION_PATH --modify-value MODIFICATION_VALUE_
```
Where:
* `PROJECT_PATH` is a path to .ocs project
* `MODIFICATION_TYPE` is a type of modification you want to make (can be either `header` or `project`)
* `MODIFICATION_PATH` is a path to a property you want to modify
* `MODIFICATION_VALUE` is a value you want to assign to a property

Modification example:
```
./ProjectLibCLI --path project.ocs --modify header --modify-path V1/ProjectName --modify-value "New Project Name"
```

OCS Project Structure
=====================
OCS project is essentially a .zip archive. You can unpack OCS project with any popular file manager.

OCS project structure looks like this:
```
PROJECT.OCS:
	| header.xml
	| project.xml
	| files/
	| ------ picture.jpg
	| ------ audio.wav and etc.
```
Where:
* `header.xml` is a header of a project
* `project.xml` is a main data of a project
* `files/` is a folder with all auxiliary files and assets