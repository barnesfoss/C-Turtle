<!-- markdownlint-disable MD024 -->

# Changelog

All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/2.0.0/), and this project adheres to [Semantic Versioning][SemVer].

## [Unreleased]

    Work in progress by [barnesfoss]

### Changed

    - Removed changelog from CTurtle.hpp and moved it to its own file `CHANGELOG.md`.
    - Completely refactored, no longer a single header, should be easier to maintain.
    - Moved to Meson build system!

## [1.0.5] - 2025-02-06

    Signed off by [walkerje]

### Changed

    - Updated dead links to documentation to new host.
    - Removed rendered docs.

## [1.0.4] - 2021-10-30

    Signed off by [walkerje]

### Fixed

    - Fixed a rounding-related position bug making it seem like negative translations were off-by-one while positive ones are not.
    - Only round X and Y coordinate positions if, and only if it will be used for rendering and explicit integer logic purposes.

## [1.0.3] - 2021-06-17

    Signed off by [walkerje]

### Fixed

    - Querying a color that doesn't exist by name now throws a runtime error detailing the issue.
    - no more segfaults when destroying turtles and their screens out-of-order; one or the other can be destructed first

### Added

    - Deconstruction behavior is now well-defined for turtle screens and turtles within the same scope.
    - bye() and exitonclick() are no longer necessary to close an InterativeTurtleScreen
    - Added xcor() and ycor() functions to the Turtle class (returns x coordinate and y coordinate of the related turtle)

### Changed

    - Rolled-back use of "make_unique" (a C++17 function) in favor of C++11-stable code
    - Remedied many, many clang/(-tidy) warnings throughout.

## [1.0.2] - 2021-02-25

    Signed off by [walkerje]

### Added

    - Implementation of turtle's goTo function that got erroneously removed

### Changed

    - Change isValid for BitmapFont class to consider the size of the glyph vector.

## [1.0.1] - 2021-02-15

    Signed off by [walkerje]

### Added

    - Added new constructor to Transform class to construct with an position and a rotation.

### Changed

    - Preprocessor check for M_PI under MSVC was malformed; replaced ifndef with ifdef
    - Implemented polygon line filling for drawLine function, reducing complexity to O(1) from O(n).

### Removed

    - Removed 100-pixel line width maximum from drawLine function.

## [1.0.0] - 2021-02-13

    First major release of C-Turtle
    Signed off by [walkerje]

### Added

    - Simplistic Bitmap Font Support
    - Default Bitmap Font, Proggy Clean (see https://proggyfonts.net)
    - Support for more dynamic font rendering, specifically allowing control over orientation, scale, and alignment.
    - "face" function to Turtles to orient the turtle towards another Point.
    - "addfont" and "font" function to the TurtleScreen class to register and retrieve user-provided Bitmap Fonts.
    - Appended version number to default title constructors in the TurtleScreen class.
    - Version numbering defines CTURTLE_VERSION_(MAJOR|MINOR|PATCH)

### Changed

    - Moved turtle function implementations to the inside of the Turtle Class
    - Moved default shape map definition to AbstractTurtleScreen rather than individual screens.
    - Refactored the internal turtle function "pushGeom" to "pushGeometry"
    - Organized include statements, and the top of the file in general.
    - Updated Documentation
    - Changed ivec2 implementation to use a union between an anonymous structure and an 2-wide array of integers

## [0.2.X] - 2020-04-23

    Signed off by [walkerje]
    - See GitHub commit histories 744dd6d through e7e17de

## [0.1.X] - 2020-04-23

    Signed off by [walkerje]
    - See GitHub commit histories a93dc4d through 744dd6d

## [0.0.X] - 2019-09-07

    Signed off by [walkerje]
    - See GitHub commit histories 12888e7 through a93dc4d

[SemVer]: https://semver.org
[@walkerje]: https://github.com/walkerje
[@barnesfoss]: https://github.com/barnesfoss
