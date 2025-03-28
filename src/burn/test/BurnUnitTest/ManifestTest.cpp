// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

#include "precomp.h"

namespace Microsoft
{
namespace Tools
{
namespace WindowsInstallerXml
{
namespace Test
{
namespace Bootstrapper
{
    using namespace System;
    using namespace Xunit;

    public ref class ManifestTest : BurnUnitTest
    {
    public:
        ManifestTest(BurnTestFixture^ fixture) : BurnUnitTest(fixture)
        {
        }

        [Fact]
        void ManifestLoadXmlTest()
        {
            HRESULT hr = S_OK;
            BURN_ENGINE_STATE engineState = { };
            try
            {
                LPCSTR szDocument =
                    "<BurnManifest EngineVersion='" szVerMajorMinorBuild "' ProtocolVersion='1' Win64='"
#if !defined(_WIN64)
                    "no"
#else
                    "yes"
#endif
                    "'>"
                    "    <UX PrimaryPayloadId='ux.exe'>"
                    "        <Payload Id='ux.exe' FilePath='ux.exe' Packaging='embedded' SourcePath='u0' />"
                    "    </UX>"
                    "    <Registration Code='{D54F896D-1952-43e6-9C67-B5652240618C}' Tag='foo' ProviderKey='foo' Version='1.0.0.0' ExecutableName='setup.exe' PerMachine='no' />"
                    "    <Variable Id='Variable1' Type='numeric' Value='1' Hidden='no' Persisted='no' />"
                    "    <RegistrySearch Id='Search1' Type='exists' Root='HKLM' Key='SOFTWARE\\Microsoft' Variable='Variable1' Condition='0' />"
                    "</BurnManifest>";

                hr = CacheInitialize(&engineState.cache, &engineState.internalCommand);
                TestThrowOnFailure(hr, L"Failed initialize cache.");

                hr = VariableInitialize(&engineState.variables);
                TestThrowOnFailure(hr, L"Failed to initialize variables.");

                // load manifest from XML
                hr = ManifestLoadXmlFromBuffer((BYTE*)szDocument, lstrlenA(szDocument), &engineState);
                TestThrowOnFailure(hr, L"Failed to parse manifest from XML.");

                // check variable values
                Assert::True(VariableExistsHelper(&engineState.variables, L"Variable1"));
            }
            finally
            {
                //CoreUninitialize(&engineState);
            }
        }
    };
}
}
}
}
}
