<h2>About</h2>
Sailfish.Silica 1.0 compatible widgets which aim to speed up development by implementing Jolla recommended platform styles.

<h2>License</h2>

This project is GPLv3 unless otherwise indicated on the file itself. Files with other licenses are copyrighted to their respective owners.

Version 1.1

<h2>Usage</h2>
Basic instructions in order to use this in your QtQuick project:
<ol>
<li> Get the source code for this project</li>
<li> Make sure that SailfishWidgets directory is located in your QML Import Path
   <ul><li>If it isn't update the QML_IMPORT_PATH environment variable to point to the base directory (the directory above SailfishWidgets)</li></ul></li>
<li> In QML use <code>import SailfishWidgets <em>current-version</em></code></li>
<li> <strong>IMPORTANT</strong>: You must bundle SailfishWidgets in your installer so that the running application knows where to find it.</li> 
</ol>
<p>
Jolla Store Instructions: <br/>
The following are instructions to using SailfishWidgets with your own project. This project will <strong>PASS</strong> Jolla QA as long as you follow the following instructions. If you find a more clever way to do this, by all means share :-). Replace <em>your-project</em> with the name of your application (without the harbour-)
<ol>
  <li> First, download the source code and put the <code>SailfishWidgets</code> folder within the <code>harbour/<em>your-project</em></code> directory</li>
  <li> Then, edit the first line of qmldir. This is easiest accomplished with the following BASH command. <code>find . -name "qmldir" -exec sed -i "s/module SailfishWidgets/module harbour.<em>yourAppName</em>.SailfishWidgets/" \{} \;</code>. If you are on Windows, manually edit each qmldir that you use to <code>module harbour.<em>your-project</em>.SailfishWidgets.</em>CurrentPackage</em></code>.</li>
  <li> For using with QtCreator add the following<pre>
OTHERFILES += harbour/<em>your-app</em>/SailfishWidgets/*
QML_IMPORT_PATH = .
<em>your-app</em>.files = harbour
<em>your-app</em>.path = /usr/share/$${TARGET}
</pre></li>
   <li> In any QML file you want to edit add the following import statement: <code>import harbour.<em>your-app</em>.SailfishWidgets 1.0 as SailfishWidgets</code></li>
</ol>

<h2>Contribute</h2>

This application is open source,  but please do contribute to active development!
<p>
You can contribute in one of two ways:
<ul>
<li>Fork this branch and make pull request! (Please create an issue ticket first, though)
<li>Donate Bitcoins
</ul>
<p>
<img src="bitcoinaddy.png" />
<p>
<code>1PFqgHeGrtXLYvMge2mTT1FohKuuoKmUN5</code>

<p>

THANK YOU!

<h2>Links</h2>
<a href="http://qt-project.org/doc/qt-5/qtqml-modules-qmldir.html">qmldir specification</a>

<br>
Copyright ©2014 Dametrious Peyton. All Rights Reserved
