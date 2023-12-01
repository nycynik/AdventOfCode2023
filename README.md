# Advent of Code 2023

<pre>
 *        +     *           *           *                *    ___ *    *
      *  ( )          | advent of code *           *         |   |
   *    (  •)    *    | 2023    *            +              .|-H-|.    *
       ( •   )      * | [https://adventofcode.com/](https://adventofcode.com/)     *   \| (._.)
*     (     • )        +         *      *         *        \(  .  )--<  *
     (  •      )   *     *     +              *        *   (   .   )   +
</pre>

# Development

This is a c++ (mostly) AdventOfCode 2023 repo. This was started with a great starter (check it out in the top, it's a template.)

to use `nextday` you have to export your adventofcode cookie using 

    ❯ export ENVSESSION=<your cookie here>
    
## How to develop with this repo

Check out [DEV_README.md](./DEV_README.md) for more information on development

## Running a solution
There are three modes to run this program as shown in the usage. This section describes how to run one input file through. The [testing.md](testing.md) file describes the two other modes.  
The command line is:

    bin/aoc -d day -p part -f filename [extra_args...]

Everything should be straight forward - give it the day, part (1 or 2), input file, and optionally any extra arguments. It'll spit out the result or tell you if there's an error.

For example:  

    [brian@dev1 advent-of-code-cpp-starter]$ bin/aoc -d 0 -p 1 -f data/sample/day0_input.txt
    ***Day 0 Part 1 for file data/sample/day0_input.txt has result 569
