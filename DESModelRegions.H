/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::functionObjects::DESModelRegions

Description
    Stores turbulence fields on the mesh database for further manipulation.

See also
    Foam::functionObjects::fvMeshFunctionObject
    Foam::functionObjects::timeControl

SourceFiles
    DESModelRegions.C

\*---------------------------------------------------------------------------*/

#ifndef functionObjects_DESModelRegions_H
#define functionObjects_DESModelRegions_H

#include "fvMeshFunctionObject.H"
#include "HashSet.H"
#include "NamedEnum.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{

/*---------------------------------------------------------------------------*\
                      Class DESModelRegions Declaration
\*---------------------------------------------------------------------------*/

class DESModelRegions
:
    public fvMeshFunctionObject
{
public:

    static const word modelName;


protected:

    // Protected data


    // Protected Member Functions

        //- Return true if compressible turbulence model is identified
        bool compressible();


private:

    // Private member functions

        //- Disallow default bitwise copy construct
        DESModelRegions(const DESModelRegions&);

        //- Disallow default bitwise assignment
        void operator=(const DESModelRegions&);


public:

    //- Runtime type information
    TypeName("DESModelRegions");


    // Constructors

        //- Construct from Time and dictionary
        DESModelRegions
        (
            const word& name,
            const Time& runTime,
            const dictionary& dict
        );


    //- Destructor
    virtual ~DESModelRegions();


    // Member Functions

        //- Calculate turbulence fields
        virtual bool execute();

        //- Do nothing.
        //  The turbulence fields are registered and written automatically
        virtual bool write();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace functionObjects
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
