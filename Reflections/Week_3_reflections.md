## Accomplishments

The only accomplishments this week that can be readily seen from the code that I have committed is that I have learned a number of ways to *not* write a beizer curve implementation. I had attempted to make an interface for beizer curves which matched the "generator" idiom of python. This was because I wanted a simple way to request N points over a beizer curve without having to keep track of the number of points that had been generated so far by the code using the interface.

A number of conceptual challenges got in the way of this however.

## Challenges

I had attempted to create this generator interface through the use of the iterator syntax of cpp. This is a standard way of interacting with iteration that copies the interface for pointers, and pointer arithmatic.

To get the value the iterator `i` currently points to, you use `*i`.
To move the iterator to its next value, `++i` or `i++`;
Iterators must be comparable if in the same domain. This means that two iterators `i` and `j` should be equal `i == j` if they point to the same "value". This is used for the idea of the "past the end" iterator. An iterator that has completed iteration.

The syntax for properly defining all of this constitutes a significant amount of terse and confusing boilerplate. For instance, the way to define the prefix increment operator is `operator++()` however the postfix is `operator++(int)`. There are tiny gotcha's all over this, and it cost a lot of developer time attempting to resolve them.

Ultimately to this current moment I have not been able to resolve them.

## Next Steps

I think that I will give the iterator interface one more day to become functional, and if so I will finish implementing the two types of beizer curves that I want to be made.

After this, whether or not the interface works I will be moving on to implementing a serializing system for saving and loading maps. As I think this is the next direction to go.

## Resources

I used a lot of resources when attempting to build on windows, but as none of them helped, im not mentioning them.

For beizer curve implementation, [This](https://pomax.github.io/BezierInfo-2) has been extremely helpful