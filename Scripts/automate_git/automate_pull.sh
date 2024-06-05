#!/bin/sh
cd ~/Desktop/Programming/
# Pull the latest changes from the remote repository
if git pull origin master; then
    echo "Pulled latest changes successfully"
else
    echo "Failed to pull latest changes"
    exit 1
fi

