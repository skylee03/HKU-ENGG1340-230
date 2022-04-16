#!/bin/bash

if [ ! -d ncurses ]
then 
    echo "Downloading ncurses..."
    git clone https://github.com/mirror/ncurses.git
    echo "Downloaded successfully!"

    cd ncurses
    mkdir ~/local
    ./configure --prefix ~/local

    echo "Installing ncurses..."
    make -j
    make -j install
    echo "Installed successfully!"
fi

echo "Done!"
