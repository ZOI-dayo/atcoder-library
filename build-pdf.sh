#!/bin/bash

cd `dirname $0`

opt=${2:-Portrait}
commitid=`git log -n 1 --pretty=format:'%H'`
commitid=${commitid:0:7}
mkdir pdf
for file in `ls **/*.hpp`; do
  mkdir -p pdf/`dirname ${file}`

  nvim -v
  nvim -V1 -v
  nvim ${file} -c 'qa!'
  echo 1
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | qa!'
  echo 2
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | qa!'
  echo 3
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | set number | qa!'
  echo 4
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | set number | TSBufDisable highlight | qa!'
  echo 5
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | set number | TSBufDisable highlight | TOhtml | qa!'
  echo 6
  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | set number | TSBufDisable highlight | TOhtml | w tmp.html | qa!'
  echo 7
  wkhtmltopdf --page-size B4 -O ${opt} --header-left "${commitid} ${file}" --header-right "[page]/[topage]" --header-font-name "Cica" --header-spacing 2 --no-background --margin-top 10 --margin-right 3 --margin-left 4 --margin-bottom 4 tmp.html pdf/${file}.pdf
  rm -f tmp.html

done
