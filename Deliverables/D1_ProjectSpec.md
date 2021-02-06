# Project Specification: Lipuma

## Summary 

Lipuma is a vector graphics tool for creating high quality art for fantasy maps. Its key feature is the fractal deformed line, that allows for creating complex and natural shapes without the tedium of having to create these features manually, and allows for more easily tweaking those features through smooth deformation of these craggy features. As well as supporting common map making features, such as feature stamps, location labels, exporting to many different image formats, and more. 

## Concept

The minimum scope of this project is to have a graphical editor that allows for the creation, saving, loading, and exporting of basic maps that could be expanded on in an art focused graphical program such as krita or photoshop. The most important feature that this program provides is again the vector nature of the art, and the fractal deformed lines that can be used to automate tedium. 

The most important feature to describe as being out of scope is any form of automatic generation of terrain, demographic information, climate information, or other items of that variety. This is a tool for someone with an idea for a land that they want to map out in their head, but does not have the time or skills to do so with more traditional map design tools, and as such it will not make any assuptions about the nature of map that the user wishes to create. 

Features that may be in scope depending on how quickly core features can be implemented and properly tested, include color selections, gradent and raster texture based layers rendered on top of the vector layer, text layout, creatable or importable "stamps" that can be used for repeating features (e.g. representing a mountain range with layered mountain symbols. 

## Software Requirements

1. Fractal line generation.
2. The ability to place fractal lines with the mouse and move them after being placed.
3. Ability to swap between straight line, fractal line, and pan/move tool.
4. Saving and loading of created designs to file for future editing.
5. in-engine understanding of distances, and a map-key utility.
6. Zooming and panning the viewport around the image.
7. Exporting the current canvas to image file types.
8. SVG importing for stamps.
9. Polygon tool for multi line fractals, or closed loop fractals.
10. Line color and polyline fill selection.
11. Multiple layers.


