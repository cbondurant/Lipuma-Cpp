# Intended tests
At the time of writing this document I already have a small collection of written unit tests, testing specific compontents of my system. Additional tests are in the works, however development difficulties have slowed down their proper integration.

Places that currently or are planned to have unit tests written for them are, the mathmatical convinence functions that I have implemented, the yet to be implemented bezier curve class and its associated functions, and file saving and loading integration.

The second kind of testing that I will be using is Usability testing through cognitive walkthroughs. I was inspired to use this kind of testing as a result of watching videos by youtube user tantacrul on his process for improving the UX of projects like musescore and more recently audacity. As the one place I lack critical skill in is proper user interface design, I wanted to get as much information as possible on what would make the interface more user friendly to new users, as I do not have any long term users to cater to at this time.

## Testing objectives
My primary objective in the addition of unit testing is not so much to find bugs as it is to prevent regression. I think that regression testing is a vitally important part of unit tests, as manually checking for all known bugs quickly becomes a fools errand. I unit test currently only the easily tested parts of my codebase, however I plan that as bugs are found through other forms of testing that regression tests should be written along side each fix in order to prevent changes from propagating new errors.

I will work to find most bugs through cognitive walkthroughs, and asking for guided user tests of new features without prompting in order to see what the way they expect to interact with new features is, tweaking the presentation and guidence based on what their first guesses of how to use new features are.

## Testing results

### Unit testing

There has been very little progress in the unit testing front recently, as each attempt at writing new tests has resulted in compilation failures that I do not think I will resolve in time for this document to be submitted. I will update this paragraph more if I am able to make any headway in the meantime.

### Cognitive Walkthrough

My first cognitive walkthrough with a user was very informative. I simply asked the user to begin trying to use the tool in they way they expected. They are an artist and are already comfortable with multiple art tools. As they knew this was a tool for drawing maps, and had seen screenshots of some possible things that could be made in the tool, I wanted to see how they reacted.

They immediately had feedback with regards to how they expected lines to be drawn, as opposed to how I had it implemented, and that the zoom scrolling direction was inverted from what they would expect.

After this, they also noted that it was confusing that you could not pan the screen with the middle mouse, which would be the expected behavior.

There are also other minor notes that I will be converting into issues on my github.