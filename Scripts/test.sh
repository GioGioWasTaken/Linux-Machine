#!/usr/bin/env bash
while true; do
  read -p "Proceed? Y/N " resp
  if [[ $resp == 'N' ||$resp!='n' ]]; then
    exit 1
  elif [[ $resp != 'Y' || $resp!='y' ]]; then
    echo "You must enter either Y for yes, or N for no."
  else
    echo "Executing...."
    break
  fi
done
