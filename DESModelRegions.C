/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is a derivative work of OpenFOAM.

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

\*---------------------------------------------------------------------------*/

#include "DESModelRegions.H"
#include "turbulentTransportModel.H"
#include "turbulentFluidThermoModel.H"
#include "wallDist.H"
#include "bound.H"
#include "SpalartAllmarasDES.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{
    defineTypeNameAndDebug(DESModelRegions, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        DESModelRegions,
        dictionary
    );
}
}

const Foam::word Foam::functionObjects::DESModelRegions::modelName
(
    Foam::turbulenceModel::propertiesName
);

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool Foam::functionObjects::DESModelRegions::compressible()
{
    if (obr_.foundObject<compressible::turbulenceModel>(modelName))
    {
        return true;
    }
    else if (obr_.foundObject<incompressible::turbulenceModel>(modelName))
    {
        return false;
    }
    else
    {
        FatalErrorInFunction
            << "Turbulence model not found in database, deactivating"
            << exit(FatalError);
    }

    return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::functionObjects::DESModelRegions::DESModelRegions
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fvMeshFunctionObject(name, runTime, dict)
{
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::functionObjects::DESModelRegions::~DESModelRegions()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionObjects::DESModelRegions::execute()
{
    return true;
}


bool Foam::functionObjects::DESModelRegions::write()
{
    bool comp = compressible();

    if (comp)
    {
        const compressible::turbulenceModel& model =
            obr_.lookupObject<compressible::turbulenceModel>(modelName);

        typedef LESModels::SpalartAllmarasDES
        <
            compressible::turbulenceModel
        > cmpDESModel;

        if (isA<cmpDESModel>(model))
        {
            const cmpDESModel& des = dynamic_cast<const cmpDESModel&>(model);
            tmp<volScalarField> tdesField(des.LESRegion());
            volScalarField &desField = tdesField.ref();
            desField.write();
        }
    }
    else
    {
        const incompressible::turbulenceModel& model =
            obr_.lookupObject<incompressible::turbulenceModel>(modelName);

        typedef LESModels::SpalartAllmarasDES
        <
            incompressible::turbulenceModel
        > icoDESModel;

        if (isA<icoDESModel>(model))
        {
            const icoDESModel& des = dynamic_cast<const icoDESModel&>(model);
            tmp<volScalarField> tdesField(des.LESRegion());
            volScalarField &desField = tdesField.ref();
            desField.write();
        }
    }

    return true;
}


// ************************************************************************* //
