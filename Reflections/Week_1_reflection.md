## Accomplishments

Over the previous week, I have actually achieved quite a bit. I have implemented a new buildchain in Cmake, implemented the catch2 testing framework, and cleaned up my codestyle significantly. After that I started work on implementing Quadratic Beizer curves in the fractal style.

## Challenges

I think the biggest challenge that I faced was in implementing the Catch2 framework. I had to try multiple times to implement the framework into CMake, and it took realizing that my short definitions in `pointHelper.hpp` needed to be inline to prevent possible multiple include errors. It took a bit of digging around on google results to find that out.

I also originally had a rather buggy implementation of Beizer Curves, as I did not realize that two iterations of lerp were needed for a four-point curve. Eventually however I found [this site](https://pomax.github.io/bezierinfo/) that provided a wonderful interactive description of beizer curves and from that I was able to implement my code the rest of the way.

## Next Steps

I feel like there is more that can be done to improve the beizer curve implementation. As it stands i am not really satisfied with the inconsistent weight of the fractal applied to the curve. However I still need to figure out how to best to smooth this out, as its intrinsic to the nature of the curve. I would like to see if there are any techniques for finding equally spaced points along a beizer curve.

After that I think my next step will be adding in the framework and widgets for changing the properties of lines. I dont feel like this will be a fast addition, however I now feel like it is my next important step in the process.

## Resources

I honestly dont know what to put here, outside of the Qt documentation, I dont have many consistent sources of information outside of what I find in the moment researching topics.