## Accomplishments

The previous week has been rather slow. I spent most of my time working on building my program on windows for windows users to test my current project, however I was blocked significantly by linking issues. I also started a branch reworking the beizer curve implementation in order to reduce possible future errors.

## Challenges

The biggest challenge was that attempting to build the program on windows. I had attempted to build the program in a windows VM, using both MSVC and QtCreator, with many different modifications to my CMake files. Nothing that I attempted worked. I would either be unable to link correctly to the Qt libraries, or unable to properly link to the FastNose2 libraries. After about 4 concerted days of work on this, I had to give up, as I could not get it to work at all.

Additionally, I had hoped to figure out how to efficently draw equidistant subdivisions of beizer curves, however so far the math has been impossible for me to properly understand.

## Next Steps

Given that there was significant amounts of wasted time attempting to build the program in a new way, my short term plan is to start on implementing the previously mentioned line settings menu, so that I can better visualize the settings that are best for these new line types. I would like to have that done by the time of reporting out on thursday.

Minor goals to be completed after this include adding more tests, which should only take a day, and then adding a multiline tool for both straight lines and curve lines.

## Resources

I used a lot of resources when attempting to build on windows, but as none of them helped, im not mentioning them.

For beizer curve implementation, [This](https://pomax.github.io/BezierInfo-2) has been extremely helpful