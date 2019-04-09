#!/bin/bash

if [[ -n $(git status --porcelain) ]]
then
  echo -e '\033[31;1mFiles are not formatted properly.\033[0m'
  git status
  exit 1
fi
exit 0
