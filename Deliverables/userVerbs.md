## Tool
### Configure
1. User clicks on a configuration option in the Tool Settings widget.
3. The Tool setting widget accepts the event and modifies the associatied config option of the current tool object.

### Select
1. User clicks on a tool in the Tool Palette widget.
2. Tool Pallet emits a Tool Change event, allowing both the Canvas View and Tool Settings widgets to be notified.

## Canvas
### Draw on
- Reversable
1. User causes a click, drag, or release actions on the canvas view widget
2. canvas view widget recieves the event, and passes it to the currently active tool 
3. The tool recieves the event, as well as the canvas that is active, and updates the canvas as needed
4. The tool marks the event as handled. 

### Pan/Scale
1. The user causes a middle click, drag, or release action on the Canvas View Widget
2. Canvas View widget recieves the event and passes it to the currently active tool
3. The tool recieves the event and does not process it.
4. The canvas registers that the event was unhandled and handles it for panning or scrolling.

### Create New
1. User selects the New Canvas option from the taskbar, under file
2. A configuration modal appears with configuration options for the new canvas
3. The config modal communicates with the Canvas View widget, causing a new canvas object to be created
4. A CanvasChange event will be emmitted for widgets that need to update themselves.

### Save
1. User selects the Save option from the taskbar, under file
2. if the user has not saved this file already, or has selected Save as..., a save configuration menu appears, defining where to save the file.
3. The file is saved to the specified location.

### Load
1. User selects the Open option from the taskbar, under file
2. A file selection modal appears, filtered to only show Lipuma files.
3. The user selects the file to be opened. 
4. The file is loaded into memory.
5. The file selection modal communicates with the Canvas View widget causes the data loaded to be registered as a canvas
6. A CanvasChange event will be emmitted for widgets that need to update themselves.

### Export
1. User selects the export option from the taskbar, under file.
2. A modal appears asking where the file should be exported to.
3. Based on selected file type in the modal, the appropriate export configuration menu will appear, providing additional configuration details.
4. The file is exported with the given information.

### Select
1. The user clicks on a tab representing a canvas on the Canvas View widget
2. The Canvas View widget changes the currently active canvas
3. A CanvasChange event will be emmitted for widgets that need to update themselves.

## Canvas Object
> Canvas objects are the individual lines that can be modified.
### Select
- Reversable
1. User clicks on the canvas with the select tool
2. The select tool uses collision information and redraw information to identify what object or objects need to be selected
3. A "Selected" event is passed o all of the objects and they are added to a list of selected objects
4. Selected objects will use the selection event to update their draw state to reflect being selected.
5. A "Selection Updated" event will trigger, annoucing that widgets that rely on selection information need to be redrawn

### Deselect
- Reversable
1. User clicks on the canvas with the select tool
2. The select tool uses collision information and redraw information to identify what object or objects need to be selected or deselected
3. A "Selected" event is passed o all of the objects and they are added to a list of selected objects
4. Selected objects will use the selection event to update their draw state to reflect being selected.
5. A "Selection Updated" event will trigger, annoucing that widgets that rely on selection information need to be redrawn

### Move Selected
- Reversable
1. The user selects the transform tool
2. The transform tool paints to screen a transformation layout guide
3. The transform tool applies transformations to all selected objects as it is manipulated

### Configure Selected
- Reversable
1. While objects are selected the object settings widget will show applicable configuration for the current objects.
2. Any updates made here will apply to all selected objects
3. The object settings widget should only show settings that apply to all currently selected objects.

### Clipboard/Delete Selected
- Reversable
1. While objects are selected the user may use any of the common keyboard clipboard shortcuts, (ctrl+C, V, X; Delete)
2. This will cause an event that modifies the current selected objects

## Layer

### Select
1. The user clicks on a layer bar and releases without dragging
2. The layer control widget sets the current widget variable to the correct value

### Hide
1. The user clicks on an eye symbol associated with a particular layer
2. This layer object is then set to be invisible, no longer drawing any of its associated objects

### Reorder 
- Reversable
1. The user clicks and drags a layer box.
2. While dragging the layer box should be rendered under the mouse, with other layer objects shifting around
3. On release, the the layer control widget redefines the draw order of layers.

### Create 
- Reversable
1. On the layer control widget, a plus button is clicked
2. This creates a new empty layer adjacent to the currently selected layer, and automatically selects it

### Delete 
- Reversable
1. The user clicks on a trash button that is adjacent to the new layer button
2. A small warning model appears, confirming that the user would like to delete the layer
3. This layer is removed, and the memory of its contained objects are all cleared.
