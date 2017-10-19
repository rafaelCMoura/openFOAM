# Compiling OpenFOAM Apps

## Configuration

Source OpenFOAM bashrc in root's .bashrc file. Run configurations with . .bashrc.
You need to make this to use wmake in root mode. Your compiled Apps will be placed
in /opt/platforms/linux64GccDPInt32Opt/bin directory.

## Required files

In you app's directory create a directory called "Make". Inside this directory
create two files.

-options
-files

Read the [details](https://cfd.direct/openfoam/user-guide/compiling-applications/)
in OpenFOAM user guide.