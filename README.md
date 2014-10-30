<h2>About</h2>
Sailfish.Silica 1.0 compatible widgets which aim to speed up development by implementing Jolla recommended platform styles.

<h2>License</h2>

This project is GPLv3 unless otherwise indicated on the file itself. Files with other licenses are copyrighted to their respective owners.

Version 1.0

<h2>Usage</h2>
Basic instructions in order to use this in your QtQuick project:
<ol>
<li> Get the source code for this project</li>
<li> Make sure that SailfishWidgets directory is located in your QML Import Path
   <ul><li>If it isn't update the QML_IMPORT_PATH environment variable to point to the base directory (the directory above SailfishWidgets)</li></ul></li>
<li> In QML use <code>import SailfishWidgets 1.0</code> or whatever the current version</li>
<li> <strong>IMPORTANT</strong>: You must bundle SailfishWidgets in your installer so that the running application knows where to find it.</li> 
</ol>
<p>
Jolla Store Instructions: <br/>
The following are instructions to using SailfishWidgets with your own project (still untested). Replace <em>your-project</em> with the name of your application (without the harbour-)
<ol>
  <li> First, download the source code and put the <code>SailfishWidgets</code> folder within the <code>harbour/<em>your-project</em></code> directory</li>
  <li> Then, edit the first line of qmldir to read <code>module harbour.<em>your-project</em>.SailfishWidgets</code>.</li>
  <li> For using with QtCreator add the following<pre>
OTHERFILES += harbour/<em>your-app</em>/SailfishWidgets/*
QML_IMPORT_PATH = .
<em>your-app</em>.files = harbour
<em>your-app</em>.path = /usr/share/$${TARGET}
</pre></li>
   <li> In any QML file you want to edit add the following import statement: <code>import harbour.<em>your-app</em>.SailfishWidgets 1.0 as SailfishWidgets</code></li>
</ol>

THANK YOU!

<h2>Links</h2>
<a href="http://qt-project.org/doc/qt-5/qtqml-modules-qmldir.html">qmldir specification</a>

<br>
Copyright ©2014 Dametrious Peyton. All Rights Reserved
