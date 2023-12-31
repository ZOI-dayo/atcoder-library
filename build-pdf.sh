#!/bin/bash

cd `dirname $0`

opt=${2:-Portrait}
mkdir pdf
for file in **/*.hpp; do
  commitid=`git log -n 1 --pretty=format:%H ${file}`
  commitid=${commitid:0:7}
  mkdir -p pdf/`dirname ${file}`

  nvim ${file} -c 'set runtimepath+=~/.config/nvim/nightfox.nvim | colorscheme dayfox | set number | let g:html_font = "Cica" | TOhtml | w tmp.html | qa!'
  wkhtmltopdf --page-size B4 -O ${opt} --header-left "${commitid} ${file}" --header-right "[page]/[topage]" --header-font-name "Cica" --header-spacing 2 --no-background --margin-top 10 --margin-right 3 --margin-left 4 --margin-bottom 4 tmp.html pdf/${file}.pdf
  rm -f tmp.html

done
