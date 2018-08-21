DESModelRegions
===============

DESModelRegions is a function object re-adapted from OpenFOAM® 2.4.x to OpenFOAM 5 and 6.

It has been created for two reasons:

  * Because of this feature request: https://bugs.openfoam.org/view.php?id=2763

  * And because some people also need this on OpenFOAM 6: https://www.cfd-online.com/Forums/openfoam-solving/117083-how-use-desmodelregions-function-object.html

This [git repository](https://github.com/wyldckat/DESModelRegions) was brought to you by Bruno Santos (wyldckat@github working at [FSD blueCAPE Lda](http://www.bluecape.com.pt)).


This will be contributed to the OpenFOAM Foundation after a feedback period from people who use this. So please report at https://www.cfd-online.com/Forums/openfoam-solving/117083-how-use-desmodelregions-function-object.html with which turbulence models you have tested this and if it worked or not.



Disclaimer and License
======================

This offering is not approved or endorsed by OpenCFD Limited, producer and distributor of the OpenFOAM software via www.openfoam.com, and owner of the OPENFOAM®  and OpenCFD®  trade marks.

This is bound to the same license as OpenFOAM, namely GNU Public License v3. Quoting from OpenFOAM's license statement:

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM. If not, see <http://www.gnu.org/licenses/>.



How to get+build DESModelRegions
================================

For getting and building from git:

```
git clone git://github.com/wyldckat/DESModelRegions.git
cd DESModelRegions
wmake
```

Or for getting and building from zip:

```
wget "https://github.com/wyldckat/yPlusLESWCompressible/archive/master.zip" -O DESModelRegions.zip
unzip DESModelRegions.zip
cd DESModelRegions-master
wmake
```


How to use it
=============

1. You must use the turbulence model `SpalartAllmarasDES` or one of its derivatives, as shown in the diagram here: https://cpp.openfoam.org/v5/classFoam_1_1LESModels_1_1SpalartAllmarasDES.html

2. For the function object, simply add the following block to your `system/controlDict`, inside the block `functions`, e.g.:

```
functions
{
    desField
    {
        type            DESModelRegions;
        functionObjectLibs ("libDESModelRegions.so");
        //region "region0";
        //timeStart 0.0;
        //timeEnd 10.0;
        writeControl timeStep;
        writeInterval  5000;
    }
}
```

The commented lines can be uncommented and used if necessary.
