<h1>Laboratory 6</h1>

I have implemented the compulsory part. The Main class contains one static method, namely <em>public static void compulsory</em>, from which the application starts.
Classes I have implemented are:
<dl>
    <dt>MainFrame</dt>
    <dd>This is the class that represents the main frame of the application. It contains a ConfigPanel, a DrawingPanel and a ControlPanel.</dd>
    <dt>ConfigPanel</dt>
    <dd>Class representing different options for setting up the shape that we want to draw (no. of sides, stroke level, color type, radius).</dd>
    <dt>DrawingPanel</dt>
    <dd>The main canvas where shapes can be drawn.</dd>
    <dt>ControlPanel</dt>
    <dd>Contains buttons for saving, loading, reseting and exiting the application.</dd>
</dl>

<h2>Second commit - added optinal part</h2>
I have added a retainer mode (also a button for undoing shapes).
I have added support for drawing multiple shapes (from a forth panel implemented in the class ShapePanel, you can choose which shape you want to draw: a regular polygon, a bowtie, a snowflake or to just free draw). All shapes extends the Polygon abstract class and implement the MyShape interface. Besides this, the ConfigPanel adapts accordingly (for example, if you choose the free drawing mode, it only displays the color selecter and the size selecter).
The free drawing is implemented using a MouseMotionActionListener.