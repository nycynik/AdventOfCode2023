#!/bin/bash

git co main
git switch day${1} 2>/dev/null || git switch -c day${1};

cp ./include/solutions/aoc_day_0.h ./include/solutions/aoc_day_${1}.h
sed -i -e "s/__AOC_DAY_0__/__AOC_DAY_${1}__/g" ./include/solutions/aoc_day_${1}.h
sed -i -e "s/AocDay0/AocDay${1}/g" ./include/solutions/aoc_day_${1}.h

cp ./src/solutions/aoc_day_0.cpp ./src/solutions/aoc_day_${1}.cpp
sed -i -e "s/aoc_day_0.h/aoc_day_${1}.h/g" ./src/solutions/aoc_day_${1}.cpp
sed -i -e "s/AocDay0/AocDay${1}/g" ./src/solutions/aoc_day_${1}.cpp
sed -i -e "s/AocDay(0/AocDay(${1}/g" ./src/solutions/aoc_day_${1}.cpp

sed -i -e "s/member to the map goes here/member to the map goes here\n    m_days[${1}] = new AocDay${1}();/" ./src/solutions/aoc_days.cpp
sed -i -e "s/includes for each day will go here/includes for each day will go here\n#include \"aoc_day_${1}.h\"/" ./src/solutions/aoc_days.cpp

sed -i -E "s/# END daily solutions/build\/solutions\/aoc_day_${1}.o: src\/solutions\/aoc_day_${1}.cpp  \\\n	include\/solutions\/aoc_day_${1}.h \\\n	include\/solutions\/aoc_day.h \\\n	include\/common\/constants.h\n	g++ \${CPPFLAGS} -o build\/solutions\/aoc_day_1.o -c src\/solutions\/aoc_day_1.cpp${1}\n\n# END daily solutions/" ./Makefile
sed -i -e "s/build\/solutions\/aoc_days.o build\/solutions\/aoc_day_0.o \/build\/solutions\/aoc_days.o build\/solutions\/aoc_day_0.o build\/solutions\/aoc_day_{$1}.o /" ./Makefile
sed -i -e "s/	build/solutions/aoc_days.o  \\\	build/solutions/aoc_day_${1}.o  \\n/	build/solutions/aoc_days.o  \\/g" ./Makefile


curl "https://adventofcode.com/2023/day/${1}/input" \
  -o ./data/2023/day${1}_input.txt \
  -H 'authority: adventofcode.com' \
  -H 'accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7' \
  -H 'accept-language: en-US,en;q=0.9' \
  -H 'cache-control: max-age=0' \
  -H "cookie: session=${ENVSESSION}" \
  -H 'dnt: 1' \
  -H 'sec-ch-ua: "Google Chrome";v="119", "Chromium";v="119", "Not?A_Brand";v="24"' \
  -H 'sec-ch-ua-mobile: ?0' \
  -H 'sec-ch-ua-platform: "macOS"' \
  -H 'sec-fetch-dest: document' \
  -H 'sec-fetch-mode: navigate' \
  -H 'sec-fetch-site: none' \
  -H 'sec-fetch-user: ?1' \
  -H 'sec-gpc: 1' \
  -H 'upgrade-insecure-requests: 1' \
  -H 'user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36' \
  --compressed 
  