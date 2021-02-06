## Identify components

Canvas - A system for managing the currently loaded image, what elements make it up, and how to render it.

Fractal Noise System - Noise functions such as Perlin and Simplex noise in 1d work very well for creating the kinds of lines I desire, however work will need to be done to talor it to my needs

Brush system - a swappable system for how the mouse interacts with the canvas, allowing for selection of different "tools" 

System Singleton - There will be multiple windows associated with revealing system state to the user, there needs to be one location to access all of this.

File exportation system - Used for reading and writing files to a variety of file formats.

Interface Widgets - An entire slew of widgets and windows will need to be designed to expose the behavor of systems to the user.


## Understanding the Components

### Canvas

An essential component, that the tool cannot function without, it will be the primary interface. 

#### Interactions

The core interactions that the canvas will have is with its associated interface widget, as well as with the render object primitives that they store. Outside of this it will need to expose a clear api that allows other components in the system to interact with it in a standard way.

It would also need to interface with the brush system, so that it can properly respond to user inputs for placing lines, erasing them, and more. 


#### Component needs

Needs to be able to properly render to the screen, as well as store information relating to user interfaces. This doesnt need to be a lot of handwritten code as QT provides a very nice interface for such work in the form of the QGraphicsView 



### Fractal Noise System

An essential component, this is the core feature that I am basing my design around and must be included.

#### Interactions

This will most likely be provided by a small abstraction layer that allows for more efficent use of an existing noise library, either perlin or simplex fractal noise. And the goal is to write a competent middleman API for fractal lines to interact with.

#### Component needs

this should rely on no other components outside of a possible third party library. 


### Brush System

The brush system controls the way the mouse interacts with the canvas. It would be best implemented as an interface of callbacks that can be reimplemented for different behavior as needed.

#### Interactions

The brush system would most likely be either controlled by the canvas directly or otherwise a highly coupled class to the canvas, as it directly acts on the canvas, or more likely, the canvas requests the brush system to handle its input events as needed. This would allow for pointing between a few different brush subclasses that each override the default behaviour in different ways

### System singleton

The system singleton is the strategy that I will use for keeping track of data that needs to be shared between many different parts of the application, or in general exposed to multiple UI widgets at the same time. 

#### Interactions
This system should be the way that all single instance classes, such as the canvas, the current brush state, or anything else that may be useful to access across multiple other interfaces, most importantly the interface widgets, that all may wish to display seperate information regarding the current canvas state. For instance I would want to be able to access the canvas object with the canvas render widget, but also have a widget that provided metadata about the canvas, such as current dimensions, zoom, and object count. 

### File Exportation system

The exportation system most likely does not need a significant amount of interaction with other components, as it would mostly exist as a seperate feature that allows for multiple output file formats. 


### Interface widgets

UI widgets should all be basic levels of resizable and able to be placed anywhere on the interface, as to allow for easy redesign of the interface if needed. 


## Breakdown

### Renderable Object type
I expect to need to be able to render a number of different renderable types, and while I have some ideas of what this type might be due to my planned frameworks, it is still good to put it to words. I expect that outside of primitive types, such as straight lines and text that I could hopefully expect to be part of the rendering utility I use, I will have at least the following types of renderable object that I would like to implement myself:

- Fractal Noise line
- Beizer curve
- Fractal Noise curve (noise line modified by beizer curve)
- SVG Stamp

### Brush system

I have implemented a brush system before and understand the concept well, this is essentially a coding practice in which virtual functions are used as handlers for user inputs, allowing for different tools to behave in unique ways for the same inputs.

This is desired because it makes behavior such as keeping track of the currently used line weight and color while not actively using the line tool.

This would be best implemented through a fully virtual "Brush" interface that all different tools of the application (such as a beizer line drawing tool and a stamp tool) can inheret and implement.

### Canvas 

The canvas will most likely be implemented by my graphics engine, and only would be written out by hand if severe incomptabilities with my design goals are found in how it is structured. I will however need to extend it as I know there are a number of missing features that I would like to add to the existing planned QGraphicsView class. Including but not limited to:

- Clean, free panning that is not limited to the width of the scrollable area (Krita has a good implementation of this I would like to look into)
- A "Ruler" system that shows the current coordinates at the edge of the screen, like in photoshop.
- Possible extention to a layers system

### File exporters/importers

It would be preferable to have a clean interface for the importing and exporting of files, and the types that they allow. I think that I would prefer to implement this as a single monolythic class that has a enumeration of the types it is able to handle. So that exporting and importing functions as follows:

`exporter->exportCanvas(canvas, path_to_export, Exporter::TYPE_PNG);`

I feel that this is preferable to the alternative of:

`pngExporter->exportCanvas(canvas, path_to_export);`

The import and export system would also need to be able to import and export my custom file format for storing raw, still editable map data. Internally this should just be another type that can be exported, as opposed to a seperate interface.

Importing would also have to be a seperate interface from exporting entirely, as I want to leave room for the possibility of streaming data in instead of requiring all files to exist in memory at all times. I may not get to that point but I would like to leave the room to expand.

### The system singleton

The system singleton is the way that I want to expose the canvas, as well as the current brush settings, colors, and more to the UI classes, I want there to be a single importable header that allows for `lipuma->getCurrentCanvas()` and can be used to inspect the totality of the engine, as opposed to having all classes that wish to be singleton manage their own singleton nature. 

Unfortunately I do not think it is possible to avoid this behavior, as either I need a singleton manager, or every class would need to be passed a reference to the information it needs anyways, which may quickly become cumbersome.

### Interface widgets

There are a number of interface widgets that I think need to be created, and the exact order I add them is uncertain at this time. Possible options include: 

- Canvas Widget (most important)
- Tool selection widget
- Layer management widget
- Color selection widget
- Tool options widget (seperate from selection)
- File metadata displaybar
- File selection widget (For holding multiple canvases at the same time)
