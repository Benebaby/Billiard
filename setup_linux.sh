#!/bin/bash

echo "Choose your IDE:"
echo "(1) Eclipse CDT"
echo "(2) Unix Makefiles"
echo "(3) Sublime Text 2"
echo "(4) CodeBlocks"
echo "(5) KDevelop3"
echo "----------------------"

read ide

build_name=""
generator=""
case $ide in
1) 
	echo "Eclipse CDT - Unix Makefiles"
	build_name="Eclipse"
	generator="Eclipse CDT4 - Unix Makefiles"
	;;
2) 
	echo "Unix Makefiles"
	build_name="Makefiles"
	generator="Unix Makefiles"
	;;
3)
	echo "Sublime Text 2 - Unix Makefiles"
	build_name="Sublime_Text_2"
	generator="Sublime Text 2 - Unix Makefiles"
	;;
4)
	echo "CodeBlocks - Unix Makefiles"
	build_name="Codeblocks"
	generator="CodeBlocks - Unix Makefiles"
	;;
5)
	echo "KDevelop3 - Unix Makefiles"
	build_name="KDevelop3"
	generator="KDevelop3 - Unix Makefiles"
	;;
*) 
	echo "No valid generator chosen"
	exit 0
	;;
esac

echo "Choose build type:"
echo "(1) Debug"
echo "(2) Release"
echo "----------------------"

read buildtypeIn

buildtype=""
case $buildtypeIn in
1) 
	echo "Debug build"
	buildtype="Debug"
	;;
2) 
	echo "Release build"
	buildtype="Release"
	;;
*) 
	echo "No valid type chosen"
	exit 0
	;;
esac

params="-DCMAKE_BUILD_TYPE="$buildtype

echo "Make installable (Resource path will be set relative to execution)?"
echo "(1) No"
echo "(2) Yes"
echo ----------------------

read installable
case $installable in
1) 
	echo "Local test build"
	params=$params" -DMAKE_INSTALLABLE=FALSE"
	;;
2) 
	echo "Installable build"
	params=$params" -DMAKE_INSTALLABLE=TRUE -DCMAKE_INSTALL_PREFIX=../INSTALL_UNIX_"$build_name
	;;
*) 
	echo "No valid choice"
	exit 0
	;;
esac



mkdir -p "BUILD_UNIX_"$build_name

cd "BUILD_UNIX_"$build_name

cmake -G "$generator" $params ../src

read -p "Press enter to continue"
