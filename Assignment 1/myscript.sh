#!/bin/bash

outputDir="/Users/mary/Documents/School/Interactive Tech/Asignment 1/merged.cpp"
mainFile="/Users/mary/Documents/School/Interactive Tech/Asignment 1/merged.cpp"
workingDirectory="/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code"

codingame-merge -w "$workingDirectory" -o "$outputDir"
# echo "hi"
# echo "$outputDir"
# cp "$outputDir" "$outputDir.temp"

# sed 's/.*/"&m/' "$outputDir" > "$outputDir.temp"

cat "$outputDir"  | pbcopy -selection clipboard
# pbcopy < "$outputDir.temp"


# rm "$outputDir.temp"

echo "Text copied to clipboard!"
