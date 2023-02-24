# Jesture UI
This is a C++ frontend to link with JesturePipe. It uses GLFW as the window manager
and Nuklear as the UI widget library.

## Quick Start
Run the Bazel target, and most things should be taken care of for you. You will
need to specify the compiler, however.

```
bazel run --config=<compiler> //jesture_qt:jesture
```

Replace `<compiler>` with `gcc9` or `gcc11` on Linux (tested with Ubuntu), `vs2019` or `vs2022` on
Windows, or `macos` on macOS.


Note that for macOS, you need to install Qt using homebrew before running the
command above.

```
brew install qt@6
```

We've got a basic menu layout for now. Not very pretty yet, but we're getting there!

![Progress Screenshot](./docs/progress_screenshot.png)