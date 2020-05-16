# Fps.h

## Framerate
Measuring the framerate is done by calling `FpsLoop()` once _(and exactly once)_ per frame.
Every seconds or so, it will print to stdout an averaged framerate, and the average execution time of a single frame in milliseconds.  
The exact period of time in seconds between each log can be defined in [fps.h](fps.h) byt changing the `PERIOD` constant.

Every frame, the global variable `g_deltatime` will also be updated with the exact time in seconds that ellapsed between the beginning of the current frame and the previous one.

## Stopwatch
For measuring the performances of a specific portion of code.

You can mark the beginning and the end of a segment code with, respectively, calls to `StartWatch()` and `StopWatch()`.
Doing so will cause `FpsLoop` to also log the averaged execution time of this specific portion of code, and the portion of time in percentage it represents when compared the rest of the code.

Each call to `StartWatch` **must** be matched with **exactly one** call to `StopWatch` in order to work properly. Behaviour is undefined otherwise.

You are however, free to call this pair of functions multiple times per frame, in different areas of the code. In which case, the logged times will represent their cumulated execution times.

The impact of a handful of stopwatch's on the performances is negligible, though an excessive amount of calls (around several thousands of times per frame) will visibly slow down the whole program, and artificially inflate the results.
